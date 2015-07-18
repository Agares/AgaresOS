#include "cpu.h"

uint64_t cpu_read_msr(uint32_t msr_id) {
	uint64_t value;

	__asm__ __volatile__ (
		"rdmsr" : "=A"(value) : "c"(msr_id) : "memory"
	);

	return value;
}

void cpu_write_msr(uint32_t msr_id, uint64_t value) {
	__asm__ __volatile__ (
		"wrmsr" : : "c"(msr_id), "A"(value) : "memory"
	);
}

uint64_t cpu_read_cr0() {
	uint64_t value;

	__asm__ __volatile__ (
		"mov %%cr0, %0" : "=r"(value) : : "memory"
	);

	return value;
}

uint64_t cpu_read_cr2() {
	uint64_t value;

	__asm__ __volatile__ (
		"mov %%cr2, %0" : "=r"(value) : : "memory"
	);

	return value;
}

uint64_t cpu_read_cr3() {
	uint64_t value;

	__asm__ __volatile__ (
		"mov %%cr3, %0" : "=r"(value) : : "memory"
	);

	return value;
}

uint64_t cpu_read_cr4() {
	uint64_t value;

	__asm__ __volatile__ (
		"mov %%cr4, %0" : "=r"(value) : : "memory"
	);

	return value;
}

void cpu_write_cr0(uint64_t value) {
	__asm__ __volatile__ (
		"mov %0, %%cr0" : : "r"(value) : "memory"
	);
}

void cpu_write_cr3(uint64_t value) {
	__asm__ __volatile__ (
		"mov %0, %%cr3" : : "r"(value) : "memory"
	);
}

void cpu_write_cr4(uint64_t value) {
	__asm__ __volatile__ (
		"mov %0, %%cr4" : : "r"(value) : "memory"
	);
}
