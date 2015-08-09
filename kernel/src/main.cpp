#include <stdint.h>
#include <video/video.hpp>

using AgaresOS::Video;

extern "C" int kmain(void) {
	Video video;
	video.Clear();
	video.PutString("Hello from kernel");

	while(true) {}
}
