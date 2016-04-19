LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := c4pkg

LOCAL_C_INCLUDES := \
   $(LOCAL_PATH)/include \
   $(LOCAL_PATH)/../../include \
   $(LOCAL_PATH)/../c4pkg_hash/include \
   $(LOCAL_PATH)/../c4pkg_net/include \
   $(LOCAL_PATH)/../c4pkg_zip/include \
   $(LOCAL_PATH)/../c4pkg_utils/include \
   $(LOCAL_PATH)/../cJSON/include \

LOCAL_SRC_FILES  := \
    src/c4pkg_common.c \
    src/c4pkg_install.c \
    src/c4pkg_remove.c \
    src/c4pkg_package.c \
    src/c4pkg_parser.c \
    src/c4pkg_list.c \
    src/c4pkg_query.c \
    src/c4pkg_schema.c \
    src/c4pkg_github.c

LOCAL_STATIC_LIBRARIES := c4pkg_net cJSON c4pkg_zip c4pkg_utils c4pkg_hash

include $(BUILD_STATIC_LIBRARY)