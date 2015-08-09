#pragma once
#include <paging/paging.h>

uint64_t elf_loader_load(void *elf_start, paging_context *paging_context);
