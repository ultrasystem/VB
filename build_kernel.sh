#!/bin/sh
export KERNELDIR=`readlink -f .`
export RAMFS_SOURCE=`readlink -f $KERNELDIR/../ramdisk`
export PARENT_DIR=`readlink -f ..`
export USE_SEC_FIPS_MODE=true
export CROSS_COMPILE=/arm/android/tools/linaro-4.7/bin/arm-linux-androideabi-

if [ "${1}" != "" ];then
  export KERNELDIR=`readlink -f ${1}`
fi

RAMFS_TMP="/tmp/ramfs-ultrakernel"

if [ ! -f $KERNELDIR/.config ];
then
  make -j4 ultrakernel_defconfig
fi

. $KERNELDIR/.config

export ARCH=arm

cd $KERNELDIR/
make -j4 || exit 1

#remove previous ramfs files
rm -rf $RAMFS_TMP
rm -rf $RAMFS_TMP.cpio
rm -rf $RAMFS_TMP.cpio.gz
#copy ramfs files to tmp directory
cp -ax $RAMFS_SOURCE $RAMFS_TMP
#clear git repositories in ramfs
find $RAMFS_TMP -name .git -exec rm -rf {} \;
#remove empty directory placeholders
find $RAMFS_TMP -name EMPTY_DIRECTORY -exec rm -rf {} \;
rm -rf $RAMFS_TMP/tmp/*
#remove mercurial repository
rm -rf $RAMFS_TMP/.hg
#copy modules into ramfs
mkdir -p $INITRAMFS/lib/modules
# mv -f drivers/media/video/samsung/mali_r3p0_lsi/mali.ko drivers/media/video/samsung/mali_r3p0_lsi/mali_r3p0_lsi.ko
# mv -f drivers/net/wireless/bcmdhd.cm/dhd.ko drivers/net/wireless/bcmdhd.cm/dhd_cm.ko
find -name '*.ko' -exec cp -av {} $RAMFS_TMP/lib/modules/ \;
rm -rf ../images/system/lib/modules/*
find -name '*.ko' -exec cp -av {} ../images/system/lib/modules/ \;

${CROSS_COMPILE}strip --strip-unneeded $RAMFS_TMP/lib/modules/*

cd $RAMFS_TMP
find | fakeroot cpio -H newc -o > $RAMFS_TMP.cpio 2>/dev/null
ls -lh $RAMFS_TMP.cpio
gzip -9 $RAMFS_TMP.cpio
cd -

make -j4 zImage || exit 1

rm -f $KERNELDIR/boot.img
./mkbootimg --kernel $KERNELDIR/arch/arm/boot/zImage --ramdisk $RAMFS_TMP.cpio.gz --pagesize 2048 --cmdline console=ttySAC2,115200 --base 0x40000000 -o $KERNELDIR/boot.img

#$KERNELDIR/mkshbootimg.py $KERNELDIR/boot.img $KERNELDIR/boot.img.pre $KERNELDIR/payload.tar
#rm -f $KERNELDIR/boot.img.pre

cd ${KERNELDIR}/../output
rm -f boot.img
rm -f ultrakernel.zip
mv -f -v ${KERNELDIR}/boot.img .
cp -f -v payload.zip ultrakernel.zip
zip -v ultrakernel.zip boot.img
