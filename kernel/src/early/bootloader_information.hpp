#pragma once
#include <stdint.h>

namespace AgaresOS { namespace Early {
	enum class MemoryMapEntryType : uint64_t {
		Unused = 0,
		Unavailable,
		Firmware,
		Acpi,
		Kernel,
		AcpiNVS
	};

	struct MemoryMapEntry {
		uint64_t StartAddress;
		uint64_t EndAddress;
		MemoryMapEntryType Type;
	} __attribute__((packed));

	struct BootloaderInformation {
		uint32_t Version;
		char BootloaderTag[81];
		MemoryMapEntry MemoryMap[64];
		uint32_t MemoryMapEntrySize;
	} __attribute__((packed));
}}
