#include <stdint.h>
#include <video/video.hpp>

using AgaresOS::Video;

extern "C" int kmain(uint32_t test) {
	Video video;
	video.Clear();
	video.PutString("Hello from kernel");

	do {
		video.PutChar("0123456789"[test%10]);
	} while((test /= 10) != 0);

	while(true) {}
}
