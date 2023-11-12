#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>


// Initialize terminal
void terminal_initialize();

// Write char to the terminal
void terminal_writechar(char c, char colour);

// 
void terminal_putchar(int x, int y, char c, char colour);


#endif
