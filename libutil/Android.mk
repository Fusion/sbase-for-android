LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
APP_PLATFORM := android-16
LOCAL_CFLAGS += -fPIC
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/extrainclude
LOCAL_MODULE    := util
LOCAL_SRC_FILES := \
	getline.c regcomp.c regfree.c regerror.c regexec.c concat.c cp.c \
	crypt.c ealloc.c enmasse.c eprintf.c eregcomp.c estrtod.c fmemopen.c \
	fnck.c fshut.c getlines.c human.c md5.c mode.c putword.c reallocarray.c \
	recurse.c rm.c sha1.c sha256.c sha512.c strcasestr.c strlcat.c strlcpy.c \
	strsep.c strtonum.c unescape.c
include $(BUILD_STATIC_LIBRARY)
