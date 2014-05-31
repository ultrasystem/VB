cmd_arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.o := /arm/android/tools/linaro-4.7/bin/arm-linux-androideabi-gcc -Wp,-MD,arch/arm/mvp/pvtcpkm/.pvtcp_off_linux_shim.o.d  -nostdinc -isystem /arm/android/tools/linaro-4.7/bin/../lib/gcc/arm-linux-androideabi/4.7.2/include -I/arm/android/SG3X/kernel/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-exynos/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float       -DMODULE  -c -o arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.o arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.S

source_arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.o := arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.S

deps_arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.o := \
  /arm/android/SG3X/kernel/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \

arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.o: $(deps_arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.o)

$(deps_arch/arm/mvp/pvtcpkm/pvtcp_off_linux_shim.o):
