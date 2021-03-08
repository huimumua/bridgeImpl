ifeq ($(TCT_TARGET_IQI),true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libiqi_bridge.iqi

LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc
LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/src/*.cpp))

LOCAL_SHARED_LIBRARIES := \
    libutils \
    liblog \
    libhidlbase \
    libhardware \
    vendor.tct.iqibridge@1.0

#LOCAL_MODULE_PATH :=$(TARGET_OUT)/priv-app/IQI/lib/arm

include $(BUILD_SHARED_LIBRARY)

endif
