#include "kheap.h"
#include "heap.h"
#include "config.h"
#include "kernel.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;


void kheap_init()
{
    int total_table_entries = SIMPLEOS_HEAP_SIZE_BYTES / SIMPLEOS_HEAP_BLOCK_SIZE;
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)(SIMPLEOS_HEAP_ADDRESS);
    kernel_heap_table.total = total_table_entries;

    void *end = (void*)(SIMPLEOS_HEAP_ADDRESS + SIMPLEOS_HEAP_SIZE_BYTES);
    int ret = heap_create(&kernel_heap, (void*)(SIMPLEOS_HEAP_ADDRESS), end, &kernel_heap_table);
    if( ret < 0 ) {
        print("Failed to create heap\n");
    }
}

void *kmalloc(size_t size)
{
    return heap_malloc(&kernel_heap, size);
}