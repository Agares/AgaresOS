#pragma once
#include <stdint.h>

void x86_gdt_setup(void);
void x86_gdt_setup_long_mode(uint64_t code_address);
