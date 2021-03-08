#ifndef HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_BNHWIQIBRIDGEEVENTCALLBACK_H
#define HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_BNHWIQIBRIDGEEVENTCALLBACK_H

#include <vendor/tct/iqibridge/1.0/IHwIqiBridgeEventCallback.h>

namespace vendor {
namespace tct {
namespace iqibridge {
namespace V1_0 {

struct BnHwIqiBridgeEventCallback : public ::android::hidl::base::V1_0::BnHwBase {
    explicit BnHwIqiBridgeEventCallback(const ::android::sp<IIqiBridgeEventCallback> &_hidl_impl);
    explicit BnHwIqiBridgeEventCallback(const ::android::sp<IIqiBridgeEventCallback> &_hidl_impl, const std::string& HidlInstrumentor_package, const std::string& HidlInstrumentor_interface);

    virtual ~BnHwIqiBridgeEventCallback();

    ::android::status_t onTransact(
            uint32_t _hidl_code,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            uint32_t _hidl_flags = 0,
            TransactCallback _hidl_cb = nullptr) override;


    /**
     * The pure class is what this class wraps.
     */
    typedef IIqiBridgeEventCallback Pure;

    /**
     * Type tag for use in template logic that indicates this is a 'native' class.
     */
    typedef android::hardware::details::bnhw_tag _hidl_tag;

    ::android::sp<IIqiBridgeEventCallback> getImpl() { return _hidl_mImpl; }
    // Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
    static ::android::status_t _hidl_sendMsgToClient(
            ::android::hidl::base::V1_0::BnHwBase* _hidl_this,
            const ::android::hardware::Parcel &_hidl_data,
            ::android::hardware::Parcel *_hidl_reply,
            TransactCallback _hidl_cb);



private:
    // Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> ping();
    using getDebugInfo_cb = ::android::hidl::base::V1_0::IBase::getDebugInfo_cb;
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb);

    ::android::sp<IIqiBridgeEventCallback> _hidl_mImpl;
};

}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor

#endif  // HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_BNHWIQIBRIDGEEVENTCALLBACK_H
