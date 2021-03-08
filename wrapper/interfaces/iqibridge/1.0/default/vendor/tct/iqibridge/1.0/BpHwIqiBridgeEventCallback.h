#ifndef HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_BPHWIQIBRIDGEEVENTCALLBACK_H
#define HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_BPHWIQIBRIDGEEVENTCALLBACK_H

#include <hidl/HidlTransportSupport.h>

#include <vendor/tct/iqibridge/1.0/IHwIqiBridgeEventCallback.h>

namespace vendor {
namespace tct {
namespace iqibridge {
namespace V1_0 {

struct BpHwIqiBridgeEventCallback : public ::android::hardware::BpInterface<IIqiBridgeEventCallback>, public ::android::hardware::details::HidlInstrumentor {
    explicit BpHwIqiBridgeEventCallback(const ::android::sp<::android::hardware::IBinder> &_hidl_impl);

    /**
     * The pure class is what this class wraps.
     */
    typedef IIqiBridgeEventCallback Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'proxy' class.
     */
    typedef android::hardware::details::bphw_tag _hidl_tag;

    virtual bool isRemote() const override { return true; }

    // Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
    static ::android::hardware::Return<void>  _hidl_sendMsgToClient(::android::hardware::IInterface* _hidl_this, ::android::hardware::details::HidlInstrumentor *_hidl_this_instrumentor, int64_t eventId, const ::android::hardware::hidl_vec<uint8_t>& outBuffer, int64_t bufferLen);

    // Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
    ::android::hardware::Return<void> sendMsgToClient(int64_t eventId, const ::android::hardware::hidl_vec<uint8_t>& outBuffer, int64_t bufferLen) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;
    ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;
    ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;
    ::android::hardware::Return<void> setHALInstrumentation() override;
    ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;
    ::android::hardware::Return<void> ping() override;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;
    ::android::hardware::Return<void> notifySyspropsChanged() override;
    ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;

private:
    std::mutex _hidl_mMutex;
    std::vector<::android::sp<::android::hardware::hidl_binder_death_recipient>> _hidl_mDeathRecipients;
};

}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor

#endif  // HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_BPHWIQIBRIDGEEVENTCALLBACK_H
