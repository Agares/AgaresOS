#pragma once

#define MEMORY_MAP_ENTRY_FREE 0
#define MEMORY_MAP_ENTRY_UNAVAILABLE 1
#define MEMORY_MAP_ENTRY_FIRMWARE 2
#define MEMORY_MAP_ENTRY_ACPI 3
#define MEMORY_MAP_ENTRY_KERNEL 4
#define MEMORY_MAP_ENTRY_ACPI_NVS 5

typedef struct {
	uint64_t start_address;
	uint64_t end_address;
	uint64_t type;
} packed memory_map_entry;

typedef struct {
	uint32_t version;
	char bootloader_tag[81];
	memory_map_entry memory_map[64];
	uint32_t memory_map_entry_size;
} packed bootloader_information;
