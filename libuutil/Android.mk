LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
APP_PLATFORM := android-16
LOCAL_CFLAGS += -fPIC
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/extrainclude
LOCAL_MODULE    := uutil
LOCAL_SRC_FILES := \
	agetline.c estrtol.c estrtoul.c getline.c mntent.c proc.c sysinfo.S tty.c
include $(BUILD_STATIC_LIBRARY)
