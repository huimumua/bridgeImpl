// FIXME: your file license if you have one

#pragma once

#include <vendor/tct/iqibridge/1.0/IIqiBridgeEventCallback.h>
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

struct IqiBridgeEventCallback : public IIqiBridgeEventCallback {
    // Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
    Return<void> sendMsgToClient(int64_t eventId, const hidl_vec<uint8_t>& outBuffer, int64_t bufferLen) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
extern "C" IIqiBridgeEventCallback* HIDL_FETCH_IIqiBridgeEventCallback(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor
