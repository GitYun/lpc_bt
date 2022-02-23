{
    values = {
        [[D:\OpenFree\gcc-arm-none-eabi-10.3-2021.10\bin\arm-none-eabi-gcc]],
        {
            "-g",
            "-O0",
            "-std=c99",
            [[-ICore\CMSIS\Include]],
            [[-ICore\Device\NXP\LPC11xx\Include]],
            [[-Idrivers\inc]],
            [[-Iiap\inc]],
            "-Imain",
            "-DLPC1XXX",
            "-DFLASH_32",
            "-DARM_MATH_CM0",
            "-mcpu=cortex-m0",
            "-mthumb",
            "-std=gnu99",
            "-Wall",
            "-fstack-usage",
            "--specs=nano.specs",
            "-mfloat-abi=soft",
            "-ffunction-sections",
            "-fdata-sections",
            "-nostartfiles",
            "-nostdlib"
        }
    },
    depfiles_gcc = "build\\.objs\\.\\lpc_bt.elf\\cross\\arm\\debug\\drivers\\src\\LPC11xx_debug.c.o:  drivers\\src\\LPC11xx_debug.c drivers\\inc/lpc_types.h  Core\\Device\\NXP\\LPC11xx\\Include/lpc11xx.h Core\\CMSIS\\Include/core_cm0.h  Core\\CMSIS\\Include/core_cmInstr.h Core\\CMSIS\\Include/core_cmFunc.h  Core\\Device\\NXP\\LPC11xx\\Include/system_LPC11xx.h  drivers\\inc/lpc11xx_uart.h drivers\\inc/lpc_types.h\
",
    files = {
        [[drivers\src\LPC11xx_debug.c]]
    }
}