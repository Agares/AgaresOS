#include "early/video.h"
#include "libc/stdlib.h"
#include "early/panic.h"
#include "arch/x86/gdt.h"
#include "multiboot/tag.h"
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

	// +8 here is to skip the header (4bytes size + 4bytes reserved)
	struct multiboot_tag *tag = multiboot_find_next_tag(MULTIBOOT_TAG_TYPE_MODULE, (struct multiboot_tag *)(multiboot_information + 8));

	if(tag == NULL) {
			early_video_put_string("Module tag not found.\n", char_color);
	} else {
			early_video_put_string("Module tag found at ", char_color);
			char buffer[33];
			itoa((int)tag, buffer, 16);
			early_video_put_string("0x", char_color);
			early_video_put_string(buffer, char_color);
			early_video_put_string("\n", char_color);
	}


	x86_gdt_setup();
	
	while(1);
}
