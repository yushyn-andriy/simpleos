#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// get string length
size_t  strlen(const char *s);

// get string lenght with limit
size_t  lstrlen(const char *s, unsigned int limit);

// reverse string in place
void strrev(char *s);

// 
bool isdigit(char c);

// 
int tonumericdigit(char c);

#endif