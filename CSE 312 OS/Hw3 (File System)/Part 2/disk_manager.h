#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include "file_system.h"

#define KB 1024

#define DISK_SIZE 4 * 1024 * 1024           /* in bytes */



typedef struct Disk {
    FILE* fptr;                 /* File descriptor of disk image        */
    int  block_size;        /* Block size in Byte                   */

    // size_t  reads;           /* Number of reads to disk image        */
    // size_t  writes;          /* Number of writes to disk image       */
    // bool    mounted;         /* Whether or not disk is mounted       */
}Disk ;


/* Disk Functions */

Disk *  disk_open(char *name);
void    disk_close(Disk *disk);


int disk_read(Disk *disk, int block_index, char *data);
int disk_write(Disk *disk, int block_index, char *data);
long int findSize(FILE * fp);
Disk * disk_create(char* name, int block_size);


#endif