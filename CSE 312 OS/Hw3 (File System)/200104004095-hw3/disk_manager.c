#include "disk_manager.h"



// void fetchBitMap(Disk* disk){               // Do not forget to free the bitmap     //  INODE_B - DATA_B
    
//     int bitmap_addr;
//     int size;
    
//     bitmap_addr = disk->superblock.data_bitmap_addr;
//     size = disk->superblock.num_of_disk_blocks;

//     int byte_size = ceil(size/8.0);
//     disk->bitmap_data.bits = (char*) calloc( byte_size,sizeof(char)  );

//     fseek(disk->fptr, bitmap_addr, SEEK_SET);
//     fread(disk->bitmap_data.bits, sizeof(uint8_t),size, disk->fptr);
    
//     //
//     bitmap_addr = disk->superblock.i_node_bitmap_addr;
//     size = disk->superblock.num_of_i_nodes;
    
//     byte_size = ceil(size/8.0);
//     disk->bitmap_inode.bits = (char*) calloc( byte_size,sizeof(char)  );

//     fseek(disk->fptr, bitmap_addr, SEEK_SET);
//     fread(disk->bitmap_inode.bits, sizeof(uint8_t),size, disk->fptr);
// }



Disk *  disk_open(char *name){
    Disk* disk = (Disk*) malloc(sizeof(Disk));
    disk->fptr = fopen(name,"rb+");

    if(disk->fptr == NULL)
        printf("Disk open Error");
    
    
    // // long int size = findSize(disk->fptr);
    // // char zero[] = "1234";
    // // if(size == 0)
    // //     for (int i = 0; i < DISK_SIZE; i++)
    // //         fwrite(&zero,sizeof(char),1,disk->fptr);
           
    // else if(size != DISK_SIZE )
    // {
    //     printf("Error: Disk size is wrong ");
    //     exit(EXIT_FAILURE);
    // }
    else
    {
        fread(&(disk->superblock),sizeof(SuperBlock),1,disk->fptr);
        disk->is_open = 1;
        disk->block_size = disk->superblock.block_size;
    }
    
    return disk;
}



void disk_close(Disk *disk){
    fclose(disk->fptr);
    free (disk);
}


int read_data_block(Disk *disk, int block_index, void* buffer, int size){         // Do not foreget to free the data
    if(disk -> block_size == 0)
        printf("Error: Block Size not defined");

    if(size > disk->block_size*KB)
        fprintf(stderr,"The given size is bigger than block size\n");

    int offset =  disk->superblock.data_block_addr + block_index*(disk->block_size*KB );
    

    if ( fseek(disk->fptr, offset, SEEK_SET) )
        printf("Disk read error");    
    else{
        return fread(buffer, size, 1, disk->fptr);
    }
}

int write_data_block(Disk *disk, int block_index, void *data, size_t size){
    
    int offset =  disk->superblock.data_block_addr + block_index*(disk->block_size*KB );
    
    if(disk -> block_size == 0)
        printf("Error: Block Size not defined");
    
    else if ( fseek(disk->fptr, offset, SEEK_SET) )
        printf("Disk write error to given index");

    else if(disk->block_size*KB < size)
        printf("Error: Given data size is bigger than block size\n");
    else{
        char* t = data;
        fseek(disk->fptr, offset, SEEK_SET);
        
        int w = fwrite(t,size , 1, disk->fptr);
        int p = ftell(disk->fptr);
        return w;
    }
}

uint8_t disk_read_byte(Disk *disk, int address){
    
    fseek(disk->fptr, address, SEEK_SET);
    uint8_t val;
    fread(&val,sizeof(uint8_t),1,disk->fptr);
    return val;
}

void disk_write_byte(Disk *disk, int address, uint8_t byte){
    int cursor = ftell(disk->fptr);
    fseek(disk->fptr, address, SEEK_SET);
    uint8_t val;
    fwrite(&byte,sizeof(uint8_t),1,disk->fptr);
    
}


long int findSize(FILE * fp)
{
  
    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file
    long int res = ftell(fp);
  
    // closing the file
    fclose(fp);
  
    return res;
}



void disk_create(const char* name, int block_size)
{
    Disk* disk = (Disk*) malloc(sizeof(Disk));
    disk->fptr = fopen (name, "wb");
    disk->block_size = block_size;
    if(disk->fptr == NULL)
    {
        fprintf(stderr, "%s\n", "Error creating disk. Exiting program." );
        exit(EXIT_FAILURE);
    }
    fseek(disk->fptr, DISK_SIZE , SEEK_SET); //go to 1 MB forward.
    fputc('\0', disk->fptr); //place the EOF
    rewind(disk->fptr);   //go back to beginning of the file.
    // fclose(disk->fptr);
    disk_close(disk);
}


Inode* read_inode(Disk* disk, int inode_index){              /* Do not forget to free returned inode */
    if(disk->is_open)
    {
        Inode * inode = (Inode*)malloc(sizeof(Inode));
        int inode_addr = disk->superblock.inode_start_addr + disk->superblock.inode_size * inode_index;
        fseek(disk->fptr, inode_addr , SEEK_SET);
        fread(inode,sizeof(Inode),1,disk->fptr);
        return inode;
    }
    else
        fprintf(stderr, "Given disk is not open");
}

void write_inode(Disk* disk, Inode* inode){
    if(inode->index > INODE_NUM)
        fprintf(stderr,"!!! The inode index is wrong to write to disk\n");
    else{
        int inode_addr = disk->superblock.inode_start_addr + disk->superblock.inode_size * inode->index;
        fseek(disk->fptr, inode_addr , SEEK_SET);
        fwrite(inode,sizeof(Inode),1,disk->fptr);
        set_bit(disk,0,inode->index,USED);
    }
}






void write_inode_data(Disk* disk,Inode* inode, void* data, size_t size, int block)      // block =-1 for append
{
    char* ptr = data;
    if(size <= 0)
    {
        write_inode(disk,inode);        // updating inode
        return;
    }

    u_int16_t target_block;
    int byte_index=0;

    if(block == 0)
        inode->file_size_bytes = 0;
    
    float bs = (float)disk->block_size*KB;
    
    if(block == -1 && inode->file_size_bytes > 0)         // append
    {
        block = ceil(inode->file_size_bytes / bs);
        byte_index = inode->file_size_bytes % (disk->block_size*KB);
        int remain = (disk->block_size*KB - byte_index);
        int fill_size = size % remain;
        int addr = disk->superblock.data_block_addr + (inode->direct_blocks[block]) * disk->block_size + byte_index;
        fseek(disk->fptr,addr,SEEK_SET);
        fwrite(data,fill_size,1,disk->fptr);
        size -= fill_size;
        if(size > 0){
            block++; 
        }
    }
    if(block == -1)
        block = ceil(inode->file_size_bytes / bs);
    
    if(block < DIRECT_BLOCK_SIZE)
    {
        if( inode->direct_blocks[block] == NO_BLOCK )       // block allocation
        {
             target_block = reserve_block(disk,DATA_B);
            inode->direct_blocks[block] = target_block;
        }
        else
            target_block = inode->direct_blocks[block];

        size_t write_size;
        if(size > disk->block_size*KB)
            write_size = disk->block_size*KB;
        else
            write_size = size;

        char* t = data;
        int aa = write_data_block(disk, target_block, data, write_size);

        inode->file_size_bytes += write_size;
        
        return write_inode_data(disk, inode, &data[write_size], size - write_size, ++block );
    }
    
    printf("Data size is bigger than supported for inode \n");

    // else if(block < DIRECT_BLOCK_SIZE*2)        // single indirect
    // {

    // }
    // double 

    // Triple


}


int read_inode_data(Disk* disk, int inode_index, void** data, int size){     /* Do not forget to free returned data  after use // size=-1 for all */ 
    Inode* inode = read_inode(disk,inode_index);
    if(size == -1)
        size = inode->file_size_bytes;

    int remain = size % (disk->block_size*KB + 1);

    float bs = (float)(disk->block_size*KB);
    int until = ceil(remain /bs);

    *data = malloc(remain);
    int read_index = 0;

    if(until > DIRECT_BLOCK_SIZE)
        fprintf(stderr,"Unsupported size to read !! \n");
    
    for (int i = 0; i < until-1; i++)
    {
            read_index += read_data_block(disk,inode->direct_blocks[i],&data[read_index],disk->block_size*KB);
            remain - disk->block_size*KB;
    }
    void* addr = data;    
     read_data_block(disk,inode->direct_blocks[until-1],*data,remain);
    read_index += remain;
    char* d = *data;
    return read_index;
}


int reserve_block(Disk* disk, short reserve_type){          // INODE_B - DATA_B

    int isData,size;

    if(reserve_type == INODE_B)
    {
        isData = 0;
        size = disk->superblock.num_of_i_nodes;
    }
    else{
        isData = 1;
        size = disk->superblock.num_of_disk_blocks;
    }

    for (int i = 1; i < size; i++)
    {
        if(get_bit(disk,isData,i) == UNUSED )
        {
            set_bit(disk,isData,i,USED);
            return i;
        }
    }
    
}



// Takes a path and returns the inode
int find_INode(Disk* disk, char* path, int start_inode){
    
    int token_len = 0;
    char * token;
    if(start_inode == disk->superblock.root_dir_index)
        token = strtok(path, "\\");
    else
        token = strtok(NULL, "\\");

    if(token == NULL)
        return start_inode;

    token_len = strlen(token);

    DirectoryEntry* entries;
    int len = read_inode_data(disk,start_inode,&entries,-1);
    len /= sizeof(DirectoryEntry);

    for(int i=0; i<len; i++)
        if( strcmp(entries[i].file_name, token) == 0 )
            return find_INode(disk, &path[token_len], entries[i].inode_number);
            
            

    return -1;              // If the inode is not found
    
}





void set_bit(Disk* disk,int isData, unsigned int index, unsigned int bit) {     // sets the bit at the given index
    uint8_t data;
    int addr;

    if(isData)
        addr = disk->superblock.data_bitmap_addr + (index/8);
    else       // inode bit
        addr = disk->superblock.i_node_bitmap_addr + (index/8);
    
    data = disk_read_byte(disk,addr);

    // or-ing
    int byte = index >> 3;
    int n = sizeof(index)*8-3;
    int offset = ((unsigned) index << n) >> n;
    if (bit) {
        data |= 1 << (7-offset);
    } else {
        data &= ~(1 << (7-offset));
    }

    disk_write_byte(disk,addr,data);

}

uint8_t get_bit(Disk* disk, int isData, unsigned int index) {
    uint8_t data;
    int addr;

    if(isData)
        addr = disk->superblock.data_bitmap_addr + (index/8);
    else       // inode bit
        addr = disk->superblock.i_node_bitmap_addr + (index/8);
    
    data = disk_read_byte(disk,addr);

    unsigned int byte = index >> 3;
    unsigned int n = sizeof(index)*8-3;
    unsigned int offset = ((unsigned) index << n) >> n;
    if (data & (1 << (7- offset))) {
        return 1;
    } else {
        return 0;
    }
}

















int main122232(){         /* Disk manager test */

    make_file_system(4,"disk");
    
    Disk * disk = disk_open("disk");
    Inode inode;
    strcpy(inode.name,"\\");
    inode.is_direcory = 1;
    inode.file_size_bytes = 0;
    for (int i = 0; i < DIRECT_BLOCK_SIZE; i++)
        inode.direct_blocks[i] = 0;
    inode.single_indirect_block = 0;
    inode.double_indirect_block = 0;
    inode.triple_indirect_block = 0;
    inode.index = 0;

    write_inode(disk,&inode);
    

    Inode* inode2 = read_inode(disk,0);
    printf("isDir:%d Name:%s\n",inode2->is_direcory, inode2->name);
    


    DirectoryEntry dirs[2] = {  {.file_name=".",.inode_number=0},
                                {.file_name="..",.inode_number=0}};


    
    char test[] = "asdf1234";
    char test1[8];
    
    //write_data_block(disk,disk->superblock.data_block_addr+200,test,9);
    //read_data_block(disk,disk->superblock.data_block_addr+200,test1,9);

    int size = sizeof(test);
    write_inode_data(disk,inode2,test,size,-1);
    

    
    DirectoryEntry* dirTest;
    read_inode_data(disk,1,test1,size);
    DirectoryEntry* di3 = &dirTest[1];
    
}


