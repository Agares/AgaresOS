#pragma once
#include <stdint.h>
// todo:
#define packed __attribute__((packed))

typedef struct {
	uint8_t is_present : 1;
	uint8_t is_writeable : 1;
	uint8_t is_user : 1;
	uint8_t page_level_write_through : 1;
	uint8_t page_level_cache_disable : 1;
	uint8_t accessed : 1;
	uint8_t ignored_3 : 1;
	uint8_t reserved_1 : 1;
	uint8_t ignored_2 : 4;
	uint64_t physical_address : 40;
	uint16_t ignored_1 : 11;
	uint8_t execute_disable : 1;
} packed paging_pml4_entry;

typedef struct {
	uint8_t is_present : 1;
	uint8_t is_writeable : 1;
	uint8_t is_user : 1;
	uint8_t page_level_write_through : 1;
	uint8_t page_level_cache_disable : 1;
	uint8_t accessed : 1;
	uint8_t ignored_3 : 1;
	uint8_t is_1GB_page : 1;
	uint8_t ignored_2 : 4;
	uint64_t physical_address : 40;
	uint16_t ignored_1 : 11;
	uint8_t execute_disable : 1;
} packed paging_pdpt_entry;

typedef struct {
	uint8_t is_present : 1;
	uint8_t is_writeable : 1;
	uint8_t is_user : 1;
	uint8_t page_level_write_through : 1;
	uint8_t page_level_cache_disable : 1;
	uint8_t accessed : 1;
	uint8_t ignored_3 : 1;
	uint8_t is_2MB_page : 1;
	uint8_t ignored_2 : 4;
	uint64_t physical_address : 40;
	uint16_t ignored_1 : 11;
	uint8_t execute_disable : 1;
} packed paging_pd_entry;

typedef struct {
	uint8_t is_present : 1;
	uint8_t is_writeable : 1;
	uint8_t is_user : 1;
	uint8_t page_level_write_through : 1;
	uint8_t page_level_cache_disable : 1;
	uint8_t accessed : 1;
	uint8_t is_dirty : 1;
	uint8_t memory_type : 1;
	uint8_t is_global : 1;
	uint8_t ignored_2 : 3;
	uint64_t physical_address : 40;
	uint16_t ignored_1 : 7;
	uint8_t protection_key : 4;
	uint8_t execute_disable : 1;
} packed paging_pt_entry;
