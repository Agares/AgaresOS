#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include "multiboot2.h"
#pragma GCC diagnostic pop
#include <stdint.h>

typedef struct {
		void *load_address;
		uint32_t size;
} multiboot_module;

multiboot_module *
multiboot_module_read_next(struct multiboot_tag *multiboot_tags);
