LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := apollo_getopt
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES  := src/getopt.c

include $(BUILD_STATIC_LIBRARY)