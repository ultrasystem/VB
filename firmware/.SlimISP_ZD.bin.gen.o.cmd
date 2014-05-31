cmd_firmware/SlimISP_ZD.bin.gen.o := /arm/android/tools/linaro-4.7/bin/arm-linux-androideabi-gcc -Wp,-MD,firmware/.SlimISP_ZD.bin.gen.o.d  -nostdinc -isystem /arm/android/tools/linaro-4.7/bin/../lib/gcc/arm-linux-androideabi/4.7.2/include -I/arm/android/SG3X/kernel/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-exynos/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float        -c -o firmware/SlimISP_ZD.bin.gen.o firmware/SlimISP_ZD.bin.gen.S

source_firmware/SlimISP_ZD.bin.gen.o := firmware/SlimISP_ZD.bin.gen.S

deps_firmware/SlimISP_ZD.bin.gen.o := \
  /arm/android/SG3X/kernel/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \

firmware/SlimISP_ZD.bin.gen.o: $(deps_firmware/SlimISP_ZD.bin.gen.o)

$(deps_firmware/SlimISP_ZD.bin.gen.o):
