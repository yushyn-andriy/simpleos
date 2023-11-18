#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "disk/streamer.h"
#include "stdlib/stdlib.h"
#include "terminal/terminal.h"
#include "memory/memory.h"
#include "string/string.h"
#include "fs/pparser.h"
#include "fs/fat/fat16.h"



void pkinfo() {
	printf("%s\n", "OS: SimpleOS V0.0.1");
	printf("%s\n", "Authors: Andriy Yushyn, Svitlana Yushyna.");
	printf("%s\n", "Email: baybaraandrey@gmail.com");
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

	// Search amd initialize the disks
	disk_search_and_init();

                      
	// Initialize filesystems
	fs_init();

	// Initialize the interrupt descriptor table
	idt_init();

	// Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
	
	// Switch to kernel paging chunk
	paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));


	// Enable paging
	enable_paging();


	enable_interrupts();

	printf("%s\n", strpath_root(pathparser_parse("0:/usr/lib/clib/stdlib.c", NULL)));
	printf("%s\n", strpath_root(pathparser_parse("0:/home/web/opt/cross/lib/gcc/i686-elf/10.2.0/include/stddef.h", NULL)));
	printf("%s\n", strpath_root(pathparser_parse("0:/usr/src/linux-source-6.1/include/uapi/linux/stddef.h", NULL)));
	

	// struct disk_stream *stream = diskstreamer_new(0);
	// diskstreamer_seek(stream, 0x200);

	// unsigned char c = 0;
	// diskstreamer_read(stream, &c, 1);
	// printf("%x\n", c);
}
