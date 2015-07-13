#pragma once
#include <stdint.h>

void paging_map_page(uint64_t, uint64_t);
void paging_load_pml4(void);
