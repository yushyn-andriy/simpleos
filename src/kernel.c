#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "string/string.h"
#include "stdlib/stdlib.h"
#include "terminal/terminal.h"


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

	// Search amd initialize the disks
	disk_search_and_init();


	// Initialize the interrupt descriptor table
	idt_init();

	// Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
	
	// Switch to kernel paging chunk
	paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));


	// Enable paging
	enable_paging();


	char buf[512];
	struct disk *real_disk = disk_get(0);
	disk_read_block(real_disk, 0, 1, buf);

	// disk_read_sector(0, 1, buf);	
	// ata_lba_read(0, 1, buf);

	for(int i = 100; i<512; i++) {
		unsigned char *n = (unsigned char*) &buf[i];
		print(" ");
		print_hex(*n);
	}

	enable_interrupts();
}
