cmd_drivers/cpufreq/built-in.o :=  /arm/android/tools/linaro-4.7/bin/arm-linux-androideabi-ld -EL    -r -o drivers/cpufreq/built-in.o drivers/cpufreq/cpufreq.o drivers/cpufreq/cpufreq_stats.o drivers/cpufreq/cpufreq_zzmoove.o drivers/cpufreq/cpufreq_pegasusq.o drivers/cpufreq/cpufreq_pegasusqplus.o drivers/cpufreq/cpufreq_lulzactiveq.o drivers/cpufreq/freq_table.o 
