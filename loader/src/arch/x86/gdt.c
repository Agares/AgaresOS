#include "gdt.h"
#include <stdint.h>
#include "../../../../common/src/gcc.h"

typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} packed gdt_entry;

typedef struct {
	uint16_t limit;
	uint32_t base;
} packed gdt_pointer;

extern void gdt_load(gdt_pointer *pointer);

static void
gdt_create_entry(gdt_entry *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
	entry->base_low = (base & 0xFFFF);
	entry->base_middle = (base >> 16) & 0xFF;
	entry->base_high = (uint8_t)((base >> 24) & 0xFF);

	entry->limit_low = (limit & 0xFFFF);
	entry->granularity = ((limit >> 16) & 0x0F); // 8 bits of limit are held in field we called "granularity"

	entry->granularity = (uint8_t)(granularity | (granularity & 0xF0));
	entry->access = access;
}

void
x86_gdt_setup() {
	gdt_entry gdt[5];
	gdt_pointer gdt_ptr;

	gdt_create_entry(&gdt[0], 0, 0, 0, 0); // first segment must be 0
	gdt_create_entry(&gdt[1], 0, 0xFFFFFFFF, 0x9A, 0xCF); // system code segment
	gdt_create_entry(&gdt[2], 0, 0xFFFFFFFF, 0x92, 0xCF); // system data segment
	gdt_create_entry(&gdt[3], 0, 0xFFFFFFFF, 0xFA, 0xCF); // user code segment
	gdt_create_entry(&gdt[4], 0, 0xFFFFFFFF, 0xF2, 0xCF); // user data segment

	gdt_ptr.limit = sizeof(gdt)-1;
	gdt_ptr.base = (uint32_t)&gdt[0];

	gdt_load(&gdt_ptr);
}
