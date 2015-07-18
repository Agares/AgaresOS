#include <early/video.h>
#include <libc/stdlib.h>
#include <early/panic.h>
#include <early/log.h>
#include "arch/x86/gdt.h"
#include "multiboot/tag.h"
#include "multiboot/module.h"
#include "elf/loader.h"
#include <paging/paging.h>
#include <cpu.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include "multiboot/multiboot2.h"
#pragma GCC diagnostic pop
#include <stddef.h>

#define ALIGN_UP(addr) (((addr) & (~0xFFFull)) + 0x1000)

static paging_context initial_paging;
static uint64_t paging_buffer[512*64] aligned(0x1000);
static int paging_buffer_index = 0;

extern void *kernel_start;
extern void *kernel_end;

static uint64_t *allocate_frame() {
	if(paging_buffer_index >= 512*63) {
		EARLY_PANIC("Page frame buffer exhausted!");
	}

	paging_buffer_index += 512;
	return &paging_buffer[paging_buffer_index - 512];
}

void kmain(uint32_t, uint32_t);

void kmain(uint32_t magic, uint32_t multiboot_information) {
	character_color char_color = { 
		.foreground = COLOR_YELLOW,
		.background = COLOR_BLACK 
	};

	initial_paging.frame_allocator = &allocate_frame;
 
	early_video_put_string("agos, version 0\n", char_color); 
	if(magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		EARLY_PANIC("Loaded from not multiboot-complaiant bootloader.");
	}

	x86_gdt_setup();

	uint32_t multiboot_information_total_size = ((uint32_t *)multiboot_information)[0];

	struct multiboot_tag *multiboot_tags_start = (struct multiboot_tag *)(multiboot_information + 8);

	// +8 here is to skip the header (4bytes size + 4bytes reserved)
	struct multiboot_tag_mmap *tag = (struct multiboot_tag_mmap*)multiboot_find_next_tag(MULTIBOOT_TAG_TYPE_MMAP, multiboot_tags_start);
	unsigned int tag_count = (tag->size - 16) / tag->entry_size;
	for (unsigned int i = 0; i < tag_count; i++) {
		LOG("MEMMAP[");
		LOG_NUMBER_DEC((int)i);
		LOG("]: ");

		LOG_NUMBER_HEX((int)tag->entries[i].type); LOG(" ");
		LOG_NUMBER_HEX((int)tag->entries[i].addr); LOG(" ");
		LOG_NUMBER_HEX((int)tag->entries[i].len);  LOG("\n");
	}

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

	// identity map first megabyte
	paging_map_range(&initial_paging, (paging_range){
		.physical_start = 0,
		.physical_end = 1024*1024,
		.virtual_start = 0
	});

	// identity map kernel
	int kernel_start_addr = (int)&kernel_start;
	int kernel_end_addr = (int)&kernel_end;

	paging_map_range(&initial_paging, (paging_range){
		.physical_start = kernel_start_addr,
		.physical_end = ALIGN_UP(kernel_end_addr),
		.virtual_start = kernel_start_addr
	});

	// identity map multiboot tags
	uint64_t multiboot_information_start = multiboot_information & ~0xFFFull;
	uint64_t multiboot_information_end = ALIGN_UP(multiboot_information + multiboot_information_total_size);
	paging_map_range(&initial_paging, (paging_range){
		.physical_start = multiboot_information_start,
		.physical_end = multiboot_information_end,
		.virtual_start = multiboot_information_start
	});

	paging_load_pml4(&initial_paging);
	
	cpu_enable_pae();
	cpu_enable_ia64();
	cpu_enable_paging();

	while(1);
}
