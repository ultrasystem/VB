cmd_fs/exfat/exfat_fs.ko := /arm/android/tools/linaro-4.7/bin/arm-linux-androideabi-ld -EL -r  -T /arm/android/SG3X/kernel/scripts/module-common.lds --build-id  -o fs/exfat/exfat_fs.ko fs/exfat/exfat_fs.o fs/exfat/exfat_fs.mod.o
