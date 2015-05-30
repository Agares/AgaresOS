OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

SECTIONS {
	. = 0x00100000;

	.text ALIGN(0x1000) : {
		*(.text)
	}

	.data ALIGN(0x1000) : {
		*(.data)
	}

	.rodata ALIGN(0x1000) : {
		*(.rodata)
	}

	.bss ALIGN(0x1000) : {
		bss_start = .;
		*(COMMON)
		*(.bss)
		bss_end = .;
	}
	
	/DISCARD/ : {
		*(.comment)
	}
}
