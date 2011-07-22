/*
 * Linker script for CHERI MIPS.
 *
 * Author: Philip Paeps <Philip.Paeps@cl.cam.ac.uk>
 */

OUTPUT_FORMAT("elf64-tradbigmips")
OUTPUT_ARCH(mips)
ENTRY(_start)
SECTIONS
{
	. = 0x9000000040000000;

	. = ALIGN(8);
	.text : { *(.text) }

	. = ALIGN(8);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(8);
	.data : { *(.data) }

	. = .;
	_gp = ALIGN(16) +0x7ff0;

	.got  : {
	__got_start = .;
		*(.got)
	__got_end = .;
	}

	. = ALIGN(8);
	.sdata  : { *(.sdata) }

	. = .;
	.u_boot_cmd : {
	__u_boot_cmd_start = .;
	*(.u_boot_cmd)
	__u_boot_cmd_end = .;
	}

	uboot_end_data = .;
	num_got_entries = (__got_end - __got_start) >> 2;

	. = ALIGN(8);
	.sbss  : { *(.sbss) }
	.bss  : { *(.bss) . = ALIGN(8); }
	uboot_end = .;
}
