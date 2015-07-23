#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <gcc.h>
#include "structures.h"

typedef union {
	uintptr_t as_uint;
	void *as_pointer;
} paging_physical_address;

typedef uint64_t paging_virtual_address;

/**
 * A frame allocator allocates space for a single page table, 
 * i.e. 4096 bytes of consecutive memory, aligned to 0x1000.
 */
typedef uint64_t *(*paging_frame_allocator)();
typedef paging_physical_address (*paging_virtual_to_physical_translator)(paging_virtual_address virtual_address);

typedef struct {
	paging_frame_allocator frame_allocator;
	paging_virtual_to_physical_translator virtual_to_physical_translator;
	paging_pml4_entry pml4[512] aligned(0x1000);
} paging_context;

typedef struct {
	paging_physical_address physical_start,
			 	   physical_end;

	paging_virtual_address virtual_start;
} paging_range;

typedef struct {
	paging_physical_address physical_address;
	paging_virtual_address virtual_address;
} paging_page;

static inline bool paging_is_aligned_virtual(paging_virtual_address address) {
	return (address % 0x1000) == 0;
}

static inline bool paging_is_aligned_physical(paging_physical_address address) {
	return (address.as_uint % 0x1000) == 0;
}

static inline paging_physical_address paging_align_down(paging_physical_address address) {
	return (paging_physical_address){ .as_uint = address.as_uint & ~((uintptr_t)0xFFFu) };
}

static inline paging_physical_address paging_align_up(paging_physical_address address) {
	return (paging_physical_address){ .as_uint = (address.as_uint + 0xFFF) & ~((uintptr_t)0xFFFu) };
}

void paging_map_page(paging_context *context, paging_page page);
void paging_map_range(paging_context *context, paging_range range);
void paging_load_pml4(paging_context *context);
