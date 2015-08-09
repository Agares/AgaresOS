#pragma once
#include "video.h"
#include "../macros.h"

extern const character_color early_panic_color;

#define EARLY_PANIC(message) do { \
		early_video_clear(); \
		early_video_put_string("KERNEL PANIC!\n", early_panic_color); \
		LOGF(__FILE__ ":" STR(__LINE__) "! %s", message); \
		while (1) {} \
	} while(0)
