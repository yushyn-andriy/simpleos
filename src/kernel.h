#ifndef KERNEL_H

#define KERNEL_H


#include <stdint.h>
#include <stddef.h>


#define TERMINAL_DEFAULT_COLOR 0x1F
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define SIZE_T_MAX_LEN 10

#define SIMPLEOS_MAX_PATH 108


void kernel_main();

#endif

