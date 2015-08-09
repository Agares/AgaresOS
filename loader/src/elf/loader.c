#include "elf.h"
#include <early/log.h>
#include <early/panic.h>
#include "loader.h"
#include <paging/paging.h>
#include <memory.h>
#include <libc/memory.h>

static const char*
get_section_type_name(Elf64_Word type) {
	const char *const types[] = {
			"SHT_NULL",
			"SHT_PROGBITS",
			"SHT_SYMTAB",
			"SHT_STRTAB",
			"SHT_RELA",
			"SHT_HASH",
			"SHT_DYNAMIC",
			"SHT_NOTE",
			"SHT_NOBITS",
			"SHT_REL",
			"SHT_SHLIB",
			"SHT_DYNSYM"
	};
	const unsigned int type_count = (sizeof(types)/sizeof(types[0]));

	return type_count > type
			? types[type] 
			: "Unknown";
}

static void
validate_signature(Elf64_Ehdr *header) {
	if(
		header->e_ident[0] != 0x7f 
		|| header->e_ident[1] != 'E' 
		|| header->e_ident[2] != 'L' 
		|| header->e_ident[3] != 'F') {
			EARLY_PANIC("INVALID ELF MAGIC");
	}

	if(header->e_type != 2) {
		EARLY_PANIC("NOT AN EXECUTABLE FILE");
	}

	if(header->e_ident[4] != 2) {
		EARLY_PANIC("NOT A 64-bit ELF");
	}

	if(header->e_shoff == 0) {
		EARLY_PANIC("NO SECTION HEADER IN ELF FILE");
	}
}

static Elf64_Shdr *
get_section_header(Elf64_Ehdr *elf_header, int index) {
	return (Elf64_Shdr *)(uint32_t)(((uint32_t)elf_header) + elf_header->e_shoff + elf_header->e_shentsize*index); // todo this is awful
}

static uint8_t *
get_section(Elf64_Ehdr *elf_header, int index) {
	return (uint8_t *)(uint32_t)(((uint32_t)elf_header) + get_section_header(elf_header, index)->sh_offset);
}

static void
log_sections(Elf64_Ehdr *header) {
	for(unsigned int i = 0; i < header->e_shnum; i++) {
		Elf64_Shdr *section_header = get_section_header(header, i);

		LOGF(
			"ELF_SECTIONS[%qi] = %s A0x%qx O0x%qx E0x%qx T0x%qx (%s)\n",
			(uint64_t)i,
			get_section(header, header->e_shstrndx) + section_header->sh_name,
			(uint64_t)section_header->sh_addr,
			(uint64_t)section_header->sh_offset,
			(uint64_t)section_header->sh_size + section_header->sh_addr,
			(uint64_t)section_header->sh_type,
			get_section_type_name(section_header->sh_type)
		);
	}
}

static void
map_progbits(Elf64_Ehdr *elf_header, int section_index, paging_context *paging_context_pointer) {
	Elf64_Shdr *section_header = get_section_header(elf_header, section_index);
	uint32_t section_physical_start = (uint32_t)get_section(elf_header, section_index);

	paging_map_range(paging_context_pointer, (paging_range){
		.virtual_start = section_header->sh_addr,
		.physical_start = (paging_physical_address){ .as_uint = section_physical_start },
		.physical_end = paging_align_up((paging_physical_address){.as_uint = section_physical_start + section_header->sh_size})
	});
}

static void
map_nobits(Elf64_Ehdr *elf_header, int section_index, paging_context *paging_context_pointer) {
	Elf64_Shdr *section_header = get_section_header(elf_header, section_index);

	void *memory = mm_find_hole(section_header->sh_size/4096);
	if(memory == 0) {
		EARLY_PANIC("Not enough memory to initialize SHT_NOBITS section!");
	}

	void *memory_end = (void *)((uintptr_t)memory + (uintptr_t)section_header->sh_size);
	mm_mark_as_used(memory, memory_end);

	memset(memory, 0, section_header->sh_size);

	paging_map_range(paging_context_pointer, (paging_range){
		.virtual_start = section_header->sh_addr,
		.physical_start = (paging_physical_address){ .as_pointer = memory },
		.physical_end = paging_align_up((paging_physical_address){ .as_pointer = memory_end })
	});
}

static void
map_sections(Elf64_Ehdr *elf_header, paging_context *paging_context_pointer) {
	for(int i = 0; i < elf_header->e_shnum; i++) {
		Elf64_Shdr *current_section_header = get_section_header(elf_header, i);

		// fixme support SHT_NOBITS (e.g. .bss)
		// fixme 1 is const for SHT_PROGBITS - define it somewhere
		switch(current_section_header->sh_type) {
			case 1: // SHT_PROGBITS
				map_progbits(elf_header, i, paging_context_pointer);
				break;
			case 8: // SHT_NOBITS
				map_nobits(elf_header, i, paging_context_pointer);
				break;
			default:
				continue;
		}
	}
}

uint64_t
elf_loader_load(void *elf_start, paging_context *paging_context_pointer) {
	Elf64_Ehdr *header = (Elf64_Ehdr *)elf_start;

	validate_signature(header);
	log_sections(header);
	map_sections(header, paging_context_pointer);

	return header->e_entry;
}
