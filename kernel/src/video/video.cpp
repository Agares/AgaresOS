#include "video.hpp"

namespace AgaresOS {
	void Video::PutChar(char c, Video::Color foreground, Video::Color background) {
		videoMemory[index++] = c | PackColor(foreground, background);
	}

	void Video::PutString(const char *string, Video::Color foreground, Video::Color background) {
		while(*string != 0) {
			PutChar(*(string++), foreground, background);
		}
	}

	void Video::Clear() {
		for(int i = 0; i < WIDTH*HEIGHT; i++) {
			videoMemory[i] = 0 | PackColor(Color::LightGray, Color::Black);
		}
	}

	uint16_t Video::PackColor(Video::Color foreground, Video::Color background) {
		return ((uint8_t)foreground << 8 | (uint8_t)background << 12);
	}
}
