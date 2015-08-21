ENTRY(_start)

SECTIONS {
	. = 0xffffffff80000000;

	.text ALIGN(0x1000) : {
		*(.text)
		*(.text.*)
	}

	.data ALIGN(0x1000) : {
		*(.data)
	}

	.rodata ALIGN(0x1000) : {
		*(.rodata)
		*(.rodata.*)
	}

	.bss ALIGN(0x1000) : {
		bss_start = .;
		*(COMMON)
		*(.bss)
		bss_end = .;
	}
	
	/DISCARD/ : {
		*(.comment)
		*(.eh_frame)
	}
}
