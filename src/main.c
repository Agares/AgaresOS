#include "early/video.h"

void kmain(int, int);

void kmain(int magic, int ptr) {
	magic = magic; ptr = ptr;

	character_color char_color = { 
		.foreground = COLOR_YELLOW,
		.background = COLOR_BLACK 
	};
 
	early_video_put_string("agos, version 0", char_color); 
	while(1){} 
}
