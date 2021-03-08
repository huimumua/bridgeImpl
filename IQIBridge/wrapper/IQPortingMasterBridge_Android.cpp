#include "IQPortingMasterBridge.h"
#include <dlfcn.h>

#include <android/log.h>
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, "MasterBridgeWrapper", __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, "MasterBridgeWrapper", __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "MasterBridgeWrapper", __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, "MasterBridgeWrapper", __VA_ARGS__)

const char * dylib_path = "/system/lib/libiqi_bridge.iqi.so";
void * sDlHandler = NULL;

iq_porting_status_t IQPorting_MasterBridgeInitialize (IQ_VOID_PARAMLIST) {
    if (sDlHandler == NULL) {
        sDlHandler = dlopen(dylib_path, RTLD_GLOBAL | RTLD_NOW);
        if (sDlHandler == NULL) {
            ALOGE("%s, dlopen failed: %s", __FUNCTION__, dlerror());
            return IQ_PORTING_NOT_IMPLEMENTED;
        }
    }

    iq_porting_status_t (*initFunc)();
    initFunc = (iq_porting_status_t (*)())
             dlsym(sDlHandler, "IQPorting_MasterBridgeInitializeImpl");
    const char* dlsym_error = dlerror();
     if (initFunc == NULL) {
         ALOGE("IQPorting_MasterBridgeInitialize not defined or exported in %s: %s",
                dylib_path, dlsym_error);
        return IQ_PORTING_NOT_IMPLEMENTED;
    }

    return initFunc();
}

iq_porting_status_t IQPorting_MasterBridgeOpen (iq_io_callback_t callbackFunc, void *callbackData) {
    if (sDlHandler == NULL) {
        sDlHandler = dlopen(dylib_path, RTLD_GLOBAL | RTLD_NOW);
        if (sDlHandler == NULL) {
            ALOGE("%s, dlopen failed: %s", __FUNCTION__, dlerror());
            return IQ_PORTING_NOT_IMPLEMENTED;
        }
    }

    iq_porting_status_t (*openFunc)(iq_io_callback_t,void*);
    openFunc = (iq_porting_status_t (*)(iq_io_callback_t, void*))
             dlsym(sDlHandler, "IQPorting_MasterBridgeOpenImpl");
    const char* dlsym_error = dlerror();
    if (openFunc == NULL) {
        ALOGE("IQPorting_MasterBridgeOpen not defined or exported in %s: %s",
               dylib_path, dlsym_error);
        return IQ_PORTING_NOT_IMPLEMENTED;
    }

    return openFunc(callbackFunc, callbackData);
}

iq_porting_status_t IQPorting_MasterBridgeRead (void *ioBuffer, unsigned long *ioLen) {
    if (sDlHandler == NULL) {
        sDlHandler = dlopen(dylib_path, RTLD_GLOBAL | RTLD_NOW);
        if (sDlHandler == NULL) {
            ALOGE("%s, dlopen failed: %s", __FUNCTION__, dlerror());
            return IQ_PORTING_NOT_IMPLEMENTED;
        }
    }

    iq_porting_status_t (*readFunc)(void*, unsigned long*);
    readFunc = (iq_porting_status_t (*)(void*, unsigned long*))
             dlsym(sDlHandler, "IQPorting_MasterBridgeReadImpl");
    const char* dlsym_error = dlerror();
    if (readFunc == NULL) {
        ALOGE("IQPorting_MasterBridgeRead not defined or exported in %s: %s",
               dylib_path, dlsym_error);
        return IQ_PORTING_NOT_IMPLEMENTED;
    }

    return readFunc(ioBuffer, ioLen);
}

iq_porting_status_t IQPorting_MasterBridgeWrite (IQ_CONST_PARAM void *ioBuffer, unsigned long *ioLen) {
    if (sDlHandler == NULL) {
        sDlHandler = dlopen(dylib_path, RTLD_GLOBAL | RTLD_NOW);
        if (sDlHandler == NULL) {
            ALOGE("%s, dlopen failed: %s", __FUNCTION__, dlerror());
            return IQ_PORTING_NOT_IMPLEMENTED;
        }
    }

    iq_porting_status_t (*writeFunc)(IQ_CONST_PARAM void*, unsigned long*);
    writeFunc = (iq_porting_status_t (*)(IQ_CONST_PARAM void*, unsigned long*))
             dlsym(sDlHandler, "IQPorting_MasterBridgeWriteImpl");
    const char* dlsym_error = dlerror();
    if (writeFunc == NULL) {
        ALOGE("IQPorting_MasterBridgeWrite not defined or exported in %s: %s",
               dylib_path, dlsym_error);
        return IQ_PORTING_NOT_IMPLEMENTED;
    }
    return writeFunc(ioBuffer, ioLen);
}

iq_porting_status_t IQPorting_MasterBridgeClose (IQ_VOID_PARAMLIST) {
    if (sDlHandler == NULL) {
        sDlHandler = dlopen(dylib_path, RTLD_GLOBAL | RTLD_NOW);
        if (sDlHandler == NULL) {
            ALOGE("%s, dlopen failed: %s", __FUNCTION__, dlerror());
            return IQ_PORTING_NOT_IMPLEMENTED;
        }
    }

    iq_porting_status_t (*closeFunc)();
    closeFunc = (iq_porting_status_t (*)())
             dlsym(sDlHandler, "IQPorting_MasterBridgeCloseImpl");
    const char* dlsym_error = dlerror();
    if (closeFunc == NULL) {
        ALOGE("IQPorting_MasterBridgeClose not defined or exported in %s: %s",
               dylib_path, dlsym_error);
        return IQ_PORTING_NOT_IMPLEMENTED;
    }
    return closeFunc();
}

iq_porting_status_t IQPorting_MasterBridgeShutdown (IQ_VOID_PARAMLIST) {
    if (sDlHandler == NULL) {
        sDlHandler = dlopen(dylib_path, RTLD_GLOBAL | RTLD_NOW);
        if (sDlHandler == NULL) {
            ALOGE("%s, dlopen failed: %s", __FUNCTION__, dlerror());
            return IQ_PORTING_NOT_IMPLEMENTED;
        }
    }

    iq_porting_status_t (*shutdownFunc)();
    shutdownFunc = (iq_porting_status_t (*)())
             dlsym(sDlHandler, "IQPorting_MasterBridgeShutdownImpl");
    const char* dlsym_error = dlerror();
    if (shutdownFunc == NULL) {
        ALOGE("IQPorting_MasterBridgeShutdown not defined or exported in %s: %s",
               dylib_path, dlsym_error);
        return IQ_PORTING_NOT_IMPLEMENTED;
    }
    if (sDlHandler != NULL) {
        dlclose(sDlHandler);
    }
    sDlHandler = NULL;
    return shutdownFunc();
}

void IQPorting_LoggingEnabledListener (bool loggingEnabled) {
    if (sDlHandler == NULL) {
        sDlHandler = dlopen(dylib_path, RTLD_GLOBAL | RTLD_NOW);
        if (sDlHandler == NULL) {
            ALOGE("%s, dlopen failed: %s", __FUNCTION__, dlerror());
            return ;
        }
    }

    void (*logFunc)(bool);
    logFunc = (void (*)(bool))
             dlsym(sDlHandler, "IQPorting_LoggingEnabledListenerImpl");
    const char* dlsym_error = dlerror();
    if (logFunc == NULL) {
        ALOGE("IQPorting_LoggingEnabledListener not defined or exported in %s: %s",
               dylib_path, dlsym_error);
        return ;
    }
    logFunc(loggingEnabled);
}
