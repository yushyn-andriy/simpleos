#include "string.h"


size_t strlen(const char *s) {
	size_t len = 0;
	while(*(s++)) len++;
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
