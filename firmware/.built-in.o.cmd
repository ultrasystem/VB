cmd_firmware/built-in.o :=  /arm/android/tools/linaro-4.7/bin/arm-linux-androideabi-ld -EL    -r -o firmware/built-in.o firmware/SlimISP_ZD.bin.gen.o firmware/SlimISP_GD.bin.gen.o firmware/tsp_melfas/CORE.fw.gen.o firmware/tsp_melfas/PRIV.fw.gen.o firmware/tsp_melfas/PUBL.fw.gen.o 
