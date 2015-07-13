#pragma once
#include <stdint.h>
#include "structures.h"

#define PML4_ENTRY_PRESENT (1 << 0)
#define PML4_ENTRY_WRITEABLE (1 << 1)
#define PML4_ENTRY_USER (1 << 2)
#define PML4_ENTRY_WRITE_THROUGH (1 << 3)
#define PML4_ENTRY_CACHE_DISABLED (1 << 4)
#define PML4_ENTRY_EXECUTION_DISABLED (1 << 5)

#define PDPT_ENTRY_PRESENT (1 << 0)
#define PDPT_ENTRY_WRITEABLE (1 << 1)
#define PDPT_ENTRY_USER (1 << 2)
#define PDPT_ENTRY_WRITE_THROUGH (1 << 3)
#define PDPT_ENTRY_CACHE_DISABLE (1 << 4)
#define PDPT_ENTRY_IS_1GB (1 << 5)
#define PDPT_ENTRY_EXECUTION_DISABLED (1 << 6)

#define PD_ENTRY_PRESENT (1 << 0)
#define PD_ENTRY_WRITEABLE (1 << 1)
#define PD_ENTRY_USER (1 << 2)
#define PD_ENTRY_WRITE_THROUGH (1 << 3)
#define PD_ENTRY_CACHE_DISABLE (1 << 4)
#define PD_ENTRY_IS_2MB (1 << 5)
#define PD_ENTRY_EXECUTION_DISABLED (1 << 6)

#define PT_ENTRY_PRESENT (1 << 0)
#define PT_ENTRY_WRITEABLE (1 << 1)
#define PT_ENTRY_USER (1 << 2)
#define PT_ENTRY_WRITE_THROUGH (1 << 3)
#define PT_ENTRY_CACHE_DISABLE (1 << 4)
/* todo #define PT_ENTRY_MEMORY_TYPE_??? (1 << 5) */
#define PT_ENTRY_GLOBAL (1 << 6)

void fill_pml4_entry(paging_pml4_entry *entry, uint64_t physical_address, int flags);
void fill_pdpt_entry(paging_pdpt_entry *entry, uint64_t physical_address, int flags);
void fill_pd_entry(paging_pd_entry *entry, uint64_t physical_address, int flags);
void fill_pt_entry(paging_pt_entry *entry, uint64_t physical_address, int flags);
