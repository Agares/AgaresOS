#include "fill_structures.h"
#include "../flags.h"
#include "../early/video.h"
#include "../early/log.h"

void fill_pml4_entry(paging_pml4_entry *entry, uint64_t physical_address, int flags) {
	entry->ignored_1 = 0;
	entry->ignored_2 = 0;
	entry->ignored_3 = 0;

	entry->reserved_1 = 0;

	entry->accessed = 0;

	entry->is_present = has_flag(flags, PML4_ENTRY_PRESENT);
	entry->is_writeable = has_flag(flags, PML4_ENTRY_WRITEABLE);
	entry->is_user = has_flag(flags, PML4_ENTRY_USER);
	entry->page_level_write_through = has_flag(flags, PML4_ENTRY_WRITE_THROUGH);
	entry->page_level_cache_disable = has_flag(flags, PML4_ENTRY_CACHE_DISABLED);
	entry->execute_disable = has_flag(flags, PML4_ENTRY_EXECUTION_DISABLED);

	entry->physical_address = physical_address >> 12;
}

void fill_pdpt_entry(paging_pdpt_entry *entry, uint64_t physical_address, int flags) {
	entry->ignored_1 = 0;
	entry->ignored_2 = 0;
	entry->ignored_3 = 0;

	entry->accessed = 0;

	entry->is_present = has_flag(flags, PDPT_ENTRY_PRESENT);
	entry->is_writeable = has_flag(flags, PDPT_ENTRY_WRITEABLE);
	entry->is_user = has_flag(flags, PDPT_ENTRY_USER);
	entry->page_level_write_through = has_flag(flags, PDPT_ENTRY_WRITE_THROUGH);
	entry->page_level_cache_disable = has_flag(flags, PDPT_ENTRY_CACHE_DISABLE);
	entry->is_1GB_page = has_flag(flags, PDPT_ENTRY_IS_1GB);
	entry->execute_disable = has_flag(flags, PDPT_ENTRY_EXECUTION_DISABLED);

	entry->physical_address = physical_address >> 12;
}

void fill_pd_entry(paging_pd_entry *entry, uint64_t physical_address, int flags) {
	entry->ignored_1 = 0;
	entry->ignored_2 = 0;
	entry->ignored_3 = 0;

	entry->accessed = 0;

	entry->is_present = has_flag(flags, PD_ENTRY_PRESENT);
	entry->is_writeable = has_flag(flags, PD_ENTRY_WRITEABLE);
	entry->is_user = has_flag(flags, PD_ENTRY_USER);
	entry->page_level_write_through = has_flag(flags, PD_ENTRY_WRITE_THROUGH);
	entry->page_level_cache_disable = has_flag(flags, PD_ENTRY_CACHE_DISABLE);
	entry->is_2MB_page = has_flag(flags, PD_ENTRY_IS_2MB);
	entry->execute_disable = has_flag(flags, PD_ENTRY_EXECUTION_DISABLED);

	entry->physical_address = physical_address >> 12;
}

void fill_pt_entry(paging_pt_entry *entry, uint64_t physical_address, int flags) {
	entry->ignored_1 = 0;
	entry->ignored_2 = 0;

	entry->accessed = 0;
	entry->is_dirty = 0;
	entry->protection_key = 0;

	entry->is_present = has_flag(flags, PT_ENTRY_PRESENT);
	entry->is_writeable = has_flag(flags, PT_ENTRY_WRITEABLE);
	entry->is_user = has_flag(flags, PT_ENTRY_USER);
	entry->page_level_write_through = has_flag(flags, PT_ENTRY_WRITE_THROUGH);
	entry->page_level_cache_disable = has_flag(flags, PT_ENTRY_CACHE_DISABLE);
	entry->is_global = has_flag(flags, PT_ENTRY_GLOBAL);
	entry->execute_disable = has_flag(flags, PDPT_ENTRY_EXECUTION_DISABLED);

	entry->physical_address = physical_address >> 12;
}
