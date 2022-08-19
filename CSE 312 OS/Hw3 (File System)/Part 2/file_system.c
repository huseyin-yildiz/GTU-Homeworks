#include "file_system.h"


void make_file_system(int size_in_KB, const char* file_name ){
    
    printf("Creating the empty disk...\n");
    
    Disk * disk = disk_create(file_name,size_in_KB);
    SuperBlock superblock;
    superblock.block_size = size_in_KB;
    strcpy(superblock.file_name, file_name);
    superblock.magic_number = MAGIC_NUMBER;
    
    superblock.inode_size = sizeof(Inode);
    superblock.num_of_i_nodes = INODE_NUM;
    
    int data_block_space = (DISK_SIZE/KB - 1*size_in_KB - (INODE_NUM*sizeof(Inode) / KB + 1) );
    superblock.num_of_disk_blocks = data_block_space / size_in_KB;

    superblock.root_dir_index = 1 ;
    
    superblock.inode_start_addr     = size_in_KB*KB;
    superblock.i_node_bitmap_addr   = superblock.inode_start_addr + INODE_NUM * sizeof(Inode);
    superblock.data_bitmap_addr     = superblock.i_node_bitmap_addr + INODE_NUM / 8;
    superblock.data_block_addr      = superblock.data_bitmap_addr + superblock.num_of_disk_blocks / 8 + ( superblock.num_of_disk_blocks % 8 != 0);



    
    
    BitMap *bit_map_block =  create_bitmap(superblock.num_of_disk_blocks);
    BitMap *i_node_bit_map =  create_bitmap(superblock.num_of_i_nodes);
    //memset(i_node_bit_map->bits ,'\0', sizeof(i_node_bit_map->bits));
    for(int i = 0 ; i <superblock.num_of_i_nodes ; ++i)
        set_bit(i_node_bit_map, i, UNUSED);
    

    for(int i = 0 ; i < superblock.num_of_disk_blocks ; ++i)
        set_bit(bit_map_block, i, UNUSED);
    
    set_bit(i_node_bit_map,0, USED ); // root inode
    set_bit(bit_map_block, 0, USED); // root data



    /*  Writing To Disk */

    fseek(disk->fptr,0,SEEK_SET);
    fwrite(&superblock,sizeof(SuperBlock),1,disk->fptr);

    fseek(disk->fptr,superblock.inode_start_addr,SEEK_SET);
    for (int i = 0; i < INODE_NUM; i++)
    {
        Inode inode;
        inode.valid = 0;
        fwrite(&inode,sizeof(Inode),1,disk->fptr);    
    }

    // inode bitmap
    fseek(disk->fptr, superblock.i_node_bitmap_addr, SEEK_SET);
    fwrite(i_node_bit_map->bits, sizeof(char), INODE_NUM/8, disk->fptr);

    // data bitmap
    fseek(disk->fptr, superblock.data_bitmap_addr, SEEK_SET);
    fwrite(bit_map_block->bits, sizeof(char), superblock.num_of_disk_blocks, disk->fptr);

    // data blocks are random values
    char* free_block = (char*)malloc(sizeof(char)*superblock.block_size*KB);
    
    for (int i = 0; i < superblock.num_of_disk_blocks; i++)
        disk_write(disk,i,free_block);
    

    

    // fwrite(,);
    

    // write_super_block(size_in_KB, file_name);
    // write_inodes(); and bitmap
    // set_data_blocks();  and bitmap
    
    

}


int main(int argc, char const *argv[])
{
    if(argc != 3)
        fprintf(stderr,"Argument error example usage:(makeFileSystem 4 mySystem.dat)\n");
    else
    {
        int blocksize;
        sscanf(argv[1],"%d",&blocksize);
        make_file_system(blocksize,argv[2]);
    }
        
    return 0;
}
