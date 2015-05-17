#include "early/video.h"
#include "libc/stdlib.h"
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
		// todo create panic macro and use it here
		early_video_put_string("Loaded from not multiboot-complaiant bootloader.", char_color);
		while(1){}
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

	char buffer[33];
	itoa(1024, buffer, 2);
	early_video_put_string(buffer, char_color);
	early_video_put_char(' ', char_color);
	itoa(1024, buffer, 10);
	early_video_put_string(buffer, char_color);

	while(1){} 
}
