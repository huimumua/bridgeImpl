// FIXME: your file license if you have one

#include "IqiBridge.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "sys/ioctl.h"

#include <android/log.h>
#include <log/log.h>
#include <string.h>

#include <poll.h>
#include <pthread.h>
#include <unistd.h>

namespace vendor {
namespace tct {
namespace iqibridge {
namespace V1_0 {
namespace implementation {

#define DEVICE_IQI_BRIDGE "/dev/ccci_iqi"
#define WR_BRIDGE_BUFFER_SIZE (1024)

#define BRIDGE_WAIT_WRITABLE_THREAD "iqibridge_wait_writable_thread"
#define BRIDGE_WAIT_READABLE_THREAD "iqibridge_wait_readable_thread"
#define BRIDGE_ASYNC_READ_THREAD "iqibridge_async_read_thread"
#define BRIDGE_ASYNC_WRITE_THREAD "iqibridge_async_write_thread"
#define BRIDGE_WAIT_MODEM_READY "iqibridge_wait_modem_ready"

#define LOG_TAG "MasterBridgeServer"
bool DUMP_BRIDGE_DATA = false;

int mBridgeFd = -1;

// callback func for notify the bridge event
sp<::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback> client_cb;

pthread_t mIqiBridgeWaitWritableThread;
pthread_t mIqiBridgeWaitReadableThread;
pthread_t mIqiBridgeAsyncOpenThread;
pthread_t mIqiBridgeWaitModemReadyThread;

pthread_t mAsyncReadThread;
pthread_t mAsyncWriteThread;

int64_t readDataLeft = 0;
int64_t writeDataLeft = 0;

IqiBridge *IqiBridge::sInstance = nullptr;

// Assitant function for dump buffer read/write
void dumpBridgeBufHex(const unsigned char *bin, unsigned int binsz, char **result) {
    char hex_str[]= "0123456789ABCDEF";
    unsigned int  i;

    *result = (char *)calloc(binsz * 2 + 1, sizeof(char));
    (*result)[binsz * 2] = 0;

    if (!binsz) {
        ALOGW("OOM");
        return;
    }

    for (i = 0; i < binsz; i++) {
        (*result)[i * 2 + 0] = hex_str[(bin[i] >> 4) & 0x0F];
        (*result)[i * 2 + 1] = hex_str[(bin[i]     ) & 0x0F];
    }
}

void dumpBridgeBuf(unsigned char *buf, unsigned int buf_len) {
    char *result = NULL;

    dumpBridgeBufHex(buf, buf_len, &result);
    ALOGI(">>>>>> server buffer: 0x%s, len=%d", result, buf_len);
    free(result);
}

static hidl_vec<unsigned char> toHidlVec(const std::vector<unsigned char> &vector) {
    hidl_vec<unsigned char> vec;
    vec.setToExternal(const_cast<unsigned char *>(vector.data()), vector.size());
    return vec;
}

static const std::vector<uint64_t> toVector(const android::hardware::hidl_vec<uint64_t> &vec) {
    std::vector<uint64_t> vector;
    vector.push_back(vec.data()[0]);
    return *const_cast<const std::vector<uint64_t> *>(&vector);
}

// Wrapper function for read "n" bytes from a descriptor.
int64_t readn(int fd, char *vptr, size_t n) {
    size_t nleft;
    int64_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0;        /* and call read() again */
            else {
                ALOGE("readn error, return");
                return(-1);
            }
        } else if (nread == 0) {
            ALOGW("readn, EOF");
            break;                /* EOF */
        }
        ALOGI("already read len=%lld", nread);

        nleft -= nread;
        ptr   += nread;
    }
    ALOGI("Already read: %u",(n - nleft));
    return(n - nleft);        /* return >= 0 */
}
/* end readn */

int64_t Readn(int fd, char *ptr, size_t nbytes) {
    int64_t n;

    if ( (n = readn(fd, ptr, nbytes)) < 0)
        ALOGE("readn error");
    return(n);
}

// Wrapper function for write "n" bytes to a descriptor.
int64_t writen(int fd, const unsigned char *vptr, size_t n) {
    size_t nleft;
    int64_t nwritten;
    const unsigned char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;        /* and call write() again */
            else
                return(-1);          /* error */
        }
        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(n);
}
/* end writen */

static void *iqiBridgeWaitReadableFunc(void *param) {
    struct pollfd fds[1];
    int poll_ret = -1;
    int timeout = 0;
    if (mBridgeFd < 0) {
        ALOGI("BridgeWaitReadableFunc() failed with invalid bridge type = %d", mBridgeFd);
        return NULL;
    }
    ALOGI("BridgeWaitReadableFunc enter loop");

    while (mBridgeFd > 0) {
        fds[0].fd = mBridgeFd;
        fds[0].events = POLLIN;

        //ALOGI("iqiBridgeReadFunc begin pull with fd = %d", mBridgeFd);
        poll_ret = poll(fds, 1, timeout);
        //ALOGI("iqiBridgeReadFunc end poll");

        if (poll_ret < 0) {
            ALOGI("BridgeWaitReadableFunc poll error, %s, errno = %d", strerror(errno), errno);
        } else {
            if (client_cb == NULL) return NULL;
            if (fds[0].revents & POLLIN) { // readable
                ALOGI("linhui BridgeWaitReadableFunc: Notify data readable");
                try {
                    Return<void> ret = client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_READABLE, NULL, 0);
                    if (!ret.isOk()) {
                        ALOGE("sendMsgToClient failed in readable, client maybe died.");
                    }
                } catch (...) { ALOGE("sendMsgToClient failed"); }
                break;
            }
        }
    }
    ALOGI("BridgeWaitReadableFunc exit loop");
    return NULL;
}

static void *iqiBridgeWaitWritableFunc(void *param) {
    struct pollfd fds[1];
    int poll_ret = -1;
    int timeout = 0;
    if (mBridgeFd < 0) {
        ALOGI("BridgeWaitWritableFunc() failed with invalid bridge type = %d", mBridgeFd);
        return NULL;
    }
    ALOGI("BridgeWaitWritableFunc enter loop");

    while (mBridgeFd > 0) {
        fds[0].fd = mBridgeFd;
        fds[0].events = POLLOUT;

        //ALOGI("iqiBridgeWriteFunc begin pull with fd = %d", mBridgeFd);
        poll_ret = poll(fds, 1, timeout);
        //ALOGI("iqiBridgeWriteFunc end poll");

        if (poll_ret < 0) {
            ALOGI("BridgeWaitWritableFunc poll error, %s, errno = %d", strerror(errno), errno);
        } else {
            if (client_cb == NULL) return NULL;
            if (fds[0].revents & POLLOUT){ // writable
                ALOGI("linhui BridgeWaitWritableFunc: Notify data writable");
                Return<void> ret = client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_WRITABLE, NULL, 0);
                if (!ret.isOk()) {
                    ALOGE("sendMsgToClient failed in writable, client maybe died.");
                }
                break;
            }
        }
    }
    ALOGI("BridgeWaitWritableFunc exit loop");
    return NULL;
}

// timer function for wait ccci modem ready
static void *iqiBridgeWaitModemReadyFunc(void *param) {
    if (mBridgeFd < 0) {
        ALOGI("BridgeWaitModemReadyFunc() failed with invalid bridge type = %d", mBridgeFd);
        return NULL;
    }
    ALOGI(">>>>>> BridgeWaitModemReadyFunc enter loop");
    int attemptCount = 0;

    while (mBridgeFd > 0 && attemptCount < 20 * 1000) {
        usleep(1000 * 1);
        attemptCount ++;
    }

    if (mBridgeFd > 0) {
        try {
            ALOGI(">>>>>> modem not ready in time, callback IO error");
            Return<void> ret = client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR, NULL, 0);
            if (!ret.isOk()) {
                ALOGE("sendMsgToClient failed in wait modem, client maybe died.");
            }
        } catch (...) { ALOGE("sendMsgToClient failed at wait modem ready"); }
    }
    ALOGI("BridgeWaitModemReadyFunc exit loop");
    return NULL;
}

// Async read
static void *iqiBridgeAsyncReadFunc(void *param) {
    ALOGI(">>>>>> Async read starting...");
    int64_t realReadLen = Readn(mBridgeFd, (char*)param, readDataLeft);

    ALOGI(">>>>>> iqiBridgeAsyncReadFunc done, realReadLen=%lld", realReadLen);
    if (realReadLen < 0 || client_cb == NULL) {
        free(param);
        if (client_cb != NULL) {
            client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR, NULL, 0);
        }
        return NULL;
    }
    if (DUMP_BRIDGE_DATA) {
        dumpBridgeBuf((unsigned char*)param, realReadLen);
    }

    std::vector<unsigned char> v(realReadLen);
    memset(v.data(), 0, realReadLen);
    memcpy(v.data(), param, realReadLen);

    const hidl_vec<unsigned char> temp = toHidlVec(v);
    ALOGI(">>>> iqiBridgeAsyncReadFunc, callback read complete");
    client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_READ_COMPLETE, temp, realReadLen);
    free(param);
    return NULL;
}

// Async write
static void *iqiBridgeAsyncWriteFunc(void *param) {
    ALOGI(">>>>>> Async write starting...");
    if (writeDataLeft > 0 && param != NULL && DUMP_BRIDGE_DATA) {
        dumpBridgeBuf((unsigned char*)param, writeDataLeft);
    }
    int64_t realWriteLen = writen(mBridgeFd, (unsigned char*)param, writeDataLeft);
    if (realWriteLen < 0 || client_cb == NULL) {
        free(param);
        if (client_cb != NULL) {
            client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR, NULL, 0);
        }
        return NULL;
    }
    ALOGI(">>>> Async write complete, realWriteLen=%lld, writeDataLeft=%lld", realWriteLen, writeDataLeft);
    client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_WRITE_COMPLETE, NULL, realWriteLen);
    free(param);
    return NULL;
}

// For async open iqi bridge
static void* tryAsyncOpenBridgeFunc(void* param) {
    ALOGI(">>>>>> Open bridge failed before, try async open, enter loop.");
    if(mBridgeFd > 0) {
        ALOGW("tryAsyncOpenBridgeFunc, bridge open success before, check previous logs");
        return NULL;
    }

    int attemptCount = 0;
    int fd = -1;

    while((fd < 0) && (attemptCount++ < 30)) {
        fd = open(DEVICE_IQI_BRIDGE, O_RDWR|O_NONBLOCK);
        if (fd < 0) {
            ALOGD(">>>>>> openStream() failed, fd=%d, errno=%d(%s), attempt count: %d, wait and try again!!",
                 fd, errno, strerror(errno), attemptCount);
            sleep(1);
            continue;
        }

        if(fd > 0) {
            mBridgeFd = fd;
            ALOGI(">>>>>> open bridge async successfully, fd=%d.",fd);
            // notify client -> app
            Return<void> ret = client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_OPEN_COMPLETE, NULL, fd);
            if (!ret.isOk()) {
                ALOGE("sendMsgToClient failed in async open, client maybe died.");
            }
            break;
        }
    }
    if(fd < 0 || attemptCount >= 30) {
        ALOGW(">>>>>> tryAsyncOpenBridgeFunc, open failed, fd=%d, errno=%d(%s)", fd, errno, strerror(errno));
        Return<void> ret = client_cb->sendMsgToClient((long long)iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR, NULL, 0);
        if (!ret.isOk()) {
            ALOGE("sendMsgToClient failed in async open error, client maybe died.");
        }
        return NULL;
    }
    ALOGD(">>>>>> tryAsyncOpenBridgeFunc loop end, openStream(), fd=%d", fd);
    return NULL;
}

IqiBridge::IqiBridge() {
    sInstance = this;
    ALOGI("Bridge fetch function, malloc buffer");
    mBridgeBuffer = (void*)malloc(WR_BRIDGE_BUFFER_SIZE);
    if (mBridgeBuffer == nullptr) {
        ALOGE("malloc buffer failed, try again");
    }
}

IqiBridge::~IqiBridge() {
    ALOGI("Bridge deconstractor function, free buffer");
    if (mBridgeBuffer == nullptr) {
        return;
    }
    free(mBridgeBuffer);
    mBridgeBuffer = nullptr;
}

IIqiBridge* IqiBridge::getInstance() {
    if (!sInstance) {
        ALOGI("sInstance is null, new one");
        sInstance = new IqiBridge();
    }
    return sInstance;
 }

// Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridge follow.
Return<int64_t> IqiBridge::tryOpen(const sp<::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback>& cb) {
    if (DUMP_BRIDGE_DATA) ALOGD(">>>>>> Bridge::open device node, %s",DEVICE_IQI_BRIDGE);

    if (mBridgeFd > 0) {
        ALOGD(">>>>>> Already open the bridge, close firstly, then reopen");
        tryClose();
    }
    client_cb = cb;
    int fd = open(DEVICE_IQI_BRIDGE,O_RDWR|O_NONBLOCK);
    int aErrno = errno;
    if (fd < 0) {
        mBridgeFd = -1;
        if (aErrno == EAGAIN || aErrno == EWOULDBLOCK || aErrno == ENODEV) {
            ALOGD("openStream() async pending, errno=%d(%s)", errno, strerror(errno));
            memset(&mIqiBridgeAsyncOpenThread, 0, sizeof(pthread_t));
            pthread_create(&mIqiBridgeAsyncOpenThread, NULL, tryAsyncOpenBridgeFunc, this);
            pthread_setname_np(mIqiBridgeAsyncOpenThread, "async_open_thread");
            return (long long)iq_porting_io_status::IQ_PORTING_IO_WOULDBLOCK;
        }
        ALOGD("openStream() failed, fd=%d, errno=%d(%s)", fd, errno, strerror(errno));
        return (long long)iq_porting_io_status::IQ_PORTING_IO_BROKEN;
    }
    mBridgeFd = fd;
    /*memset(&mAsyncReadThread, 0, sizeof(pthread_t));
    memset(&mAsyncWriteThread, 0, sizeof(pthread_t));*/
    ALOGD(">>>>>> Bridge open(%d) successfully", mBridgeFd);
    return fd;
}

Return<void> IqiBridge::tryRead(uint64_t rLen, tryRead_cb _hidl_cb) {
    if (mBridgeFd < 0) return Void();
    ALOGI(">>>>>> server read begin, try read len=%llu", rLen);
    readDataLeft = rLen;
    IqiBridge* thisPtr = static_cast<IqiBridge*>(IqiBridge::getInstance());

    // only malloc once in constractor func, if fail, alloc here
    if (thisPtr->mBridgeBuffer == nullptr) {
        thisPtr->mBridgeBuffer = (void*)malloc(WR_BRIDGE_BUFFER_SIZE);
    }

    memset(thisPtr->mBridgeBuffer, 0, WR_BRIDGE_BUFFER_SIZE);
    int64_t realReadLen = read(mBridgeFd, thisPtr->mBridgeBuffer, rLen);
    //int64_t realReadLen = Readn(mBridgeFd, (char*)tempBuffer, rLen);
    ALOGI("try read, realReadLen=%lld",realReadLen);
    if (realReadLen > 0) {
        ALOGD(">>>>>> Read data from device node OK, realReadLen=%lld", realReadLen);
    } else if (realReadLen < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == ETXTBSY) {
            ALOGW(">>>>>> No data read from device node. wait readable, errno=%d(%s)", errno, strerror(errno));
            memset(&mIqiBridgeWaitReadableThread, 0, sizeof(pthread_t));
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
            pthread_create(&mIqiBridgeWaitReadableThread, &attr, iqiBridgeWaitReadableFunc, NULL);
            pthread_setname_np(mIqiBridgeWaitReadableThread, BRIDGE_WAIT_READABLE_THREAD);
            _hidl_cb(realReadLen, {});
        } else {
            ALOGW(">>>>>> read data error, errno=%d(%s)", errno, strerror(errno));
            _hidl_cb(-2, {});
        }
        return Void();
    }
    if (DUMP_BRIDGE_DATA) {
        dumpBridgeBuf((unsigned char*)thisPtr->mBridgeBuffer, realReadLen);
    }

    std::vector<unsigned char> v(realReadLen);
    memset(v.data(), 0, realReadLen);
    memcpy(v.data(),thisPtr->mBridgeBuffer,realReadLen);

    const hidl_vec<unsigned char> temp = toHidlVec(v);

    _hidl_cb(realReadLen,temp);
    /*if (realReadLen < rLen) {
        readDataLeft = rLen - realReadLen;
        ALOGW(">>>>>> data not read complete, starting async read");
        memset(tempBuffer, 0, rLen);
        pthread_create(&mAsyncReadThread, NULL, iqiBridgeAsyncReadFunc, tempBuffer);
        pthread_setname_np(mAsyncReadThread, BRIDGE_ASYNC_READ_THREAD);
        return Void();
    }*/

    return Void();
}

static int64_t lastwritten_len = 0;

Return<int64_t> IqiBridge::tryWrite(const hidl_vec<uint8_t>& inBuffer, uint64_t wLen) {
    if (mBridgeFd < 0) return (long)iq_porting_status::IQ_PORTING_ERROR;

    ALOGD(">>>>>> server write begin, len=%llu", wLen);
    if (DUMP_BRIDGE_DATA) {
        dumpBridgeBuf((unsigned char*)inBuffer.data(), wLen);
    }
    writeDataLeft = wLen;

    if (lastwritten_len >= 500) {
        ALOGD(">>>>>> Write data sleep 5 ms");
        usleep(1000 * 5);
    }

    int64_t realWriteLen = write(mBridgeFd, inBuffer.data(), inBuffer.size());
    // int64_t realWriteLen = writen(mBridgeFd, (unsigned char*)inBuffer.data(), inBuffer.size());
    if (realWriteLen > 0) {
        ALOGD(">>>>>> Write data successfully, realWriteLen=%lld",realWriteLen);
    } else if (realWriteLen < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == ETXTBSY) {
            ALOGW(">>>>>> Write data to device node failed, wait writable, errno=%d(%s)",errno, strerror(errno));
            memset(&mIqiBridgeWaitWritableThread, 0, sizeof(pthread_t));
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
            pthread_create(&mIqiBridgeWaitWritableThread, &attr, iqiBridgeWaitWritableFunc, NULL);
            pthread_setname_np(mIqiBridgeWaitWritableThread, BRIDGE_WAIT_WRITABLE_THREAD);
            return realWriteLen;
        } else {
            ALOGI(">>>>>> write return errno=%d(%s)",errno, strerror(errno));
            if (errno == ENODEV) {
                ALOGW(">>>>>> starting timer for wait modem ready");
                memset(&mIqiBridgeWaitModemReadyThread, 0, sizeof(pthread_t));
                pthread_attr_t attrWait;
                pthread_attr_init(&attrWait);
                pthread_attr_setdetachstate(&attrWait, PTHREAD_CREATE_DETACHED);
                pthread_create(&mIqiBridgeWaitModemReadyThread, &attrWait, iqiBridgeWaitModemReadyFunc, NULL);
                pthread_setname_np(mIqiBridgeWaitModemReadyThread, BRIDGE_WAIT_MODEM_READY);
                return realWriteLen;
            }
            return -2;
        }
        // Async write
    }/* else {
        writeDataLeft = wLen - realWriteLen;
        char* tempBuffer = (char*)malloc(writeDataLeft);
        memset(tempBuffer, 0, writeDataLeft);
        memcpy(tempBuffer, (char*)inBuffer.data()+realWriteLen, writeDataLeft);
        ALOGW(">>>>>> data not write complete, starting async write");
        pthread_create(&mAsyncWriteThread, NULL, iqiBridgeAsyncWriteFunc, (void*)tempBuffer);
        pthread_setname_np(mAsyncWriteThread, BRIDGE_ASYNC_WRITE_THREAD);
    }*/

    lastwritten_len = realWriteLen;
    return realWriteLen;
}

Return<int64_t> IqiBridge::tryClose() {
    if (mBridgeFd < 0) return (long)iq_porting_status::IQ_PORTING_ERROR;
    ALOGD(">>>>>> close bridge, mBridgeFd=%d",mBridgeFd);
    int ret = close(mBridgeFd);
    if (ret < 0) {
        ALOGW("close bridge device node failed, errno=%d(%s)!", errno, strerror(errno));
        return ret;
    }
    ALOGD(">>>>>> server device node close successfully");
    mBridgeFd = -1;
    client_cb = NULL;
    return ret;
}

Return<void> IqiBridge::setLoggingEnabled(bool loggingEnabled) {
    ALOGI("setLoggingEnabled, loggingEnabled=%d", loggingEnabled);
    DUMP_BRIDGE_DATA = loggingEnabled;
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

IIqiBridge* HIDL_FETCH_IIqiBridge(const char* /* name */) {
    return new IqiBridge();
}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor
