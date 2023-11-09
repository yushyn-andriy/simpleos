#ifndef KERNEL_H

#define KERNEL_H


#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define SIZE_T_MAX_LEN 10

void kernel_main();
void print(const char *str);

#endif

