#ifndef MEMORY_H
#define MEMORY_H


#include <stddef.h>

void *memset(void *ptr, int c, size_t size);
int memcmp(void *m1, void *m2, int n);
int memcpy(void *s1, void *s2, int count);

#endif
