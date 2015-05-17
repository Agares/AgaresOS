#include "video.h"

static const int width  = 80,
		  height = 25;

static volatile uint16_t *video_memory = (volatile uint16_t*)0xb8000;
static int video_cursor = 0;

static inline void
check_for_video_memory_overflow() {
	if (video_cursor == width*height) {
		early_video_clear();
	}
}

static inline uint16_t 
pack_character_with_color(unsigned char character, character_color char_color) {
	uint16_t color_flags = (uint16_t)((char_color.foreground) | (char_color.background << 4));
	return (uint16_t)(((int)character) | (color_flags << 8));
}

static inline void
new_line() {
	int y = video_cursor / width;

	video_cursor = (y+1)*width;
	check_for_video_memory_overflow();
}

void 
early_video_clear(void) {
	for(int i = 0; i < width*height; i++) {
		video_memory[i] = 0;
	}
	video_cursor = 0;
}

inline void 
early_video_put_char(char character, character_color char_color) {
	check_for_video_memory_overflow();
	
	switch(character) {
		case '\n':
			new_line();
			break;
		default:
			video_memory[video_cursor++] = pack_character_with_color((unsigned char)character, char_color);
			break;
	}
}

void 
early_video_put_string(const char *string, character_color char_color) {
	for(; *string != '\0'; string++) {
		early_video_put_char(*string, char_color);
	}
}
