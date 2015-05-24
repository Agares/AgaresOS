#pragma once
#include "video.h"
#include "../libc/stdlib.h"

extern character_color early_log_colors;

#define LOG(str) do { \
		early_video_put_string(str, early_log_colors); \
	} while (0)

#define LOG_NUMBER(num, base) do { \
		char buffer[33]; \
		itoa(num, buffer, base); \
		early_video_put_string(buffer, early_log_colors); \
		early_video_put_string("\n", early_log_colors); \
} while (0)


#define LOG_NUMBER_HEX(num) do { \
		early_video_put_string("0x", early_log_colors); \
	   	LOG_NUMBER(num, 16); \
} while(0)


#define LOG_NUMBER_BIN(num) do { \
		early_video_put_string("0b", early_log_colors); \
	   	LOG_NUMBER(num, 2); \
} while(0)

#define LOG_NUMBER_DEC(num) LOG_NUMBER(num, 10)
