#!/system/bin/sh

unzip sbase_bin.zip "$1" && mount -o remount,rw /system && mv "$1" /system/bin/s_"$1" && chmod +x /system/bin/s_"$1" && mount -o remount,ro /system
