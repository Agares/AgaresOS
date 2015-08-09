#include "memory.h"
#include <stdint.h>
#include <stddef.h>

#define BITMAP_SIZE (1024*64)

static uint64_t usage_bitmap[1024];

static void bitmap_set(int index) {
	usage_bitmap[index/1024] |= 1 << (index%1024);
}

static int bitmap_get(int index) {
	return usage_bitmap[index/1024] & (1 << (index%1024));
}

void mm_set_top(void *end) {
	uintptr_t end_address = (uintptr_t)end;
	
	int end_index = end_address/4096;
	for(int i = end_index; i < BITMAP_SIZE; i++) {
		bitmap_set(i);
	}
}

void mm_mark_as_used(void *start, void *end) {
	int start_index = ((uintptr_t)start)/4096;
	int end_index = ((uintptr_t)end)/4096;

	for(int i = start_index; i < end_index; i++) {
		bitmap_set(i);
	}	
}

void *mm_find_hole(int pages) {
	for(int i = 0; i < BITMAP_SIZE; i++) {
		if(bitmap_get(i)) {
			continue;
		}

		for(int j = i; j < BITMAP_SIZE; j++) {
			if(bitmap_get(i)) {
				break;
			}

			if(j - i == pages) {
				return (void *)(i*4096);
			}
		}
	}

	return NULL;
}
