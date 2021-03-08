/*
 * Copyright (c) 2016 AT&T Intellectual Property. ALL RIGHTS RESERVED
 *
 * This code is licensed under a personal license granted to you by AT&T.
 *
 * All use must comply with the terms of such license. No unauthorized use,
 * copying, modifying or transfer is permitted without the express permission
 * of AT&T. If you do not have a copy of the license, you may obtain a copy
 * of such license from AT&T.
 */

#include "IQPortingMasterBridgeImpl.h"
#include "IQTargetLogging.h"

#define BRIDGE_TYPE_NONE 0
#define BRIDGE_TYPE_CCCI_IQI 1


#define BRIDGE_TYPE	BRIDGE_TYPE_CCCI_IQI

#if (BRIDGE_TYPE == BRIDGE_TYPE_NONE)
iq_porting_status_t IQPorting_MasterBridgeInitializeImpl (IQ_VOID_PARAMLIST)
{
    return IQ_PORTING_NOT_IMPLEMENTED;
}

iq_porting_status_t IQPorting_MasterBridgeOpenImpl (iq_io_callback_t callbackFunc, void *callbackData)
{
    IQ_UNUSED_PARAM(callbackFunc);
    IQ_UNUSED_PARAM(callbackData);
    return IQ_PORTING_NOT_IMPLEMENTED;
}

iq_porting_status_t IQPorting_MasterBridgeReadImpl (void *ioBuffer, unsigned long *ioLen)
{
    IQ_UNUSED_PARAM(ioBuffer);
    IQ_UNUSED_PARAM(ioLen);
    return IQ_PORTING_NOT_IMPLEMENTED;
}

iq_porting_status_t IQPorting_MasterBridgeWriteImpl (IQ_CONST_PARAM void *ioBuffer, unsigned long *ioLen)
{
    IQ_UNUSED_PARAM(ioBuffer);
    IQ_UNUSED_PARAM(ioLen);
    return IQ_PORTING_NOT_IMPLEMENTED;
}

iq_porting_status_t IQPorting_MasterBridgeCloseImpl (IQ_VOID_PARAMLIST)
{
    return IQ_PORTING_NOT_IMPLEMENTED;
}

iq_porting_status_t IQPorting_MasterBridgeShutdownImpl (IQ_VOID_PARAMLIST)
{
    return IQ_PORTING_NOT_IMPLEMENTED;
}
#endif


#if (BRIDGE_TYPE == BRIDGE_TYPE_CCCI_IQI)

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <termios.h>
#include <pthread.h>
#include <string.h>

#include <vendor/tct/iqibridge/1.0/IIqiBridge.h>
#include <vendor/tct/iqibridge/1.0/IIqiBridgeEventCallback.h>
using ::vendor::tct::iqibridge::V1_0::IIqiBridge;
using ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback;

using android::hardware::Return;
using android::hardware::Void;

#include <log/log.h>
#define LOG_TAG "MasterBridgeClient"
static android::sp<IIqiBridge> service = nullptr;
#define WR_BRIDGE_BUFFER_SIZE (1024)
bool DUMP_BRIDGE_DATA = true;

typedef struct {
    int              mStreamFd;
    iq_io_callback_t cb_func;
    void*            cb_data;
    void*            read_data;
    int64_t          read_len;
    int64_t          write_len;
    bool             pending;
    bool             inited;
    bool             opened;
    bool             closed;
}master_bridge_info_t;

static master_bridge_info_t master_bridge_info;
static master_bridge_info_t * mbip = &master_bridge_info;

pthread_t mIqiBridgeCbThread;

static void init_master_bridge_info() {
    mbip->cb_func   = NULL;
    mbip->cb_data   = NULL;
    mbip->read_data = NULL;
    mbip->read_len  = 0;
    mbip->write_len = 0;
    mbip->inited    = true;
    mbip->opened    = false;
    mbip->closed    = true;
    memset(&mIqiBridgeCbThread, 0, sizeof(pthread_t));
}

static void uninit_master_bridge_info() {
    mbip->cb_func   = NULL;
    mbip->cb_data   = NULL;
    mbip->inited    = false;
    mbip->opened    = false;
    mbip->closed    = true;
}

static void set_master_bridge_closed() {
    mbip->cb_func = NULL;
    mbip->cb_data = NULL;
    mbip->opened  = false;
    mbip->closed  = true;
}

static void set_master_bridge_callback(
        iq_io_callback_t cb_func, void* cb_data) {
    mbip->cb_func = cb_func;
    mbip->cb_data = cb_data;
}

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
    ALOGI("******** client buffer: 0x%s, len=%d", result, buf_len);
    free(result);
}

// Function callback to notify App about IO event coming up
static void *iqiBridgeCbThreadFunc(void *param) {
    int64_t * temp = (int64_t *)param;
    int64_t eventId = (int64_t)*temp;
    if (mbip->cb_func == NULL) return NULL;
    switch(eventId)
    {
        case IQ_PORTING_IOEVENT_OPEN_COMPLETE:
            ALOGI("async open bridge completely, callback to App");
            mbip->cb_func(mbip->cb_data,IQ_PORTING_IOEVENT_OPEN_COMPLETE, 0, IQ_PORTING_OK);
            break;
        case IQ_PORTING_IOEVENT_READABLE:
            ALOGI("bridge readable, callback to App");
            mbip->cb_func(mbip->cb_data,IQ_PORTING_IOEVENT_READABLE, 0, IQ_PORTING_OK);
            break;
        case IQ_PORTING_IOEVENT_WRITABLE:
            ALOGI("bridge writeable, callback to App");
            mbip->cb_func(mbip->cb_data,IQ_PORTING_IOEVENT_WRITABLE, 0, IQ_PORTING_OK);
            break;
        case IQ_PORTING_IOEVENT_READ_COMPLETE:
            ALOGI("bridge read completely, callback to App");
            mbip->cb_func(mbip->cb_data, IQ_PORTING_IOEVENT_READ_COMPLETE, mbip->read_len, IQ_PORTING_OK);
            break;
        case IQ_PORTING_IOEVENT_WRITE_COMPLETE:
            ALOGI("bridge write completely, callback to App");
            mbip->cb_func(mbip->cb_data, IQ_PORTING_IOEVENT_WRITE_COMPLETE, mbip->write_len, IQ_PORTING_OK);
            break;
        case IQ_PORTING_IOEVENT_ERROR:
            ALOGI("bridge receive io event error, callback to App");
            mbip->cb_func(mbip->cb_data, IQ_PORTING_IOEVENT_ERROR, 0, IQ_PORTING_IO_BROKEN);
            break;
        default:
            ALOGW("unknown event id from bridge server!!!");
    }
    ALOGI("notify app event coming done");
    free(param);
    return NULL;
}

class IqiBridgeEventCallback : public IIqiBridgeEventCallback {
    Return<void> sendMsgToClient(int64_t eventId, const android::hardware::hidl_vec<uint8_t>& outBuffer, int64_t bufferLen) {
        ALOGI("sendMsgToClient called from server, eventId=%lld, bufferLen=%lld",eventId, bufferLen);
        int64_t alreadyRead = mbip->read_len;
        switch(eventId) {
            case IQ_PORTING_IOEVENT_READ_COMPLETE:
                mbip->read_len += bufferLen;
                if (bufferLen > 0 && outBuffer != NULL && mbip->read_data != NULL) {
                    // fill buffer, App will get buffer from it.
                    memcpy((unsigned char*)mbip->read_data+alreadyRead, (unsigned char*)outBuffer.data(), bufferLen);
                    dumpBridgeBuf((unsigned char*)mbip->read_data, mbip->read_len);
                }
                break;
            case IQ_PORTING_IOEVENT_WRITE_COMPLETE:
                mbip->write_len += bufferLen;
                break;
            case IQ_PORTING_IOEVENT_OPEN_COMPLETE:
                mbip->mStreamFd = bufferLen;
                break;
        }

        int64_t *eventIdPtr = (int64_t *)calloc(0, sizeof(int64_t));
        *eventIdPtr = eventId;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&mIqiBridgeCbThread, &attr, iqiBridgeCbThreadFunc, (void *)eventIdPtr);
        pthread_setname_np(mIqiBridgeCbThread, "iqibridge_cb_thread");
        return Void();
    }
};

int openDeviceInternal() {
    if (DUMP_BRIDGE_DATA) ALOGI("******** IQPorting_MasterBridgeOpen");

    android::sp<IIqiBridgeEventCallback> bridgeCb =  new IqiBridgeEventCallback();

    int fd = service->tryOpen(bridgeCb);
    if (DUMP_BRIDGE_DATA) ALOGI("openDeviceInternal, fd=%d",fd);
    return fd;
}

iq_porting_status_t IQPorting_MasterBridgeInitializeImpl (IQ_VOID_PARAMLIST) {
    service = IIqiBridge::getService();
    if (service == nullptr) {
        ALOGE("IQPorting_MasterBridgeInitialize, failed to get hidl service\n");
        return IQ_PORTING_ERROR;
    }
    init_master_bridge_info();
    if (DUMP_BRIDGE_DATA) ALOGI("******** IQPorting_MasterBridgeInitialize, IQ_PORTING_OK");

    return IQ_PORTING_OK;
}

iq_porting_status_t IQPorting_MasterBridgeOpenImpl (iq_io_callback_t callbackFunc, void *callbackData) {
    if (callbackFunc == NULL) {
        ALOGW("IQ Agent did not specify an I/O Callback func. Assert");
        return IQ_PORTING_IO_ERROR_BASE;
    }

    if (mbip->inited == false) {
        ALOGW("Open master bridge without initialized!");
        return IQ_PORTING_IO_ERROR_BASE;
    }
    set_master_bridge_callback(callbackFunc, callbackData);

    int fd = openDeviceInternal();

    if (fd < 0) {
        mbip->mStreamFd = -1;
        if (DUMP_BRIDGE_DATA) ALOGW("******** IQPorting_MasterBridgeOpen return IQ_PORTING_IO_ASYNC_PENDING");
        return IQ_PORTING_IO_ASYNC_PENDING;
    }
    mbip->mStreamFd = fd;

    if (DUMP_BRIDGE_DATA) ALOGI("IQPorting_MasterBridgeOpen(%d): IQ_PORTING_OK", mbip->mStreamFd);
    return IQ_PORTING_OK;
}

iq_porting_status_t IQPorting_MasterBridgeReadImpl (void *ioBuffer, unsigned long *ioLen) {
    /* Validate params */
    if (ioBuffer == NULL) {
        ALOGE("Read buffer provided by IQ Agent is NULL.");
        return IQ_PORTING_INVALID_PARAM;
    }

    if (*ioLen == 0) {
        ALOGE("No. of bytes to read provided by IQ Agent is 0. Skip read");
        return IQ_PORTING_INVALID_PARAM;
    }

    if (DUMP_BRIDGE_DATA) ALOGI("******** IQPorting_MasterBridgeRead");
    //int64_t req_size = *ioLen;
    int64_t readLen = -1;
    std::vector<uint8_t> data((*ioLen));
    memset(data.data(),0,*ioLen);
    auto a = service->tryRead(*ioLen, [&](int32_t rVal, const android::hardware::hidl_vec<uint8_t> buf) {
        readLen = rVal;
        data = buf;
    });
    if (readLen == -1) {
        if (DUMP_BRIDGE_DATA) ALOGI("******** No data read from node, return IQ_PORTING_IO_WOULDBLOCK");
        *ioLen = 0;
        return IQ_PORTING_IO_WOULDBLOCK;
    } else if (readLen < 0) {
        *ioLen = 0;
        return IQ_PORTING_ERROR;
    }
    if (DUMP_BRIDGE_DATA) ALOGI("******** Read data from server, len=%lld", readLen);
    *ioLen = readLen;
    memcpy(ioBuffer, data.data(), readLen);
    if (DUMP_BRIDGE_DATA) {
        dumpBridgeBuf((unsigned char*)ioBuffer, readLen);
    }
    /*if (readLen == req_size) { // read data end
        if (DUMP_BRIDGE_DATA) {
            dumpBridgeBuf((unsigned char*)ioBuffer, readLen);
        }
    } else {
        ALOGI("******** IQPorting_MasterBridgeRead IQ_PORTING_IO_ASYNC_PENDING, current readLen=%lld", readLen);
        // Async read in server.
        mbip->read_data = ioBuffer;
        mbip->read_len = readLen;
        return IQ_PORTING_IO_ASYNC_PENDING;
    }*/
    if (DUMP_BRIDGE_DATA) ALOGI("******** IQPorting_MasterBridgeRead IQ_PORTING_OK");

    return IQ_PORTING_OK;
}

iq_porting_status_t IQPorting_MasterBridgeWriteImpl (IQ_CONST_PARAM void *ioBuffer, unsigned long *ioLen) {
    /* Validate params */
    if (ioBuffer == NULL) {
        ALOGE("Write buffer provided by IQ Agent is NULL.");
        return IQ_PORTING_INVALID_PARAM;
    }

    if (*ioLen == 0) {
        ALOGE("No. of bytes to write provided by IQ Agent is 0. Skip write");
        return IQ_PORTING_INVALID_PARAM;
    }
    //int64_t req_size = *ioLen;

    std::vector<unsigned char> temp(*ioLen);
    memcpy(temp.data(), ioBuffer,*ioLen);

    if (DUMP_BRIDGE_DATA) {
        ALOGI("******** IQPorting_MasterBridgeWrite start, len=%lu", *ioLen);
        dumpBridgeBuf((unsigned char*)ioBuffer, *ioLen);
    }
    iq_porting_status_t rVal = service->tryWrite(temp, *ioLen);
    *ioLen = rVal;
    if (rVal == -1) {
        if (DUMP_BRIDGE_DATA) ALOGI("******** IQPorting_MasterBridgeWrite return IQ_PORTING_IO_WOULDBLOCK");
        *ioLen = 0;
        return IQ_PORTING_IO_WOULDBLOCK;
    } else if (rVal < 0) {
        if (DUMP_BRIDGE_DATA) ALOGI("******** IQPorting_MasterBridgeWrite return IQ_PORTING_ERROR");
        *ioLen = 0;
        return IQ_PORTING_ERROR;
    }/* else if (rVal < req_size) {
        mbip->write_len = rVal;
        ALOGI("******** IQPorting_MasterBridgeWrite IQ_PORTING_IO_ASYNC_PENDING --> current write=%ld",rVal);
        return IQ_PORTING_IO_ASYNC_PENDING;
    }*/
    if (DUMP_BRIDGE_DATA) ALOGI("******** IQPorting_MasterBridgeWrite IQ_PORTING_OK --> write len=%ld",rVal);

    return IQ_PORTING_OK;
}

iq_porting_status_t IQPorting_MasterBridgeCloseImpl (IQ_VOID_PARAMLIST) {
    if (DUMP_BRIDGE_DATA) ALOGI("******** IQPorting_MasterBridgeClose");
    if (mbip->mStreamFd < 0) {
        ALOGW("Invalid stream FD while closing");
        return IQ_PORTING_OK;
    }
    set_master_bridge_closed();

    if (service->tryClose()) {
        ALOGW("cannot close(%d), errno = %d(%s)", mbip->mStreamFd, errno, strerror(errno));
        return IQ_PORTING_ERROR;
    }

    if (DUMP_BRIDGE_DATA) ALOGI("IQPorting_MasterBridgeClose(%d) successfully, return IQ_PORTING_OK", mbip->mStreamFd);
    mbip->mStreamFd = -1;
    return IQ_PORTING_OK;
}

iq_porting_status_t IQPorting_MasterBridgeShutdownImpl (IQ_VOID_PARAMLIST) {
    if (mbip->inited) {
        uninit_master_bridge_info();
    }
    if (DUMP_BRIDGE_DATA) ALOGI("IQPorting_MasterBridgeShutdown, return IQ_PORTING_OK");
    return IQ_PORTING_OK;
}

void IQPorting_LoggingEnabledListenerImpl(bool loggingEnabled) {
    if (loggingEnabled == DUMP_BRIDGE_DATA) return;
    if (DUMP_BRIDGE_DATA) ALOGI("IQPorting_LoggingEnabledListener, loggingEnabled=%d",loggingEnabled);
    DUMP_BRIDGE_DATA = loggingEnabled;
    service = IIqiBridge::getService();
    if (service != nullptr) {
        service->setLoggingEnabled(loggingEnabled);
    }
    return;
}

/*


void bridge_cb_to_app(	void* callbackData, iq_io_event_t ioEvent,
               unsigned long ioParam, iq_porting_status_t ioError )
{
    ALOGI("*******************App: bridge cb from iqi bridge");
    return;
}

// test main
int main() 
{
    ALOGI("******************************************************");
    int ret = IQPorting_MasterBridgeInitialize();

    if (ret == 0) {
        ret = IQPorting_MasterBridgeOpen(bridge_cb_to_app, NULL);
        if(ret<0)
        {
            ALOGE("IQPorting_MasterBridgeOpen failed, main func exit");
            exit(0);
        }
    }

    sleep(1);

    char* buff[WR_BRIDGE_BUFFER_SIZE];

    char buf1[] = {'H','e','l','l','o','\0'};
    char buf2[] = {'H','u','i','l','i','n','\0'};

    const void *wr1 = &buf1;
    const void *wr2 = &buf2;
    unsigned long * ioLen1= (unsigned long *)malloc(sizeof(unsigned long)*1);
    unsigned long * ioLen2=(unsigned long *)malloc(sizeof(unsigned long)*1);
    unsigned long * readLen=(unsigned long *)malloc(sizeof(unsigned long)*1);
    *ioLen1 = (unsigned long)sizeof(buf1);
    *ioLen2 = (unsigned long)sizeof(buf2);
    *readLen = WR_BRIDGE_BUFFER_SIZE;

    ALOGI("client main function called, write buffer start");
    ALOGI("write buff2");
    ret = IQPorting_MasterBridgeWrite(wr1,ioLen1);
    sleep(1);
    ret = IQPorting_MasterBridgeRead(buff,readLen);

    sleep(1);
    ALOGI("write buff2");
    ret = IQPorting_MasterBridgeWrite(wr2,ioLen2);
    sleep(1);

    *readLen = WR_BRIDGE_BUFFER_SIZE;
    ret = IQPorting_MasterBridgeRead(buff,readLen);

    sleep(1);
    ret = IQPorting_MasterBridgeClose();
    free(ioLen1);
    free(ioLen2);
    free(readLen);
    ALOGI("******************************************************\n");
    return ret;
}*/

#endif
