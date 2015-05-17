#include "early/video.h"
#include "libc/stdlib.h"
#include "early/panic.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include "multiboot/multiboot2.h"
#pragma GCC diagnostic pop

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

	struct multiboot_tag *tag;

	for(tag = (struct multiboot_tag *)(multiboot_information + 8);
		tag-> type != MULTIBOOT_TAG_TYPE_END;
		tag = (struct multiboot_tag *)(
			(uint8_t *)tag + ((tag->size + 7) & ~7u)
		)) {
		char buffer[33];
		itoa((int)tag->type, buffer, 16);
		early_video_put_string("tag type: ", char_color);
		early_video_put_string(buffer, char_color);
		early_video_put_char('\n', char_color);
	}
	
	EARLY_PANIC("TERMINATED");
}
