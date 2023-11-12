#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <stdint.h>

int atoi(const char *nptr);
int itoa(const char *nptr);
void print(const char *str);
void print_size_t(size_t n);
void print_hex(unsigned int num);

#endif
