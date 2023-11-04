#include "kernel.h"
#include <stdint.h>

void kernel_main()
{
	char * video_mem = (char*)(0xB8000);
	video_mem[0] = 'a';	
	video_mem[1] = 3;	
	
	video_mem[2] = 'c';	
	video_mem[3] = 3;	
	
	video_mem[4] = 'b';	
	video_mem[5] = 3;	
}
