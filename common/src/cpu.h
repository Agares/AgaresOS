#pragma once
#include <stdint.h>

uint64_t cpu_read_msr(uint32_t msr_id);
void cpu_write_msr(uint32_t msr_id, uint64_t value);

uint64_t cpu_read_cr0(void);
uint64_t cpu_read_cr2(void);
uint64_t cpu_read_cr3(void);
uint64_t cpu_read_cr4(void);

void cpu_write_cr0(uint64_t value);
void cpu_write_cr3(uint64_t value);
void cpu_write_cr4(uint64_t value);
