#ifndef BASE_OPERATION_H
#define BASE_OPERATION_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "file_system.h"

typedef struct {
    char* bits;
    unsigned int size;
}BitMap;

BitMap* create_bitmap(unsigned int size);
void destroy_BitMap(BitMap *bitmap);
void set_bit(BitMap* bitmap, unsigned int index, unsigned int bit);
int get_bit(BitMap* bitmap, unsigned int index);




#endif