#include "kernel.h"


uint16_t *video_mem = 0;

uint16_t terminal_make_char(char c, char colour) {
	return (uint16_t) (colour << 8) | (uint16_t) c;
}

void terminal_initialize()
{
	video_mem = (uint16_t*)(0xB8000);
	for (int y = 0; y < VGA_HEIGHT; y++) {
		for(int x = 0; x < VGA_WIDTH; x++) {
			video_mem[((y*VGA_WIDTH) + x)] = terminal_make_char(' ', 0x1f); 
		}
	}
}



void hello() {
	uint16_t *video_mem = (uint16_t*)(0xB8000);
	video_mem[91] = terminal_make_char('A', 0x1f);
	video_mem[92] = terminal_make_char('B', 0x1f);
	video_mem[93] = terminal_make_char('C', 0x1f);
}

void kernel_main()
{
	terminal_initialize();
	hello();
}
