LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := c4pkg_hash
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES  := \
    src/sha.c \
    src/c4pkg_hash_sha1.c \

CPPFLAGS += -std=c11

include $(BUILD_STATIC_LIBRARY)