#!/bin/sh

adb wait-for-devices
adb push ../output/boot.img /tmp/
adb shell flash_image /dev/block/mmcblk0p5 /tmp/boot.img
adb remount
adb shell rm /system/lib/modules/*
adb push ../images/system/lib/modules/ /system/lib/modules/
adb reboot
adb wait-for-devices
adb shell dmesg > /tmp/rom.log
