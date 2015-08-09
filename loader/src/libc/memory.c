#include "memory.h"

void *memset(void *address, int value, size_t length) {
	uint8_t *memory = (uint8_t *)address;

	for(size_t i = 0; i < length; i++) {
		memory[i] = value;
	}

	return address;
}
