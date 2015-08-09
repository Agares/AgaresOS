#pragma once
#include <stdint.h>

typedef enum {
	COLOR_BLACK = 0,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_BROWN,
	COLOR_LIGHT_GRAY,
	COLOR_DARK_GRAY,
	COLOR_LIGHT_BLUE,
	COLOR_LIGHT_GREEN,
	COLOR_LIGHT_CYAN,
	COLOR_LIGHT_RED,
	COLOR_LIGHT_MAGENTA,
	COLOR_YELLOW,
	COLOR_WHITE
} color;

typedef struct {
	color foreground;
	color background;
} character_color;

void early_video_clear(void);
void early_video_put_char(char, character_color);
void early_video_put_string(const char*, character_color);
