LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

PATH_PRE := $(LOCAL_PATH)/../../prebuilt

LOCAL_MODULE := c4pkg_net

LOCAL_C_INCLUDES := \
   $(LOCAL_PATH)/include \
   $(PATH_PRE)/include \

LOCAL_SRC_FILES := src/c4pkg_download.c

LOCAL_LDLIBS := \
   -L$(PATH_PRE)/lib \
   -lc4pkg_curl \
   -lc4pkg_ssl \
   -lc4pkg_crypto \
		-lz \
  	-lm

include $(BUILD_STATIC_LIBRARY)