LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := c4pkg_zip

LOCAL_C_INCLUDES := \
   $(LOCAL_PATH)/../../prebuilt/include \
   $(LOCAL_PATH)/../c4pkg_utils/include \
   $(LOCAL_PATH)/include \

LOCAL_SRC_FILES := \
    src/zipfile.c \
    src/centraldir.c \
    src/c4pkg_zip.c

LOCAL_LDLIBS := -pie \
   -L$(LOCAL_PATH)/../../prebuilt/lib \
		-lz \
  	-lm

include $(BUILD_STATIC_LIBRARY)