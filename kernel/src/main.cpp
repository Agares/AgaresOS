#include <stdint.h>

extern "C" int kmain(void) {
	uint16_t *video_memory = (uint16_t *)0xb8000;
	video_memory[0] = 0xef63;
	video_memory[1] = 0xec64;

	while(true) {}
}
