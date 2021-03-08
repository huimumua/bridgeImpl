#define LOG_TAG "vendor.tct.iqibridge@1.0::IqiBridgeEventCallback"

#include <log/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <hidl/Static.h>
#include <hwbinder/ProcessState.h>
#include <utils/Trace.h>
#include <android/hidl/manager/1.0/IServiceManager.h>
#include <vendor/tct/iqibridge/1.0/BpHwIqiBridgeEventCallback.h>
#include <vendor/tct/iqibridge/1.0/BnHwIqiBridgeEventCallback.h>
#include <vendor/tct/iqibridge/1.0/BsIqiBridgeEventCallback.h>
#include <android/hidl/base/1.0/BpHwBase.h>
#include <hidl/ServiceManagement.h>

namespace vendor {
namespace tct {
namespace iqibridge {
namespace V1_0 {

const char* IIqiBridgeEventCallback::descriptor("vendor.tct.iqibridge@1.0::IIqiBridgeEventCallback");

__attribute__((constructor)) static void static_constructor() {
    ::android::hardware::details::getBnConstructorMap().set(IIqiBridgeEventCallback::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hardware::IBinder> {
                return new BnHwIqiBridgeEventCallback(static_cast<IIqiBridgeEventCallback *>(iIntf));
            });
    ::android::hardware::details::getBsConstructorMap().set(IIqiBridgeEventCallback::descriptor,
            [](void *iIntf) -> ::android::sp<::android::hidl::base::V1_0::IBase> {
                return new BsIqiBridgeEventCallback(static_cast<IIqiBridgeEventCallback *>(iIntf));
            });
};

__attribute__((destructor))static void static_destructor() {
    ::android::hardware::details::getBnConstructorMap().erase(IIqiBridgeEventCallback::descriptor);
    ::android::hardware::details::getBsConstructorMap().erase(IIqiBridgeEventCallback::descriptor);
};

// Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
// no default implementation for: ::android::hardware::Return<void> IIqiBridgeEventCallback::sendMsgToClient(int64_t eventId, const ::android::hardware::hidl_vec<uint8_t>& outBuffer, int64_t bufferLen)

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> IIqiBridgeEventCallback::interfaceChain(interfaceChain_cb _hidl_cb){
    _hidl_cb({
        ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback::descriptor,
        ::android::hidl::base::V1_0::IBase::descriptor,
    });
    return ::android::hardware::Void();}

::android::hardware::Return<void> IIqiBridgeEventCallback::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    (void)fd;
    (void)options;
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IIqiBridgeEventCallback::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    _hidl_cb(::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback::descriptor);
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IIqiBridgeEventCallback::getHashChain(getHashChain_cb _hidl_cb){
    _hidl_cb({
        (uint8_t[32]){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} /* 0000000000000000000000000000000000000000000000000000000000000000 */,
        (uint8_t[32]){236,127,215,158,208,45,250,133,188,73,148,38,173,174,62,190,35,239,5,36,243,205,105,87,19,147,36,184,59,24,202,76} /* ec7fd79ed02dfa85bc499426adae3ebe23ef0524f3cd6957139324b83b18ca4c */});
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IIqiBridgeEventCallback::setHALInstrumentation(){
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IIqiBridgeEventCallback::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    (void)cookie;
    return (recipient != nullptr);
}

::android::hardware::Return<void> IIqiBridgeEventCallback::ping(){
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IIqiBridgeEventCallback::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hidl::base::V1_0::DebugInfo info = {};
    info.pid = -1;
    info.ptr = 0;
    info.arch = 
    #if defined(__LP64__)
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_64BIT
    #else
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_32BIT
    #endif
    ;
    _hidl_cb(info);
    return ::android::hardware::Void();
}

::android::hardware::Return<void> IIqiBridgeEventCallback::notifySyspropsChanged(){
    ::android::report_sysprop_change();
    return ::android::hardware::Void();
}

::android::hardware::Return<bool> IIqiBridgeEventCallback::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    return (recipient != nullptr);
}


::android::hardware::Return<::android::sp<::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback>> IIqiBridgeEventCallback::castFrom(const ::android::sp<::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback>& parent, bool /* emitError */) {
    return parent;
}

::android::hardware::Return<::android::sp<::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback>> IIqiBridgeEventCallback::castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError) {
    return ::android::hardware::details::castInterface<IIqiBridgeEventCallback, ::android::hidl::base::V1_0::IBase, BpHwIqiBridgeEventCallback>(
            parent, "vendor.tct.iqibridge@1.0::IIqiBridgeEventCallback", emitError);
}

BpHwIqiBridgeEventCallback::BpHwIqiBridgeEventCallback(const ::android::sp<::android::hardware::IBinder> &_hidl_impl)
        : BpInterface<IIqiBridgeEventCallback>(_hidl_impl),
          ::android::hardware::details::HidlInstrumentor("vendor.tct.iqibridge@1.0", "IIqiBridgeEventCallback") {
}

// Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
::android::hardware::Return<void> BpHwIqiBridgeEventCallback::_hidl_sendMsgToClient(::android::hardware::IInterface *_hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int64_t eventId, const ::android::hardware::hidl_vec<uint8_t>& outBuffer, int64_t bufferLen) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this_instrumentor->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this_instrumentor->getInstrumentationCallbacks();
    #else
    (void) _hidl_this_instrumentor;
    #endif // __ANDROID_DEBUGGABLE__
    ::android::ScopedTrace PASTE(___tracer, __LINE__) (ATRACE_TAG_HAL, "HIDL::IIqiBridgeEventCallback::sendMsgToClient::client");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&eventId);
        _hidl_args.push_back((void *)&outBuffer);
        _hidl_args.push_back((void *)&bufferLen);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_ENTRY, "vendor.tct.iqibridge", "1.0", "IIqiBridgeEventCallback", "sendMsgToClient", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Parcel _hidl_data;
    ::android::hardware::Parcel _hidl_reply;
    ::android::status_t _hidl_err;
    ::android::hardware::Status _hidl_status;

    _hidl_err = _hidl_data.writeInterfaceToken(BpHwIqiBridgeEventCallback::descriptor);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt64(eventId);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl_outBuffer_parent;

    _hidl_err = _hidl_data.writeBuffer(&outBuffer, sizeof(outBuffer), &_hidl_outBuffer_parent);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    size_t _hidl_outBuffer_child;

    _hidl_err = ::android::hardware::writeEmbeddedToParcel(
            outBuffer,
            &_hidl_data,
            _hidl_outBuffer_parent,
            0 /* parentOffset */, &_hidl_outBuffer_child);

    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = _hidl_data.writeInt64(bufferLen);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::IInterface::asBinder(_hidl_this)->transact(1 /* sendMsgToClient */, _hidl_data, &_hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    _hidl_err = ::android::hardware::readFromParcel(&_hidl_status, _hidl_reply);
    if (_hidl_err != ::android::OK) { goto _hidl_error; }

    if (!_hidl_status.isOk()) { return _hidl_status; }

    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::CLIENT_API_EXIT, "vendor.tct.iqibridge", "1.0", "IIqiBridgeEventCallback", "sendMsgToClient", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>();

_hidl_error:
    _hidl_status.setFromStatusT(_hidl_err);
    return ::android::hardware::Return<void>(_hidl_status);
}


// Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
::android::hardware::Return<void> BpHwIqiBridgeEventCallback::sendMsgToClient(int64_t eventId, const ::android::hardware::hidl_vec<uint8_t>& outBuffer, int64_t bufferLen){
    ::android::hardware::Return<void>  _hidl_out = ::vendor::tct::iqibridge::V1_0::BpHwIqiBridgeEventCallback::_hidl_sendMsgToClient(this, this, eventId, outBuffer, bufferLen);

    return _hidl_out;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BpHwIqiBridgeEventCallback::interfaceChain(interfaceChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwIqiBridgeEventCallback::debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_debug(this, this, fd, options);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwIqiBridgeEventCallback::interfaceDescriptor(interfaceDescriptor_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_interfaceDescriptor(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwIqiBridgeEventCallback::getHashChain(getHashChain_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getHashChain(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwIqiBridgeEventCallback::setHALInstrumentation(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_setHALInstrumentation(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwIqiBridgeEventCallback::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie){
    ::android::hardware::ProcessState::self()->startThreadPool();
    ::android::hardware::hidl_binder_death_recipient *binder_recipient = new ::android::hardware::hidl_binder_death_recipient(recipient, cookie, this);
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    _hidl_mDeathRecipients.push_back(binder_recipient);
    return (remote()->linkToDeath(binder_recipient) == ::android::OK);
}

::android::hardware::Return<void> BpHwIqiBridgeEventCallback::ping(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_ping(this, this);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwIqiBridgeEventCallback::getDebugInfo(getDebugInfo_cb _hidl_cb){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_getDebugInfo(this, this, _hidl_cb);

    return _hidl_out;
}

::android::hardware::Return<void> BpHwIqiBridgeEventCallback::notifySyspropsChanged(){
    ::android::hardware::Return<void>  _hidl_out = ::android::hidl::base::V1_0::BpHwBase::_hidl_notifySyspropsChanged(this, this);

    return _hidl_out;
}

::android::hardware::Return<bool> BpHwIqiBridgeEventCallback::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient){
    std::unique_lock<std::mutex> lock(_hidl_mMutex);
    for (auto it = _hidl_mDeathRecipients.rbegin();it != _hidl_mDeathRecipients.rend();++it) {
        if ((*it)->getRecipient() == recipient) {
            ::android::status_t status = remote()->unlinkToDeath(*it);
            _hidl_mDeathRecipients.erase(it.base()-1);
            return status == ::android::OK;
        }
    }
    return false;
}


BnHwIqiBridgeEventCallback::BnHwIqiBridgeEventCallback(const ::android::sp<IIqiBridgeEventCallback> &_hidl_impl)
        : ::android::hidl::base::V1_0::BnHwBase(_hidl_impl, "vendor.tct.iqibridge@1.0", "IIqiBridgeEventCallback") { 
            _hidl_mImpl = _hidl_impl;
            auto prio = ::android::hardware::details::gServicePrioMap->get(_hidl_impl, {SCHED_NORMAL, 0});
            mSchedPolicy = prio.sched_policy;
            mSchedPriority = prio.prio;
            setRequestingSid(::android::hardware::details::gServiceSidMap->get(_hidl_impl, false));
}

BnHwIqiBridgeEventCallback::~BnHwIqiBridgeEventCallback() {
    ::android::hardware::details::gBnMap->eraseIfEqual(_hidl_mImpl.get(), this);
}

// Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
::android::status_t BnHwIqiBridgeEventCallback::_hidl_sendMsgToClient(
        ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        TransactCallback _hidl_cb) {
    #ifdef __ANDROID_DEBUGGABLE__
    bool mEnableInstrumentation = _hidl_this->isInstrumentationEnabled();
    const auto &mInstrumentationCallbacks = _hidl_this->getInstrumentationCallbacks();
    #endif // __ANDROID_DEBUGGABLE__

    ::android::status_t _hidl_err = ::android::OK;
    if (!_hidl_data.enforceInterface(BnHwIqiBridgeEventCallback::Pure::descriptor)) {
        _hidl_err = ::android::BAD_TYPE;
        return _hidl_err;
    }

    int64_t eventId;
    const ::android::hardware::hidl_vec<uint8_t>* outBuffer;
    int64_t bufferLen;

    _hidl_err = _hidl_data.readInt64(&eventId);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    size_t _hidl_outBuffer_parent;

    _hidl_err = _hidl_data.readBuffer(sizeof(*outBuffer), &_hidl_outBuffer_parent,  reinterpret_cast<const void **>(&outBuffer));

    if (_hidl_err != ::android::OK) { return _hidl_err; }

    size_t _hidl_outBuffer_child;

    _hidl_err = ::android::hardware::readEmbeddedFromParcel(
            const_cast<::android::hardware::hidl_vec<uint8_t> &>(*outBuffer),
            _hidl_data,
            _hidl_outBuffer_parent,
            0 /* parentOffset */, &_hidl_outBuffer_child);

    if (_hidl_err != ::android::OK) { return _hidl_err; }

    _hidl_err = _hidl_data.readInt64(&bufferLen);
    if (_hidl_err != ::android::OK) { return _hidl_err; }

    atrace_begin(ATRACE_TAG_HAL, "HIDL::IIqiBridgeEventCallback::sendMsgToClient::server");
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        _hidl_args.push_back((void *)&eventId);
        _hidl_args.push_back((void *)outBuffer);
        _hidl_args.push_back((void *)&bufferLen);
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_ENTRY, "vendor.tct.iqibridge", "1.0", "IIqiBridgeEventCallback", "sendMsgToClient", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    ::android::hardware::Return<void> _hidl_ret = static_cast<IIqiBridgeEventCallback*>(_hidl_this->getImpl().get())->sendMsgToClient(eventId, *outBuffer, bufferLen);

    (void) _hidl_cb;

    atrace_end(ATRACE_TAG_HAL);
    #ifdef __ANDROID_DEBUGGABLE__
    if (UNLIKELY(mEnableInstrumentation)) {
        std::vector<void *> _hidl_args;
        for (const auto &callback: mInstrumentationCallbacks) {
            callback(InstrumentationEvent::SERVER_API_EXIT, "vendor.tct.iqibridge", "1.0", "IIqiBridgeEventCallback", "sendMsgToClient", &_hidl_args);
        }
    }
    #endif // __ANDROID_DEBUGGABLE__

    _hidl_ret.assertOk();
    ::android::hardware::writeToParcel(::android::hardware::Status::ok(), _hidl_reply);

    return _hidl_err;
}


// Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.

// Methods from ::android::hidl::base::V1_0::IBase follow.
::android::hardware::Return<void> BnHwIqiBridgeEventCallback::ping() {
    return ::android::hardware::Void();
}
::android::hardware::Return<void> BnHwIqiBridgeEventCallback::getDebugInfo(getDebugInfo_cb _hidl_cb) {
    ::android::hidl::base::V1_0::DebugInfo info = {};
    info.pid = ::android::hardware::details::getPidIfSharable();
    info.ptr = ::android::hardware::details::debuggable()? reinterpret_cast<uint64_t>(this) : 0;
    info.arch = 
    #if defined(__LP64__)
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_64BIT
    #else
    ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_32BIT
    #endif
    ;
    _hidl_cb(info);
    return ::android::hardware::Void();
}

::android::status_t BnHwIqiBridgeEventCallback::onTransact(
        uint32_t _hidl_code,
        const ::android::hardware::Parcel &_hidl_data,
        ::android::hardware::Parcel *_hidl_reply,
        uint32_t _hidl_flags,
        TransactCallback _hidl_cb) {
    ::android::status_t _hidl_err = ::android::OK;

    switch (_hidl_code) {
        case 1 /* sendMsgToClient */:
        {
            bool _hidl_is_oneway = _hidl_flags & 1u /* oneway */;
            if (_hidl_is_oneway != false) {
                return ::android::UNKNOWN_ERROR;
            }

            _hidl_err = ::vendor::tct::iqibridge::V1_0::BnHwIqiBridgeEventCallback::_hidl_sendMsgToClient(this, _hidl_data, _hidl_reply, _hidl_cb);
            break;
        }

        default:
        {
            return ::android::hidl::base::V1_0::BnHwBase::onTransact(
                    _hidl_code, _hidl_data, _hidl_reply, _hidl_flags, _hidl_cb);
        }
    }

    if (_hidl_err == ::android::UNEXPECTED_NULL) {
        _hidl_err = ::android::hardware::writeToParcel(
                ::android::hardware::Status::fromExceptionCode(::android::hardware::Status::EX_NULL_POINTER),
                _hidl_reply);
    }return _hidl_err;
}

BsIqiBridgeEventCallback::BsIqiBridgeEventCallback(const ::android::sp<::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback> impl) : ::android::hardware::details::HidlInstrumentor("vendor.tct.iqibridge@1.0", "IIqiBridgeEventCallback"), mImpl(impl) {
    mOnewayQueue.start(3000 /* similar limit to binderized */);
}

::android::hardware::Return<void> BsIqiBridgeEventCallback::addOnewayTask(std::function<void(void)> fun) {
    if (!mOnewayQueue.push(fun)) {
        return ::android::hardware::Status::fromExceptionCode(
                ::android::hardware::Status::EX_TRANSACTION_FAILED,
                "Passthrough oneway function queue exceeds maximum size.");
    }
    return ::android::hardware::Status();
}

::android::sp<IIqiBridgeEventCallback> IIqiBridgeEventCallback::tryGetService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwIqiBridgeEventCallback>(serviceName, false, getStub);
}

::android::sp<IIqiBridgeEventCallback> IIqiBridgeEventCallback::getService(const std::string &serviceName, const bool getStub) {
    return ::android::hardware::details::getServiceInternal<BpHwIqiBridgeEventCallback>(serviceName, true, getStub);
}

::android::status_t IIqiBridgeEventCallback::registerAsService(const std::string &serviceName) {
    return ::android::hardware::details::registerAsServiceInternal(this, serviceName);
}

bool IIqiBridgeEventCallback::registerForNotifications(
        const std::string &serviceName,
        const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification) {
    const ::android::sp<::android::hidl::manager::V1_0::IServiceManager> sm
            = ::android::hardware::defaultServiceManager();
    if (sm == nullptr) {
        return false;
    }
    ::android::hardware::Return<bool> success =
            sm->registerForNotifications("vendor.tct.iqibridge@1.0::IIqiBridgeEventCallback",
                    serviceName, notification);
    return success.isOk() && success;
}

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");

}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor
