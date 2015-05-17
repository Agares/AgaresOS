#include "early/video.h"
#include "libc/stdlib.h"

void kmain(int, int);

void kmain(int magic, int ptr) {
	magic = magic; ptr = ptr;

	character_color char_color = { 
		.foreground = COLOR_YELLOW,
		.background = COLOR_BLACK 
	};
 
	early_video_put_string("agos, version 0 ", char_color); 

	char buffer[33];
	itoa(1024, buffer, 2);
	early_video_put_string(buffer, char_color);
	early_video_put_char(' ', char_color);
	itoa(1024, buffer, 10);
	early_video_put_string(buffer, char_color);

	while(1){} 
}
