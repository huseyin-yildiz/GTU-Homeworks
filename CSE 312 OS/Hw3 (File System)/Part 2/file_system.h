#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#define DIRECT_BLOCK_SIZE 8
#define FILE_NAME_MAX 14
#define MAGIC_NUMBER       (0xf0f01690)

#define INODE_NUM 2000          /* Must be dividable to 8 */

#define USED 0
#define UNUSED 1


#include <stdint.h>
#include <time.h>
#include <string.h>
#include "base_operation.h"

#include "disk_manager.h"





typedef struct SuperBlock{             // SuperBlock Struct
    
    uint32_t    magic_number;                   /* File system magic number */
    uint8_t     block_size;                     /* Size of a block in KB */
    uint16_t    inode_size;                     /* Size of a i-node in bytes */
    uint16_t    num_of_i_nodes;                 /* Number of i_nodes */
    uint32_t    num_of_disk_blocks;             /* Number of disk blocks */
    
    // segment adresses
    uint16_t    inode_start_addr;
    uint16_t    data_bitmap_addr;              /* the address of data block bitmap */
    uint16_t    i_node_bitmap_addr;            /* the address of i_node bitmap */  
    uint16_t    data_block_addr;

    
    uint16_t    root_dir_index;
    
    char file_name[FILE_NAME_MAX];

}SuperBlock;


typedef struct FileSystem{             // File system Struct 
    //struct SuperBlock super_block;
}FileSystem;









typedef struct Inode
{
    short valid;
    uint32_t file_size_bytes;                         /* File size in bytes */
    struct tm  creation_time;
    struct tm last_access_time;
    struct tm last_modification_time;
    short is_direcory;

    uint16_t direct_blocks[DIRECT_BLOCK_SIZE];
    uint16_t single_indirect_block;
    uint16_t double_indirect_block;
    uint16_t triple_indirect_block;

}Inode;





// typedef union Block {
//     SuperBlock  superblock;                     /* View block as superblock */
//     Inode       inodes[INODES_PER_BLOCK];       /* View block as inode */
//     uint32_t    pointers[POINTERS_PER_BLOCK];   /* View block as pointers */
//     char        data[BLOCK_SIZE];               /* View block as data */
// };






void make_file_system(int size_in_KB, const char *file_name );







#endif
