#include "string.h"
#include <stdbool.h>

char tolower(char s1)
{
    if (s1 >= 65 && s1 <= 90)
    {
        s1 += 32;
    }

    return s1;
}

size_t strlen(const char *s) {
	size_t len = 0;
	while(*s != 0) {
		len++;
		s++;
	}
	return len;
}

size_t  strnlen(const char *s, int max)
{
	int i = 0;
	for(; i < max; i++)
	{
		if(s[i] == 0) break;
	}
	return i;
}


void strrev(char *s)
{
	size_t len = strlen(s);
	char tmp;
	for(int i = 0; i < len / 2; i++)
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

char digittochar(int n)
{
	return n + 0x30;
}


char* strcpy(char* dest, const char* src)
{
    char* res = dest;
    while(*src != 0)
    {
        *dest = *src;
        src += 1;
        dest += 1;
    }

    *dest = 0x00;

    return res;
}

int istrncmp(const char* s1, const char* s2, int n)
{
    unsigned char u1, u2;
    while(n-- > 0)
    {
        u1 = (unsigned char)*s1++;
        u2 = (unsigned char)*s2++;
        if (u1 != u2 && tolower(u1) != tolower(u2))
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}
int strncmp(const char* str1, const char* str2, int n)
{
    unsigned char u1, u2;

    while(n-- > 0)
    {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}

int strnlen_terminator(const char* str, int max, char terminator)
{
    int i = 0;
    for(i = 0; i < max; i++)
    {
        if (str[i] == '\0' || str[i] == terminator)
            break;
    }

    return i;
}
