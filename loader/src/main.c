#include <early/video.h>
#include <libc/stdlib.h>
#include <early/panic.h>
#include <early/log.h>
#include <early/kprint.h>
#include "arch/x86/gdt.h"
#include "multiboot/tag.h"
#include "multiboot/module.h"
#include "elf/loader.h"
#include <paging/paging.h>
#include <cpu.h>
#include <early/kprint.h>
#include "memory.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include "multiboot/multiboot2.h"
#pragma GCC diagnostic pop
#include <stddef.h>

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

static paging_physical_address translate_address(paging_virtual_address address) {
	return (paging_physical_address){ .as_uint = address };
}

void kmain(uint32_t, uint32_t);

void kmain(uint32_t magic, uint32_t multiboot_information) {
	initial_paging.frame_allocator = &allocate_frame;
	initial_paging.virtual_to_physical_translator = &translate_address;
 
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
		LOGF(
			"MEMMAP[0x%qx] = T0x%qx A0x%qx L0x%qx\n", 
			(uint64_t)i, 
			(uint64_t)tag->entries[i].type, 
			(uint64_t)tag->entries[i].addr, 
			(uint64_t)tag->entries[i].len
		);
	}

	multiboot_module *module = multiboot_module_read_next(multiboot_tags_start);
	if(module != NULL) {
		LOGF("MBMOD: A0x%px S0x%qx\n", module->load_address, (uint64_t)module->size);
	} else {
		EARLY_PANIC("Module tag not found in multiboot information.");
	}

	// identity map first megabyte
	paging_map_range(&initial_paging, (paging_range){
		.physical_start = (paging_physical_address){ .as_uint = 0 },
		.physical_end = (paging_physical_address){ .as_uint = 1024*1024 },
		.virtual_start = 0
	});

	// identity map kernel
	paging_map_range(&initial_paging, (paging_range){
		.physical_start = (paging_physical_address){ .as_pointer = &kernel_start },
		.physical_end = paging_align_up((paging_physical_address){ .as_pointer = &kernel_end }),
		.virtual_start = (paging_virtual_address)(uintptr_t)&kernel_start // that cast is really stupid
	});

	// identity map multiboot tags
	uint64_t multiboot_information_start = multiboot_information;
	uint64_t multiboot_information_end = multiboot_information + multiboot_information_total_size;

	paging_map_range(&initial_paging, (paging_range){
		.physical_start = paging_align_down((paging_physical_address){ .as_uint = multiboot_information_start }),
		.physical_end = paging_align_up((paging_physical_address){ .as_uint = multiboot_information_end }),
		.virtual_start = paging_align_down((paging_physical_address){ .as_uint = multiboot_information_start }).as_uint // todo that's stupid
	});

	mm_mark_as_used((void *)0, (void *)(1024*1024));
	mm_mark_as_used(&kernel_start, &kernel_end);
	mm_mark_as_used((void *)(uintptr_t)multiboot_information_start, (void *)(uintptr_t)multiboot_information_end); // fixme hack
	mm_mark_as_used(module->load_address, (void *)((uintptr_t)module->load_address + module->size));

	uint64_t kernel_entry = elf_loader_load((void*)module->load_address, &initial_paging);
	kprint("Kernel loaded. Entry point: %qx\n", kernel_entry);

	paging_load_pml4(&initial_paging);
	
	cpu_enable_pae();
	cpu_enable_ia64();
	cpu_enable_paging();

	x86_gdt_setup_long_mode(kernel_entry);

	while(1);
}
