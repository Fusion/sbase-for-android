CFR_PROJECT_PATH := $(call my-dir)
LOCAL_PATH := $(CFR_PROJECT_PATH)

define cfr_add_module
    include $(CLEAR_VARS)  
    APP_PLATFORM := android-16
    LOCAL_CFLAGS += -fPIE
    LOCAL_LDFLAGS += -fPIE -pie
    LOCAL_C_INCLUDES := $(LOCAL_PATH)
    LOCAL_LDLIBS := -L$(LOCAL_PATH)/libutf/obj/local/armeabi -L$(LOCAL_PATH)/libutil/obj/local/armeabi  -L$(LOCAL_PATH)/libuutil/obj/local/armeabi -lutf -lutil -luutil
    LOCAL_MODULE    := $1
    LOCAL_SRC_FILES := $1.c
    include $(BUILD_EXECUTABLE)  
endef

module_list := \
	basename cal cat chgrp chmod chown chroot cksum cmp col cols comm cp cron \
	cut date dirname du echo env expand expr false find fold grep head kill \
	link ln logname ls md5sum mkdir mkfifo mktemp mv nice nl nohup paste \
	printenv printf pwd readlink renice rm rmdir sed seq setsid sha1sum \
	sha256sum sha512sum sleep sort split sponge strings sync tail tar tee \
	test time touch tr true tty uname unexpand uniq unlink uudecode uuencode \
	wc xargs yes \
	\
	clear df dmesg halt id \
	lsusb mknod mkswap pagesize pidof respawn stat \
	sysctl truncate watch
$(foreach module_name,$(module_list),$(eval $(call cfr_add_module,$(module_name))))
