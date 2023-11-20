#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

size_t  strlen(const char *s);
size_t  strnlen(const char *s, int max);
void strrev(char *s);
bool isdigit(char c);
int tonumericdigit(char c);
char digittochar(int n);
char* strcpy(char* dest, const char* src);
int strncmp(const char* str1, const char* str2, int n);
int strnlen_terminator(const char* str, int max, char terminator);
int istrncmp(const char* s1, const char* s2, int n);
char tolower(char s1);

#endif