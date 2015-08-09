#include "kprint.h"
#include "../libc/string.h"
#include "../early/video.h"
#include <stdarg.h>
#include <stdbool.h>

static character_color kprint_color = { .background=COLOR_BLACK, .foreground=COLOR_LIGHT_GRAY };

static inline void 
kputch(char c) {
	early_video_put_char(c, kprint_color);
}

static inline void 
kputs(const char *s) {
	early_video_put_string(s, kprint_color);
}

static inline void
kputnumber(uint64_t number, unsigned int base, bool as_signed) {
	char buffer[65] = { 0 };
	int buffer_index = 0;
	bool add_minus = false;
	static const char * const digits = "0123456789abcdef";

	if(as_signed && (int64_t)(number) < 0) {
		number = -number;
		add_minus = true;
	}

	do {
		int digit = (int)(number % base);

		buffer[buffer_index] = digits[digit];
		buffer_index++;
	} while(number /= (uint64_t)base);

	strrev(buffer);

	if(add_minus) {
		kputch('-');
	}
	kputs(buffer);
}

void kprint(const char *format, ...) {
	va_list arguments;
	va_start(arguments, format);

	for(size_t i = 0, length = strlen(format); i < length; i++) {
		if(format[i] != '%') {
			kputch(format[i]);
			continue;
		}

		i++;

		uint64_t value = 0;

		switch(format[i]) {
			case '%':
				kputch('%');
				continue;

			case 's':
				kputs(va_arg(arguments, const char *));
				continue;

			case 'q':
				value = va_arg(arguments, uint64_t);
				break;

			case 'd':
				value = va_arg(arguments, uint32_t);
				break;

			// both of these are promotable to 32bit:
			case 'w':
				value = va_arg(arguments, uint32_t);
				break;

			case 'b':
				value = va_arg(arguments, uint32_t);
				break;

			case 'p':
				value = (uintptr_t)va_arg(arguments, void*);
				break;
		}
		
		i++;

		switch(format[i]) {
			case 'u': // uint
				kputnumber(value, 10, false);
				break;

			case 'x': // uint - hex
				kputnumber(value, 16, false);
				break;

			case 'i': // int
				kputnumber(value, 10, true);
				break;
		}
	}
	
	va_end(arguments);
}
