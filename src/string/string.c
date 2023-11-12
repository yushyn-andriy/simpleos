#include "string.h"
#include <stdbool.h>


size_t strlen(const char *s) {
	size_t len = 0;
	while(*s != 0) {
		len++;
		s++;
	}
	return len;
}

size_t  lstrlen(const char *s, unsigned int limit)
{
	size_t len = 0;
	while(*s != 0) {
		len++;
		s++;
		if(len >= limit) return -1;	
	}
	return len;
}


void strrev(char *s)
{
	size_t len = strlen(s);
	char tmp;
	for(int i = 0; i < len/2; i++)
	{
		tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
	}
}

bool isdigit(char c)
{
	return (0x30 <= c && c <= 0x39);
}

int tonumericdigit(char c)
{
	return c - 0x30;
}
