#pragma once
#include <stdint.h>
#include <gcc.h>
#include "structures.h"

typedef uint64_t *(*frame_allocator)();

typedef struct {
	frame_allocator frame_allocator;
	paging_pml4_entry pml4[512] aligned(0x1000);
} paging_context;

typedef struct {
	uint64_t physical_start,
			 physical_end,
			 virtual_start;
} paging_range;

typedef struct {
	uint64_t physical_address,
			 virtual_address;
} paging_page;

void paging_map_page(paging_context *context, paging_page page);
void paging_map_range(paging_context *context, paging_range range);
void paging_load_pml4(paging_context *context);
