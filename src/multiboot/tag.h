#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include "multiboot2.h"
#pragma GCC diagnostic pop
#include <stdint.h>

struct multiboot_tag *multiboot_find_next_tag(uint16_t type, struct multiboot_tag *tags_start);
