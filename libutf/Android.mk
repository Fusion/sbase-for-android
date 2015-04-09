LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
APP_PLATFORM := android-16
LOCAL_CFLAGS += -fPIC
LOCAL_MODULE    := utf
LOCAL_SRC_FILES := \
	fgetrune.c fputrune.c isalnumrune.c isalpharune.c isblankrune.c \
	iscntrlrune.c isdigitrune.c isgraphrune.c isprintrune.c ispunctrune.c \
	isspacerune.c istitlerune.c isxdigitrune.c lowerrune.c rune.c runetype.c \
	upperrune.c utf.c utftorunestr.c
include $(BUILD_STATIC_LIBRARY)
