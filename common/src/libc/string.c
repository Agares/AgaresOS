#include "string.h"

inline size_t
strlen(const char *string) {
	size_t length = 0;

	for(; *string != '\0'; string++) {
		length++;
	}

	return length;
}

inline char *
strrev(char *string) {
	size_t length = strlen(string);
	char temp;

	for(size_t i = 0; i < length/2; i++) {
		temp = string[i];
		string[i] = string[length-i-1];
		string[length-i-1] = temp;
	}

	return string;
}
