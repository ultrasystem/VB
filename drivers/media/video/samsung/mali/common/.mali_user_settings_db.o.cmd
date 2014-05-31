cmd_drivers/media/video/samsung/mali/common/mali_user_settings_db.o := /arm/android/tools/linaro-4.7/bin/arm-linux-androideabi-gcc -Wp,-MD,drivers/media/video/samsung/mali/common/.mali_user_settings_db.o.d  -nostdinc -isystem /arm/android/tools/linaro-4.7/bin/../lib/gcc/arm-linux-androideabi/4.7.2/include -I/arm/android/SG3X/kernel/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-exynos/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -marm -march=armv7-a -mcpu=cortex-a9 -mtune=cortex-a9 -fno-pic -O2 -marm -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -Idrivers/media/video/samsung/mali/../ump/include -Idrivers/media/video/samsung/mali/ -Idrivers/media/video/samsung/mali/include -Idrivers/media/video/samsung/mali/common -Idrivers/media/video/samsung/mali/linux -Idrivers/media/video/samsung/mali/platform -Idrivers/media/video/samsung/mali/regs -DONLY_ZBT=0 -DUSING_ZBT=0 -DUSING_MMU=1 -DUSING_OS_MEMORY=1 -DUSING_DED=0 -DUSING_UMP=0 -D_MALI_OSK_SPECIFIC_INDIRECT_MMAP -DUSING_MALI_PMU=0 -DMALI_PMM_RUNTIME_JOB_CONTROL_ON=1 -DUSING_MALI_PMM=1 -DMALI_GPU_UTILIZATION=1 -DCONFIG_MALI_MEM_SIZE= -D_MALI_OSK_SPECIFIC_INDIRECT_MMAP -DMALI_INTERNAL_TIMELINE_PROFILING_ENABLED=0 -DMALI_MAJOR_PREDEFINE=1 -DMALI_DVFS_ENABLED=1 -DUSING_MALI_PMM_EARLYSUSPEND=0 -DMALI_STATE_TRACKING=0 -DMALI_OS_MEMORY_KERNEL_BUFFER_SIZE_IN_MB=16 -DMALI_TRACEPOINTS_ENABLED=0 -DDISABLE_PP0=0 -DDISABLE_PP1=0 -DDISABLE_PP2=0 -DDISABLE_PP3=0 -DPROFILING_SKIP_PP_JOBS=0 -DPROFILING_SKIP_PP_AND_GP_JOBS=0 -DPROFILING_PRINT_L2_HITRATE_ON_GP_FINISH=0 -DMALI_PP_SCHEDULER_FORCE_NO_JOB_OVERLAP=0 -DMALI_PP_SCHEDULER_KEEP_SUB_JOB_STARTS_ALIGNED=0 -DMALI_PP_SCHEDULER_FORCE_NO_JOB_OVERLAP_BETWEEN_APPS=0 -DMALI_TIMELINE_PROFILING_ENABLED=0 -DMALI_POWER_MGMT_TEST_SUITE=0 -DMALI_OS_MEMORY_KERNEL_BUFFER_SIZE_IN_MB=16 -DMALI_UKK_HAS_IMPLICIT_MMAP_CLEANUP -DMALI_USE_UNIFIED_MEMORY_PROVIDER=1 -Idrivers/media/video/samsung/mali/linux/license/gpl -Idrivers/media/video/samsung/mali/common/pmm -DCONFIG_MALI400_GPU_UTILIZATION=1 -DUSING_MALI400 -DUSING_MALI400_L2_CACHE -DSVN_REV= -DSVN_REV_STRING=\"\"    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(mali_user_settings_db)"  -D"KBUILD_MODNAME=KBUILD_STR(mali)" -c -o drivers/media/video/samsung/mali/common/.tmp_mali_user_settings_db.o drivers/media/video/samsung/mali/common/mali_user_settings_db.c

source_drivers/media/video/samsung/mali/common/mali_user_settings_db.o := drivers/media/video/samsung/mali/common/mali_user_settings_db.c

deps_drivers/media/video/samsung/mali/common/mali_user_settings_db.o := \
  drivers/media/video/samsung/mali/common/mali_osk.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /arm/android/SG3X/kernel/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /arm/android/SG3X/kernel/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /arm/android/SG3X/kernel/arch/arm/include/asm/posix_types.h \
  drivers/media/video/samsung/mali/common/mali_kernel_memory_engine.h \
  drivers/media/video/samsung/mali/linux/mali_osk_specific.h \
  drivers/media/video/samsung/mali/common/mali_kernel_common.h \
  drivers/media/video/samsung/mali/linux/mali_uk_types.h \
  drivers/media/video/samsung/mali/linux/../include/linux/mali/mali_utgard_uk_types.h \
  drivers/media/video/samsung/mali/common/mali_user_settings_db.h \
  drivers/media/video/samsung/mali/common/mali_session.h \
  drivers/media/video/samsung/mali/common/mali_mmu_page_directory.h \
  drivers/media/video/samsung/mali/common/mali_kernel_descriptor_mapping.h \
  drivers/media/video/samsung/mali/common/mali_osk_list.h \

drivers/media/video/samsung/mali/common/mali_user_settings_db.o: $(deps_drivers/media/video/samsung/mali/common/mali_user_settings_db.o)

$(deps_drivers/media/video/samsung/mali/common/mali_user_settings_db.o):
