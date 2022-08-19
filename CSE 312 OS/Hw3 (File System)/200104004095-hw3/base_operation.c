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


int split_path(char *path){
    for (int i = strlen(path)-1; 0 <= i; i--)
        if(path[i] == '\\')
            return i;
}



void inode_init(Inode* inode, int index, int is_directory, char* name ){


    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );

    inode->creation_time = *info;

    for (int i = 0; i < DIRECT_BLOCK_SIZE; i++)
        inode->direct_blocks[i] = 0;
    inode->single_indirect_block = 0;
    inode->double_indirect_block = 0;
    inode->triple_indirect_block = 0;

    inode->index = index;
    inode->file_size_bytes = 0;
    inode->is_direcory = is_directory;

    inode->last_modification_time = inode->creation_time;
    
    
    
    strcpy(inode->name, name);

}