#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"

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




void print_int(size_t n) {
	char s[15];
	char tmp[15];

	int i = 0;
	while(n>0) {
		int rest = n % 10;
		n =  (n - rest) / 10;
		s[i] = rest + 0x30;
		// terminal_writechar(rest + 0x30, terminal_default_colour);
		// print("\n");
		i++;
	}
	s[i] = 0;
	tmp[i] = 0;

	i = i - 1;
	for(int j = i; j >= 0; j--) {
		tmp[i-j] = s[j];
	}
	print("address: ");
	print(tmp);
	print("\n");
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


void kernel_main()
{
	terminal_initialize();


	// inititalize the heap
	kheap_init();


	// Initialize the interrupt descriptor table
	idt_init();
	info();


	void *ptr = kmalloc(50);
	void *ptr2 = kmalloc(5000);
	if(ptr || ptr2) {
		print_int((size_t)ptr);
		print("\n");
		print_int((size_t)ptr2);
	}

	// outb(0x60, 0xff);
}
