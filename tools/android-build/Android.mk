# include $(call all-subdir-makefiles)

LOCAL_PATH := $(call my-dir)

subdirs := $(addprefix $(LOCAL_PATH)/,$(addsuffix /Android.mk, \
		src \
		deps/apollo_getopt \
		deps/c4pkg \
		deps/c4pkg_hash \
		deps/c4pkg_net \
		deps/c4pkg_utils \
		deps/c4pkg_zip \
		deps/cJSON \
	))

include $(subdirs)