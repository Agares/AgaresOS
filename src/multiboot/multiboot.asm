%define UINT32_MAX 4294967295

%define MULTIBOOT2_HEADER_MAGIC 0xe85250d6
%define MULTIBOOT_ARCHITECTURE_I386 0

section .multiboot-header
multiboot_header:
	; magic value
	dd MULTIBOOT2_HEADER_MAGIC
	; architecture (i386)
	dd MULTIBOOT_ARCHITECTURE_I386
	; header_length (in bytes)
	dd multiboot_header_end - multiboot_header
	; checksum
	dd UINT32_MAX-( \
		MULTIBOOT2_HEADER_MAGIC \
		+MULTIBOOT_ARCHITECTURE_I386 \
		+(multiboot_header_end - multiboot_header) \
		-1 \
	)
multiboot_header_tag_end:
	dw 0 ;type
	dw 0 ;flags
	dd 8 ;size
multiboot_header_end:
