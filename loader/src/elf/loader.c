#include "elf.h"
#include <early/log.h>
#include <early/panic.h>
#include "loader.h"

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

void
elf_loader_load(void *elf_start) {
	Elf64_Ehdr *header = (Elf64_Ehdr *)elf_start;

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

	for(unsigned int i = 0; i < header->e_shnum; i++) {
		Elf64_Shdr *section_header = (Elf64_Shdr *)(uint32_t)(((uint32_t)elf_start) + header->e_shoff + header->e_shentsize*i); // todo this is awful

		LOGF(
			"ELF_SECTIONS[%qi] = A0x%qx O0x%qx T0x%qx (%s)\n",
			(uint64_t)i,
			(uint64_t)section_header->sh_addr,
			(uint64_t)section_header->sh_offset,
			(uint64_t)section_header->sh_type,
			get_section_type_name(section_header->sh_type)
		);
	}
}
