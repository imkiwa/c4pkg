LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := c4pkg_utils

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include 

LOCAL_SRC_FILES := \
    src/buffer_utils.c \
    src/fs_utils.c \
    src/string_utils.c

include $(BUILD_STATIC_LIBRARY)