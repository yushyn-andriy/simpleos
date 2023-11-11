#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"


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



// reverse string in place
void strrev(char *s)
{
	size_t len = strlen(s);
	char tmp;
	for(int i = 0; i < len/2; i++)
	{
		tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
	}
}

void print_size_t(size_t n) {
	char res[SIZE_T_MAX_LEN+1];

	if(n == 0) {
		res[0] = 0x30;
		res[1] = 0;
		goto pout;
	} 


	int i = 0;
	while(n>0) {
		int rest = n % 10;
		n =  (n - rest) / 10;
		res[i] = rest + 0x30;
		i++;
	}
	res[i] = 0;
	strrev(res);

pout:
	print(res);
}


void terminal_ascii_test() {
	for(char ch = 0x21; ch<=0x7e; ch++)
		terminal_writechar(ch, terminal_default_colour);
}

void pkinfo() {
	// terminal_ascii_test();
	print("OS: SimpleOS V0.0.1\n");
	print("Authors: Andriy Yushyn, Svitlana Yushyna.\n");
	print("Email: baybaraandrey@gmail.com\n");
}

static struct paging_4gb_chunk *kernel_chunk;
void kernel_main()
{
	// initialize terminal
	terminal_initialize();

	// print kernel info
	pkinfo();

	// inititalize the heap
	kheap_init();


	// Initialize the interrupt descriptor table
	idt_init();

	// Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
	
	// Switch to kernel paging chunk
	paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));


	char *ptr = kzalloc(4096);
	paging_set(paging_4gb_chunk_get_directory(kernel_chunk), (void*)0x1000, (uint32_t)ptr | PAGING_ACCESS_FROM_ALL | PAGING_IS_PRESENT | PAGING_IS_WRITEABLE);

	// Enable paging
	enable_paging();

	char *ptr2 = (void*)0x1000;
	ptr2[0] = 'A';
	ptr2[1] = 'B';
	ptr2[2] = 'C';
	
	print(ptr2);
	
	print(ptr);
	
	// from this place we are able to enable interrupts
	enable_interrupts();




	// void *ptr = kmalloc(10);
	// void *ptr2 = kmalloc(10);
	// if(ptr || ptr2) {
	// 	print_size_t((size_t)ptr);
	// 	print("\n");
	// 	print_size_t((size_t)ptr2);
	// 	print("\n");
	// }

	// outb(0x60, 0xff);
}
