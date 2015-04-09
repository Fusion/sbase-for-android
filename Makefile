BUILDER = ndk-build
DEPS = libutf/obj/local/armeabi/libutf.a libutil/obj/local/armeabi/libutil.a

all: ${DEPS}
	${BUILDER} NDK_PROJECT_PATH=$(CURDIR) APP_BUILD_SCRIPT=$(CURDIR)/Android.mk

clean:
	rm -rf obj && rm -rf libutf/obj && rm -rf libutil/obj && rm -rf libs

libutf/obj/local/armeabi/libutf.a:
	cd libutf && ${BUILDER} NDK_PROJECT_PATH=$(CURDIR)/libutf APP_BUILD_SCRIPT=$(CURDIR)/libutf/Android.mk NDK_APPLICATION_MK=$(CURDIR)/libutf/Application.mk

libutil/obj/local/armeabi/libutil.a:
	cd libutil && ${BUILDER} NDK_PROJECT_PATH=$(CURDIR)/libutil APP_BUILD_SCRIPT=$(CURDIR)/libutil/Android.mk NDK_APPLICATION_MK=$(CURDIR)/libutil/Application.mk

