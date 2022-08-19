#ifndef BASE_OPERATION_H
#define BASE_OPERATION_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>


typedef struct {
    char* bits;
    unsigned int size;
}BitMap;

#include "file_system.h"
#include "disk_manager.h"


BitMap* create_bitmap(unsigned int size);
void destroy_BitMap(BitMap *bitmap);

int split_path(path);
void inode_init(Inode* inode, int index, int is_directory, char* name );




#endif