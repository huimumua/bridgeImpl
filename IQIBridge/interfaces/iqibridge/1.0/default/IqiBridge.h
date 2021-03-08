// FIXME: your file license if you have one

#pragma once

#include <vendor/tct/iqibridge/1.0/IIqiBridge.h>
#include <vendor/tct/iqibridge/1.0/types.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace vendor {
namespace tct {
namespace iqibridge {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

using ::vendor::tct::iqibridge::V1_0::iq_porting_base_status;
using ::vendor::tct::iqibridge::V1_0::iq_porting_status;
using ::vendor::tct::iqibridge::V1_0::iq_porting_io_status;

struct IqiBridge : public IIqiBridge {

public:
    IqiBridge();
    ~IqiBridge();
    static IIqiBridge* getInstance();
    // Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridge follow.
    Return<int64_t> tryOpen(const sp<::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback>& cb) override;
    Return<void> tryRead(uint64_t rLen, tryRead_cb _hidl_cb) override;
    Return<int64_t> tryWrite(const hidl_vec<uint8_t>& inBuffer, uint64_t wLen) override;
    Return<int64_t> tryClose() override;
    Return<void> setLoggingEnabled(bool loggingEnabled) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
private:
    static IqiBridge* sInstance;
    void* mBridgeBuffer;

};

// FIXME: most likely delete, this is only for passthrough implementations
extern "C" IIqiBridge* HIDL_FETCH_IIqiBridge(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor
