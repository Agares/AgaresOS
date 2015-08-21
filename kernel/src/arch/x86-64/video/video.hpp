#pragma once
#include <stdint.h>

namespace AgaresOS {
	class Video {
		public:
			enum class Color : uint8_t {
				Black = 0,
				Blue,
				Green,
				Cyan,
				Red,
				Magenta,
				Brown,
				LightGray,
				DarkGray,
				LightBlue,
				LightGreen,
				LightCyan,
				LightRed,
				LightMagenta,
				LightYellow,
				White
			};

			void PutChar(char c, Color foreground = Color::LightGray, Color background = Color::Black);
			void PutString(const char * string, Color foreground = Color::LightGray, Color background = Color::Black);
			void Clear();
		private:
			volatile uint16_t *videoMemory = (volatile uint16_t*)0xb8000;
			uint16_t index = 0;

			const int WIDTH = 80;
			const int HEIGHT = 25;

			uint16_t PackColor(Color foreground, Color background);
	};
}
