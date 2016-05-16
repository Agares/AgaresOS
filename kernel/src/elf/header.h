#pragma once
#include <stdint.h>
#include "types.h"

namespace AgaresOS { namespace Elf { namespace Private {
	struct ElfHeader {
		unsigned char Identification[16];
		uint16_t Type;
		uint16_t MachineType;
		uint32_t ObjectFileVersion;
		Offset ProgramHeaderOffset;
		Offset SectionHeaderOffset;
		uint32_t ProcessorFlags;
		uint16_t ElfHeaderSize;
		uint16_t ProgramHeaderEntrySize;
		uint16_t ProgramHeaderEntries;
		uint16_t SectionHeaderEntrySize;
		uint16_t SectionHeaderEntries;
		uint16_t SectionNameStringTableIndex;
	};

	struct ProgramHeader {
		uint32_t Type;
		uint32_t Flags;
		Offset OffsetValue;
		Address VirtualAddress;
		Address Reserved;
		uint64_t SegmentSizeInFile;
		uint64_t SegmentSizeInMemory;
		uint64_t Alignment;
	};

	struct SectionHeader {
		uint32_t SectionName;
		uint32_t Type;
		uint64_t Flags;
		Address AddressValue;
		Offset OffsetValue;
		uint64_t Size;
		uint32_t Link;
		uint32_t Information;
		uint64_t AddressAlignment;
		uint64_t EntrySize;
	};

	struct SymbolTableEntry {
		uint32_t Name;
		uint8_t Information;
		uint8_t Reserved;
		uint16_t SectionTableIndex;
		Address Value;
		uint64_t Size;
	};

	struct RelocationRel {
		Address OffsetValue;
		uint64_t Information;
	};
	
	struct RelocationRela {
		Address OffsetValue;
		uint64_t Information;
		int64_t Addend;
	};
}}}
