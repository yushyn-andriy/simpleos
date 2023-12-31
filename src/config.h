#ifndef CONFIG_H
#define CONFIG_H


#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define SIMPLEOS_TOTAL_INTERRUPTS 512

// 100M heap size
#define SIMPLEOS_HEAP_SIZE_BYTES 104857600
#define SIMPLEOS_HEAP_BLOCK_SIZE 4096
#define SIMPLEOS_HEAP_ADDRESS 0x01000000
#define SIMPLEOS_HEAP_TABLE_ADDRESS 0x00007E00

#define SIMPLEOS_SECTOR_SIZE 512

#define SIMPLEOS_MAX_FILESYSTEMS 12
#define SIMPLEOS_MAX_FILE_DESCRIPTORS 512


#endif
