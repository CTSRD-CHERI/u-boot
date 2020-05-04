/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2017 Tuomas Tynkkynen
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

/* Physical memory map */

#define CONFIG_SYS_SDRAM_BASE		0x100000000

#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_SDRAM_BASE + SZ_2M)

#define CONFIG_PL011_CLOCK		24000000
#define CONFIG_PL01x_PORTS		{(void *)CONFIG_SYS_SERIAL0}

#define CONFIG_SYS_SERIAL0		0x10000

#if CONFIG_IS_ENABLED(CMD_VIRTIO)
# define BOOT_TARGET_VIRTIO(func) func(VIRTIO, virtio, 0)
#else
# define BOOT_TARGET_VIRTIO(func)
#error
#endif

#define BOOT_TARGET_DEVICES(func) \
	BOOT_TARGET_VIRTIO(func)

#include <config_distro_bootcmd.h>

#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdtfile=bhyve-arm.dts\0" \
	"fdt_addr_r=0x100000000\0" \
	"kernel_addr_r=0x100200000\0" \
	BOOTENV

#endif /* __CONFIG_H */
