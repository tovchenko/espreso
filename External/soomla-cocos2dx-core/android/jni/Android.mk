LOCAL_PATH := $(call my-dir)

# cocos2dx-soomla-common
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_soomla_common_static
LOCAL_MODULE_FILENAME := libcocos2dxsoomlacommon



srcrootpath := $(LOCAL_PATH)/../../Soomla

dirs := $(shell find $(srcrootpath) -type d)

cppfilestemp1 := $(shell find $(dirs) -name *.cpp)
cppfilestemp2 := $(sort $(cppfilestemp1))
cppfiles := $(subst $(LOCAL_PATH)/,,$(cppfilestemp2))

LOCAL_SRC_FILES := \
		   $(cppfiles)

LOCAL_C_INCLUDES := $(dirs)



LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += jansson_static


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../..
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Soomla
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Soomla/domain
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Soomla/rewards

include $(BUILD_STATIC_LIBRARY)

$(call import-module, ../espreso/External/jansson)
