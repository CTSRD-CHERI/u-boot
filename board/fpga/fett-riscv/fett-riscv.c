// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018, Bin Meng <bmeng.cn@gmail.com>
 * Copyright (C) 2021, Jessica Clarke <jrtc27@jrtc27.com>
 */

#include <common.h>
#include <dm.h>
#include <image.h>
#include <log.h>
#include <spl.h>
#include <init.h>
#include <virtio_types.h>
#include <virtio.h>

int board_init(void)
{
	/*
	 * Make sure virtio bus is enumerated so that peripherals
	 * on the virtio bus can be discovered by their drivers
	 */
	virtio_init();

	return 0;
}

int board_late_init(void)
{
	/* RISC-V FETT doesn't add a kernel-start to the FDT like QEMU */
	return 0;
}

#ifdef CONFIG_SPL
u32 spl_boot_device(void)
{
	/* RISC-V FETT only supports RAM as SPL boot device */
	return BOOT_DEVICE_RAM;
}
#endif

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
	/* boot using first FIT config */
	return 0;
}
#endif
