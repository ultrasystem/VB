cmd_drivers/gpio/built-in.o :=  /arm/android/tools/linaro-4.7/bin/arm-linux-androideabi-ld -EL    -r -o drivers/gpio/built-in.o drivers/gpio/gpiolib.o drivers/gpio/gpio-exynos4.o drivers/gpio/gpio-plat-samsung.o 
