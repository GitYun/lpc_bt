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
    depfiles_gcc = "build\\.objs\\.\\lpc_bt.elf\\cross\\arm\\debug\\iap\\src\\FlashPrg.c.o:  iap\\src\\FlashPrg.c iap\\inc/FlashOS.H\
",
    files = {
        [[iap\src\FlashPrg.c]]
    }
}