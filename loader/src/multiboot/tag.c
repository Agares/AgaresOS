#include "tag.h"
#include <stddef.h>
#include <early/video.h>
#include <libc/stdlib.h>
#include <gcc.h>

struct multiboot_tag *
multiboot_find_next_tag(uint16_t type, struct multiboot_tag *tags_start) {
	struct multiboot_tag *current_tag = NULL;

	for(current_tag = tags_start;
		current_tag->type != MULTIBOOT_TAG_TYPE_END;
		current_tag = (struct multiboot_tag *)(
			(uint8_t *)current_tag + ((current_tag->size + 7) & ~7u) // todo ALIGN macro
		)) {
		if(current_tag->type == type) {
				return current_tag;
		}
	}
	return NULL;
}

