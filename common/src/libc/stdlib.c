#include <stddef.h>
#include "stdlib.h"
#include "string.h"

inline char *
itoa(int value, char *string, int base) {
	int index = 0;
	static char map[] = "0123456789abcdefghijklmnopqrstuwxyz";

	if(base == 10 && value < 0) {
		string[index++] = '-';
	}

	do
	{
		string[index++] = map[value % base];
	} while(value /= base);

	string[index++] = '\0';
	strrev(string); // todo handle "-" sign
	return string;
}
