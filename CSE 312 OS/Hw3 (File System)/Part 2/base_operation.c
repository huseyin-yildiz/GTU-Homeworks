#include "base_operation.h"

BitMap* create_bitmap(unsigned int bitsize) {
    BitMap* bitmap = (BitMap*)malloc(sizeof(BitMap));
    int size =  ceil(bitsize/8.0) ;
    bitmap->size = size;
    bitmap->bits = (char*)calloc(size, 1);
    return bitmap;
}

void rm_bitmap(BitMap *bitmap) {
    free(bitmap->bits);
    free(bitmap);
}

void set_bit(BitMap* bitmap, unsigned int index, unsigned int bit) {
    int byte = index >> 3;
    int n = sizeof(index)*8-3;
    int offset = ((unsigned) index << n) >> n;
    if (bit) {
        bitmap->bits[byte] |= 1 << (7-offset);
    } else {
        bitmap->bits[byte] &= ~(1 << (7-offset));
    }
}

int get_bit(BitMap* bitmap, unsigned int index) {
    unsigned int byte = index >> 3;
    unsigned int n = sizeof(index)*8-3;
    unsigned int offset = ((unsigned) index << n) >> n;
    if (bitmap->bits[byte] & (1 << (7- offset))) {
        return 1;
    } else {
        return 0;
    }
}



