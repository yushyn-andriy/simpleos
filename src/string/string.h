#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

// get string length
size_t  strlen(const char *s);

// reverse string in place
void strrev(char *s);

#endif