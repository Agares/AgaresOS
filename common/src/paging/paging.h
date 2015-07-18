#pragma once
#include <stdint.h>

void paging_map_page(uint64_t, uint64_t);
void paging_map_range(uint64_t physical_start, uint64_t physical_end, uint64_t virtual_start);
void paging_load_pml4(void);
