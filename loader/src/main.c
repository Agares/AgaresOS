#include "../../common/src/early/video.h"
#include "../../common/src/libc/stdlib.h"
#include "../../common/src/early/panic.h"
#include "../../common/src/early/log.h"
#include "arch/x86/gdt.h"
#include "multiboot/tag.h"
#include "multiboot/module.h"
#include "elf/loader.h"
#include "../../common/src/paging/paging.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include "multiboot/multiboot2.h"
#pragma GCC diagnostic pop
#include <stddef.h>

void kmain(uint32_t, uint32_t);

void kmain(uint32_t magic, uint32_t multiboot_information) {
	character_color char_color = { 
		.foreground = COLOR_YELLOW,
		.background = COLOR_BLACK 
	};
 
	early_video_put_string("agos, version 0\n", char_color); 
	if(magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		EARLY_PANIC("Loaded from not multiboot-complaiant bootloader.");
	}

	x86_gdt_setup();

	struct multiboot_tag *multiboot_tags_start = (struct multiboot_tag *)(multiboot_information + 8);

	// +8 here is to skip the header (4bytes size + 4bytes reserved)
	struct multiboot_tag *tag = multiboot_find_next_tag(MULTIBOOT_TAG_TYPE_MODULE, multiboot_tags_start);

	if(tag == NULL) {
			EARLY_PANIC("Module tag not found.");
	} else {
			early_video_put_string("Module tag found at ", char_color);
			char buffer[33];
			itoa((int)tag, buffer, 16);
			early_video_put_string("0x", char_color);
			early_video_put_string(buffer, char_color);
			early_video_put_string("\n", char_color);
	}

	multiboot_module *module = multiboot_module_read_next(multiboot_tags_start);
	LOG("Multiboot module found at ");
	LOG_NUMBER_HEX((int)module->load_address);
	LOG(" with size ");
	LOG_NUMBER_DEC((int)module->size);
	LOG("\n");

	elf_loader_load((void*)module->load_address);

	for(uint64_t i = 0; i < 16*1024*1024; i+=4096) {
		paging_map_page(i, i);
	}
	paging_load_pml4();
	
	__asm__(" \
		mov %cr4, %eax \n \
		orl $(1<<5), %eax \n \
		mov %eax, %cr4 \n \
		\
		mov $0xC0000080, %ecx \n \
		rdmsr \n \
		orl $(1<<8), %eax \n \
		wrmsr \n \
		\
		mov %cr0, %eax \n \
		orl $(1<<31), %eax \n \
		mov %eax, %cr0 \n \
		");

	while(1);
}
