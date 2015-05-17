#pragma once
#include "video.h"

extern const character_color early_panic_color;

#define EARLY_PANIC(message) do { \
		early_video_clear(); \
		early_video_put_string("KERNEL PANIC!\n", early_panic_color); \
		early_video_put_string(message, early_panic_color); \
		while (1) {} \
	} while(0)
