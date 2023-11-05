#include "kernel.h"
#include "idt/idt.h"

uint16_t *video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;
char terminal_default_colour = 0x1F;



uint16_t terminal_make_char(char c, char colour) {
	return (uint16_t) (colour << 8) | (uint16_t) c;
}

void terminal_putchar(int x, int y, char c, char colour) {
	video_mem[( (y * VGA_WIDTH) + x)] = terminal_make_char(c, colour);
}


void terminal_writechar(char c, char colour) {
	if (c == '\n') {
		terminal_row += 1;
		terminal_col = 0;
		return;
	}
	terminal_putchar(terminal_col, terminal_row, c, colour);
	
	terminal_col += 1;
	if(terminal_col >= VGA_WIDTH) {
		terminal_col = 0;
		terminal_row += 1;
	}
}

void terminal_initialize()
{
	video_mem = (uint16_t*)(0xB8000);
	for (int y = 0; y < VGA_HEIGHT; y++) {
		for(int x = 0; x < VGA_WIDTH; x++) {
			terminal_putchar(x, y, ' ', terminal_default_colour);	
		}
	}
}


size_t strlen(const char *str) {
	size_t len = 0;
	while(*(str++)) len++;
	return len;
}


void print(const char *str)
{
	size_t len = strlen(str);
	for(int i = 0; i<len; i++)
		terminal_writechar(str[i], terminal_default_colour);
}



void terminal_ascii_test() {
	for(char ch = 0x21; ch<=0x7e; ch++)
		terminal_writechar(ch, terminal_default_colour);
}

void info() {
	// terminal_ascii_test();
	print("OS: SimpleOS V0.0.1\n");
	print("Authors: Andriy Yushyn, Svitlana Yushyna.\n");
	print("Email: baybaraandrey@gmail.com\n");
}

extern void problem();

void kernel_main()
{
	terminal_initialize();

	// Initialize the interrupt descriptor table
	idt_init();
	info();
	problem();
}
