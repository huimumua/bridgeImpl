#define LOG_TAG "vendor.tct.iqibridge@1.0::types"

#include <log/log.h>
#include <cutils/trace.h>
#include <hidl/HidlTransportSupport.h>

#include <hidl/Static.h>
#include <hwbinder/ProcessState.h>
#include <utils/Trace.h>
#include <vendor/tct/iqibridge/1.0/types.h>
#include <vendor/tct/iqibridge/1.0/hwtypes.h>

namespace vendor {
namespace tct {
namespace iqibridge {
namespace V1_0 {

static_assert(sizeof(::android::hardware::MQDescriptor<char, ::android::hardware::kSynchronizedReadWrite>) == 32, "wrong size");
static_assert(sizeof(::android::hardware::hidl_handle) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_memory) == 40, "wrong size");
static_assert(sizeof(::android::hardware::hidl_string) == 16, "wrong size");
static_assert(sizeof(::android::hardware::hidl_vec<char>) == 16, "wrong size");

}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor
