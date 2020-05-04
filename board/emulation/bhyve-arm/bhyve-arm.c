// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2020 Andrew Turner
 */

#include <common.h>

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
		.size = 0x40000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = bhyve_arm64_mem_map;

int board_init(void)
{

	return 0;
}

int dram_init(void)
{

	gd->ram_size = 0x40000000UL;
	return 0;
}
