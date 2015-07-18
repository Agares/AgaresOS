#include "structures.h"
#include "fill_structures.h"
#include "../flags.h"
#include "paging.h"
#include "../early/log.h"
#include "../early/panic.h"
#include "../macros.h"
#include <stdbool.h>

static paging_pml4_entry pml4[512] __attribute__((aligned(4096)));
static uint64_t paging_buffer[512*64] __attribute__((aligned(4096)));
static int paging_buffer_index = 0;

#define IS_ALIGNED(x) (((x) % 0x1000) == 0)

#define PML4_INDEX(x) (((x) >> 39) & 511)
#define PDPT_INDEX(x) (((x) >> 30) & 511)
#define PD_INDEX(x) (((x) >> 21) & 511)
#define PT_INDEX(x) (((x) >> 12) & 511)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
static uint64_t get_page_from_buffer() {
	if(paging_buffer_index >= 512*64) {
		__asm__ __volatile__ ("xchg %bx, %bx");
		return 0;
	}

	paging_buffer_index += 512;
	return (uint64_t)&paging_buffer[paging_buffer_index - 512];
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
void paging_map_page(uint64_t physical_address, uint64_t virtual_address) {
	if(!IS_ALIGNED(physical_address)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": physical_address not aligned");
	}

	if(!IS_ALIGNED(virtual_address)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": virtual_address not aligned");
	}

	uint64_t pml4_index = PML4_INDEX(virtual_address);
	uint64_t pdpt_index = PDPT_INDEX(virtual_address);
	uint64_t pd_index = PD_INDEX(virtual_address);
	uint64_t pt_index = PT_INDEX(virtual_address);

	if(!pml4[pml4_index].is_present) {
		fill_pml4_entry(&pml4[pml4_index], get_page_from_buffer(), PML4_ENTRY_PRESENT | PML4_ENTRY_WRITEABLE);
	}

	paging_pdpt_entry *pdpt_entry = &(((paging_pdpt_entry *)(pml4[pml4_index].physical_address << 12))[pdpt_index]);

	if(!pdpt_entry->is_present) {
		fill_pdpt_entry(pdpt_entry, get_page_from_buffer(), PDPT_ENTRY_PRESENT | PDPT_ENTRY_WRITEABLE);
	}

	paging_pd_entry *pd_entry = &(((paging_pd_entry *)(pdpt_entry->physical_address << 12))[pd_index]);

	if(!pd_entry->is_present) {
		fill_pd_entry(pd_entry, get_page_from_buffer(), PD_ENTRY_PRESENT | PD_ENTRY_WRITEABLE);
	}

	paging_pt_entry *pt_entry = &(((paging_pt_entry *)(pd_entry->physical_address << 12))[pt_index]);

	if(!pt_entry->is_present) {
		fill_pt_entry(pt_entry, physical_address, PT_ENTRY_PRESENT | PT_ENTRY_WRITEABLE);
	} else {
		LOG("Mapping from virtual ");
		LOG_NUMBER_HEX((int)virtual_address);
		LOG(" to physical ");
		LOG_NUMBER_HEX((int)physical_address);
		LOG(" already exists!\n");
	}
}
#pragma GCC diagnostic pop

void paging_map_range(uint64_t physical_start, uint64_t physical_end, uint64_t virtual_start) {
	if(!IS_ALIGNED(physical_start)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": physical_start not aligned");
	}

	if(!IS_ALIGNED(physical_end)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": physical_end not aligned");
	}

	if(!IS_ALIGNED(virtual_start)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": virtual_start not aligned");
	}

	for(uint64_t v = virtual_start, p = physical_start; p < physical_end; p += 0x1000, v+= 0x1000) {
		paging_map_page(v, p);
	}
}

void paging_load_pml4() {
	__asm__ __volatile__ (
		"mov %0, %%cr3"
		:
		: "r" (&pml4[0])
		: "memory"
		);
}
