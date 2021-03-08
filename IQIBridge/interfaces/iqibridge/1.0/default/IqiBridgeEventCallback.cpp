// FIXME: your file license if you have one

#include "IqiBridgeEventCallback.h"

namespace vendor {
namespace tct {
namespace iqibridge {
namespace V1_0 {
namespace implementation {

// Methods from ::vendor::tct::iqibridge::V1_0::IIqiBridgeEventCallback follow.
Return<void> IqiBridgeEventCallback::sendMsgToClient(int64_t eventId, const hidl_vec<uint8_t>& outBuffer, int64_t bufferLen) {
    // TODO implement
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

IIqiBridgeEventCallback* HIDL_FETCH_IIqiBridgeEventCallback(const char* /* name */) {
    return new IqiBridgeEventCallback();
}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor
