#define LOG_TAG "vendor.tct.iqibridge@1.0-service"
 
#include <vendor/tct/iqibridge/1.0/IIqiBridge.h>
#include <vendor/tct/iqibridge/1.0/IIqiBridgeEventCallback.h>
 
#include <hidl/LegacySupport.h>
#include "IqiBridge.h"
#include "IqiBridgeEventCallback.h"
 
// Generated HIDL files
using vendor::tct::iqibridge::V1_0::IIqiBridge;
using vendor::tct::iqibridge::V1_0::implementation::IqiBridge;
 
using android::hardware::defaultPassthroughServiceImplementation;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

int main() {
#if 0
    return defaultPassthroughServiceImplementation<IIqiBridge>();
#else
    android::sp<IIqiBridge> service = new IqiBridge();
    configureRpcThreadpool(1, true /*callerWillJoin*/);
    if(android::OK !=  service->registerAsService()) {
        printf("registerAsService failed\n");
        return 1;
    }
    joinRpcThreadpool();
#endif
} 