# Block device driver for SD card supported by K64 platforms
This driver implements BlockDevice class introduced with mbed OS 5.4 for SD card running in SD bus mode on K64 platforms which support it.

ARM mbed team also releases an official SD driver, but it supports SPI bus mode rather than SD bus mode.

## Use with FAT file system

The SD file system example is cloned from the FAT file system example released by ARM mbed team and is modified to use this SD block device to back the FAT file system.

## Support platforms
- FRDM-K64F

## Notice
1. You have to replace the mbed OS's sdhc driver by the NXP SDK's. They are in `./sd-driver-sd/driver-files-replacing/` folder
	- `mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_sdhc.c.file`
	- `mbed-os/targets/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers/fsl_sdhc.h.file`