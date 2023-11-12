#include "disk.h"
#include "io/io.h"
#include "config.h"
#include "status.h"
#include "memory/memory.h"

struct disk disk;


/*
    lba - Logical block address
    total - total number of sectors to be read
    buf - destination buffer

    32bit - 4Byte
    EAX - 0000 0100 0000 1000 0110 0000 0000 0111
    AX  -                     0110 0000 0000 0111
    AH  -                     0110 0000
    AL  -                               0000 0111
    ===========================================
    | 0000 0001 0010 0011 0100 0101 0110 0111 | ------> EAX

    |                     0100 0101 0110 0111 | ------> AX

    |                               0110 0111 | ------> AL

    |                     0100 0101           | ------> AH
    ===========================================
    shr eax, 8
    0001 0010 0011 0100 0101 0110 0111 1000
    0000 0000 0001 0010 0011 0100 0101 0110

*/
int disk_read_sector(int lba, int total, void* buf)
{
    outb(0x1F6, (unsigned char)(lba >> 24) | 0xE0);
    outb(0x1F2, (unsigned char)total);
    outb(0x1F3, (unsigned char)(lba));
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20);

    unsigned short* ptr = (unsigned short*) buf;
    for (int b = 0; b < total; b++)
    {
        // Wait for the buffer to be ready
        char c = insb(0x1F7);
        while(!(c & 0x08))
        {
            c = insb(0x1F7);
        }

        // Copy from hard disk to memory
        for (int i = 0; i < 256; i++)
        {
            *ptr = insw(0x1F0);
            ptr++;
        }

    }
    return 0;
}

void disk_search_and_init()
{
    memset(&disk, 0, sizeof(disk));
    disk.type = SIMPLEOS_DISK_TYPE_REAL;
    disk.sector_size = SIMPLEOS_SECTOR_SIZE;

}


struct disk *disk_get(int index)
{
    if(index!=0)
        return 0;

    return &disk;
}


int disk_read_block(struct  disk *idisk, unsigned int lba, int total, void *buf)
{
    if(idisk != &disk) return -EIO;

    return disk_read_sector(lba, total, buf);
}
