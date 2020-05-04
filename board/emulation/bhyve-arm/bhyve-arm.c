// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2020 Andrew Turner
 */

#include <common.h>
#include <dm.h>
#include <fdtdec.h>
#include <virtio.h>

#include <asm/armv8/mmu.h>

DECLARE_GLOBAL_DATA_PTR;

static struct mm_region bhyve_arm64_mem_map[] = {
	{
		/* Peripherals */
		.virt = 0x10000UL,
		.phys = 0x10000UL,
		.size = 0x1000ul,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* GICv3 */
		.virt = 0x2f000000UL,
		.phys = 0x2f000000UL,
		.size = 0x10000ul,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* GICv3 */
		.virt = 0x2f100000UL,
		.phys = 0x2f100000UL,
		.size = 0x200000ul,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* PCI */
		.virt = 0xa0000000UL,
		.phys = 0xa0000000UL,
		.size = 0x50000000ul,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* RAM */
		.virt = 0x100000000UL,
		.phys = 0x100000000UL,
		.size = 252UL * SZ_1G,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = bhyve_arm64_mem_map;

void *board_fdt_blob_setup(int *err)
{
	/* Return the DTB pointer from the host */
	*err = 0;
	/* XXX: Pass in the address from the host */
	return (void *)0x100100000;
}

int board_init(void)
{

	return 0;
}

int board_late_init(void)
{
	/*
	 * Make sure virtio bus is enumerated so that peripherals
	 * on the virtio bus can be discovered by their drivers
	 */
	virtio_init();

	return 0;
}

int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}
