#include "structures.h"
#include "fill_structures.h"
#include "../flags.h"
#include "paging.h"
#include "../early/log.h"
#include "../early/panic.h"
#include "../macros.h"
#include "../gcc.h"
#include "../cpu.h"
#include <stdbool.h>
#include <stddef.h>

#define IS_ALIGNED(x) (((x) % 0x1000) == 0)

#define PML4_INDEX(x) ((((uint64_t)x) >> 39) & 511)
#define PDPT_INDEX(x) (((x) >> 30) & 511)
#define PD_INDEX(x) (((x) >> 21) & 511)
#define PT_INDEX(x) (((x) >> 12) & 511)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"

void paging_map_page(paging_context *context, paging_page page) {
	if(!paging_is_aligned(page.physical_address)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": physical_address not aligned");
	}

	if(!paging_is_aligned(page.virtual_address)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": virtual_address not aligned");
	}

	int pml4_index = PML4_INDEX(page.virtual_address.as_uint);
	int pdpt_index = PDPT_INDEX(page.virtual_address.as_uint);
	int pd_index = PD_INDEX(page.virtual_address.as_uint);
	int pt_index = PT_INDEX(page.virtual_address.as_uint);

	if(!context->pml4[pml4_index].is_present) {
		fill_pml4_entry(&context->pml4[pml4_index], (uint64_t)context->frame_allocator(), PML4_ENTRY_PRESENT | PML4_ENTRY_WRITEABLE);
	}

	paging_pdpt_entry *pdpt_entry = &(((paging_pdpt_entry *)(context->pml4[pml4_index].physical_address << 12))[pdpt_index]);

	if(!pdpt_entry->is_present) {
		fill_pdpt_entry(pdpt_entry, (uint64_t)context->frame_allocator(), PDPT_ENTRY_PRESENT | PDPT_ENTRY_WRITEABLE);
	}

	paging_pd_entry *pd_entry = &(((paging_pd_entry *)(pdpt_entry->physical_address << 12))[pd_index]);

	if(!pd_entry->is_present) {
		fill_pd_entry(pd_entry, (uint64_t)context->frame_allocator(), PD_ENTRY_PRESENT | PD_ENTRY_WRITEABLE);
	}

	paging_pt_entry *pt_entry = &(((paging_pt_entry *)(pd_entry->physical_address << 12))[pt_index]);

	if(!pt_entry->is_present) {
		fill_pt_entry(pt_entry, page.physical_address.as_uint, PT_ENTRY_PRESENT | PT_ENTRY_WRITEABLE);
	} else {
		LOG("Mapping from virtual ");
		LOG_NUMBER_HEX((int)page.virtual_address.as_uint);
		LOG(" to physical ");
		LOG_NUMBER_HEX((int)page.physical_address.as_uint);
		LOG(" already exists!\n");
	}
}
#pragma GCC diagnostic pop

void paging_map_range(paging_context *context, paging_range range) {
	if(!paging_is_aligned(range.physical_start)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": physical_start not aligned");
	}

	if(!paging_is_aligned(range.physical_end)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": physical_end not aligned");
	}

	if(!paging_is_aligned(range.virtual_start)) {
		EARLY_PANIC(__FILE__ ":" STR(__LINE__) ": virtual_start not aligned");
	}

	for(
		paging_address v = range.virtual_start, p = range.physical_start; 
		p.as_uint < range.physical_end.as_uint; 
		p.as_uint += 0x1000, v.as_uint += 0x1000
	) {
		paging_map_page(context, (paging_page){.physical_address = p, .virtual_address = v});
	}
}

void paging_load_pml4(paging_context *context) {
	paging_pml4_entry *pml4 = &context->pml4[0];
	cpu_write_cr3((uintptr_t)pml4);
}
