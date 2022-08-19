#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <stdlib.h>
#include <stdio.h>


#define KB 1024

#define DISK_SIZE 4 * 1024 * 1024           /* in bytes */

#define INODE_B 0
#define DATA_B 1

#include "file_system.h"


typedef struct Disk {
    FILE* fptr;                 /* File descriptor of disk image            */
    int  block_size;            /* Block size in KByte                      */
    SuperBlock superblock;      
    short    is_open;           /* Whether or not disk is mounted or not    */
    
}Disk ;






void fetchBitMap(Disk* disk);


/* Disk Functions */

void    disk_create(const char* name, int block_size);
Disk *  disk_open(char *name);
void    disk_close(Disk *disk);
long int findSize(FILE * fp);


int read_data_block(Disk *disk, int block_index, void* buffer, int size);
int write_data_block(Disk *disk, int block_index, void *data, size_t size);
int reserve_block(Disk* disk, short reserve_type);                                                      /* Reserves a free data block if no then returns -1 */ 

uint8_t disk_read_byte(Disk *disk, int address);
void disk_write_byte(Disk *disk, int address, uint8_t byte);

void set_bit(Disk* disk,int isData, unsigned int index, unsigned int bit);
uint8_t get_bit(Disk* disk, int isData, unsigned int index);


Inode* read_inode(Disk* disk, int inode_index);
void write_inode(Disk* disk, Inode* inode);
int find_INode(Disk* disk, char* path, int start_inode);

void write_inode_data(Disk* disk, Inode* inode, void* data, size_t size, int block);
int read_inode_data(Disk* disk, int inode, void** data, int size);




#endif