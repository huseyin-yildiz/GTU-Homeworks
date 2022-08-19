#include "file_system.h"


void make_file_system(int size_in_KB, const char* file_name ){
    
    printf("Creating the empty disk...\n");
    disk_create(file_name,size_in_KB);

    Disk* disk = disk_open(file_name);
    disk->block_size = size_in_KB;

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


    disk->superblock = superblock;



    /*  Writing To Disk */


    


        /* superblock */
    fseek(disk->fptr,0,SEEK_SET);
    fwrite(&superblock,sizeof(SuperBlock),1,disk->fptr);
    


    BitMap *bit_map_block =  create_bitmap(superblock.num_of_disk_blocks);
    BitMap *i_node_bit_map =  create_bitmap(superblock.num_of_i_nodes);
    //memset(i_node_bit_map->bits ,'\0', sizeof(i_node_bit_map->bits));
    for(int i = 0 ; i <superblock.num_of_i_nodes ; ++i)
        set_bit(disk,0, i, UNUSED);
    

    for(int i = 0 ; i < superblock.num_of_disk_blocks ; ++i)
        set_bit(disk, 1, i, UNUSED);
    
    set_bit(disk, 0, 1, USED ); // root inode
    set_bit(disk, 1, 1, USED); // root data



    /* inodes */ 
    // fseek(disk->fptr,superblock.inode_start_addr,SEEK_SET);
    // for (int i = 0; i < INODE_NUM; i++)
    // {
    //     Inode inode;
    //     inode.valid = 0;
    //     fwrite(&inode,sizeof(Inode),1,disk->fptr);    
    // }
    
    Inode inode;
    inode_init(&inode,1,1,"\\");
    inode.direct_blocks[0] = 1;

    write_inode(disk,&inode);
    
    // DirectoryEntry dirs[2] = {  {.file_name=".",.inode_number=1},
    //                             {.file_name="..",.inode_number=1}};

    // char test[] = "asdf";
    // char b[4];
    // char* a = test;
    // write_inode_data(disk,&inode,test,sizeof(test),-1);


    // Inode* in2 = read_inode(disk,1);
    
    // DirectoryEntry d[2];
    // int i = read_inode_data(disk,inode.index,b,sizeof(b));

    // fseek(disk->fptr,13804,SEEK_SET);
    // fwrite(test,sizeof(test),1,disk->fptr);
    // fseek(disk->fptr,13804,SEEK_SET);
    // fread(b,sizeof(test),1,disk->fptr);



    // // inode bitmap
    // fseek(disk->fptr, superblock.i_node_bitmap_addr, SEEK_SET);
    // fwrite(i_node_bit_map->bits, sizeof(char), INODE_NUM/8, disk->fptr);

    // // data bitmap
    // fseek(disk->fptr, superblock.data_bitmap_addr, SEEK_SET);
    // fwrite(bit_map_block->bits, sizeof(char), superblock.num_of_disk_blocks/8, disk->fptr);








    // data blocks are random values
    // char* free_block = (char*)malloc(sizeof(char)*superblock.block_size*KB);
    
    // for (int i = 0; i < superblock.num_of_disk_blocks; i++)
    //     disk_write(disk,i,free_block);
    

    

    // fwrite(,);
    

    // write_super_block(size_in_KB, file_name);
    // write_inodes(); and bitmap
    // set_data_blocks();  and bitmap
    
    disk_close(disk);

}


int main122234(int argc, char const *argv[])
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
