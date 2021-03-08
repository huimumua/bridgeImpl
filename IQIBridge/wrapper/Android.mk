ifeq ($(TCT_TARGET_IQI),true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libiqi_bridge
LOCAL_SRC_FILES := IQPortingMasterBridge_Android.cpp
LOCAL_LDLIBS    += -llog
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include

LOCAL_SDK_VERSION := current
LOCAL_NDK_STL_VARIANT := c++_shared

LOCAL_MODULE_PATH :=$(TARGET_OUT)/priv-app/IQI/lib/arm

include $(BUILD_SHARED_LIBRARY)
endif
