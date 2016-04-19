LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cJSON

LOCAL_C_INCLUDES := \
   $(LOCAL_PATH)/include \
   $(LOCAL_PATH)/../../prebuilt/include \

LOCAL_SRC_FILES := \
  src/cJSON.c \
  src/cJSON_Utils.c

LOCAL_LDLIBS := -pie \
   -L$(LOCAL_PATH)/../../prebuilt/lib \
		-lz \
  	-lm

include $(BUILD_STATIC_LIBRARY)
