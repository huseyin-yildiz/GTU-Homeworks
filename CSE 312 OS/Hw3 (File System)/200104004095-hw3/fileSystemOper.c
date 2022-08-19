#include"fileSystemOper.h"

Inode new_file(Disk* disk, char name[FILE_NAME_MAX], int isDirecory){     // creates a inode in the disk and returns the inode 

    Inode new_inode;
    int inode_index = reserve_block(disk, INODE_B);
    inode_init(&new_inode,inode_index,isDirecory,name);

    write_inode(disk,&new_inode);           // writing to the disk
    return new_inode;
}


void dumpe2fs(Disk* disk){
    
    int file_num = disk->superblock.num_of_i_nodes - get_free_block_size(disk,INODE_B);

    printf("Block Count                         : %d \n", disk->superblock.num_of_disk_blocks);
    printf("Free Block Count                    : %d \n", get_free_block_size(disk,DATA_B));
    printf("Number of Files and Directories     : %d \n", file_num );
    printf("Block size                          : %d KB\n", disk->block_size);

}


int get_free_block_size(Disk* disk, int type){
    int tot = disk->superblock.num_of_disk_blocks;
    int isData = 1;
    if(type == INODE_B)
    {
        tot = disk->superblock.num_of_i_nodes;
        isData = 0;
    }

    int sum = 0;
    for (int i = 0; i < tot;  i++)
        if(get_bit(disk,isData,i) == UNUSED)
            sum++;

    return sum;
}





int add_file(Disk* disk, int dest_inode_num, Inode* new_inode){         // adds the given inode to the destination inode(directory)
    DirectoryEntry* entries;
    int entry_size = read_inode_data(disk,dest_inode_num,&entries,-1);
    
    
    for (int i = 0; i < (entry_size / sizeof(DirectoryEntry)); i++)
    {
        if( strcmp(entries[i].file_name, new_inode->name) == 0 )
        {
            printf("There is a file or directory with this name !! \n");
            set_bit(disk,0,new_inode->index,UNUSED);
            return -1;
        }
    }
    
    
    entry_size += sizeof(DirectoryEntry);
    realloc(entries,entry_size);

    int index = entry_size / sizeof(DirectoryEntry);
    DirectoryEntry* d = &entries[index-1];
    entries[index-1].inode_number = new_inode->index;
    
    strcpy(entries[index-1].file_name, new_inode->name);
    
    

    Inode* root_inode = read_inode(disk,dest_inode_num);
    write_inode_data(disk,root_inode,entries,entry_size,0);
    
    if(new_inode->is_direcory)
    {   
        DirectoryEntry dirs[2] = {  {.file_name=".",.inode_number = new_inode->index},
                                    {.file_name="..",.inode_number = dest_inode_num }};
        write_inode_data(disk,new_inode,dirs,sizeof(dirs),0);
    }

    free(root_inode);
    return new_inode->index;
}



void dir(Disk* disk, char * path){
    
    int inode_num = find_INode(disk,path,1);
    
    DirectoryEntry* dirs;
    int size = read_inode_data(disk, inode_num, &dirs, -1) / sizeof(DirectoryEntry);

    for (int i = 0; i < size; i++)
    {
        int index = dirs[i].inode_number;
        Inode* inode = read_inode(disk, index);
        struct tm t = inode->last_modification_time;
        printf("%d-%d-%d  %2d:%2d \t",t.tm_year+1900, t.tm_mon, t.tm_mday,t.tm_hour,t.tm_min );
        if(inode->is_direcory)
            printf("<DIR>");
        else
            printf("     ");
        printf("\t\t%-14s \n",dirs[i].file_name);
    }

    if(size == 0)
        printf("There is no such path \n");
    

}

void mkdir(Disk* disk, char* path){
    
    int i = split_path(path);
    char * name = &path[i+1];
    int dest_inode_num = 1;

    if(i != 0){
        char* dir = malloc(i+1); 
        strncpy(dir,path,i);
        dir[i] = NULL;
        int start_inode = 1;
        dest_inode_num = find_INode(disk,dir,start_inode);
    }
    
    if(dest_inode_num == -1)
        fprintf(stderr, "The given path is wrong \n");

    Inode inode = new_file(disk, name, 1);
    add_file(disk, dest_inode_num, &inode );
    
}







int write(Disk* disk, char* path, char* file_name){
    FILE* f = fopen(file_name,"r");
    if(f == NULL){
        printf("No such file \n");
        return -1;
    }

    
    int i = split_path(path);
    char * name = &path[i+1];
    int dest_inode_num = 1;

    if(i != 0){
        char* dir = malloc(i+1); 
        strncpy(dir,path,i);
        dir[i] = NULL;
        int start_inode = 1;
        dest_inode_num = find_INode(disk,dir,start_inode);
    }
    
    Inode inode = new_file(disk, name, 0);
    if(add_file(disk, dest_inode_num, &inode ) == -1)
        return -1;

    // copying to the free inode from given file
    
    
    fseek(f, 0L, SEEK_END);
    int size = ftell(f);
    char* buffer = malloc(size);
    fseek(f,0,SEEK_SET);
    fread(buffer,size,1,f);
    
    write_inode_data(disk, &inode, buffer, size, 0);

    free(buffer);
    fclose(f);
}



int read(Disk* disk, char* path, char* file_name){
    int inode_num = find_INode(disk,path,disk->superblock.root_dir_index);
    char* buffer;
    int size = read_inode_data(disk,inode_num, &buffer, -1);

    if("No such file or the file is empty \n");

    FILE* file = fopen(file_name, "w");
    //size = sizeof(buffer);
    fwrite(buffer,size,1,file);
    fclose(file);
    free(buffer);
    
}


int rm_inode(Disk* disk, char* path, int isDirectory){
    int i = split_path(path);
    char * name = &path[i+1];
    int dest_inode_num = 1;

    if(i != 0){
        char* dir = malloc(i+1); 
        strncpy(dir,path,i);
        dir[i] = NULL;
        int start_inode = 1;
        dest_inode_num = find_INode(disk,dir,start_inode);
    }

    Inode* inode = read_inode(disk,dest_inode_num);
    if(inode->is_direcory)
    {
        DirectoryEntry* dirs;
        int size = read_inode_data(disk, inode->index, &dirs, -1 );
        size /= sizeof(DirectoryEntry);
        
        int found_i=-1;
        for (int i = 0; i < size; i++)
        {
            if( strcmp( dirs[i].file_name, name) == 0 )
            {
                Inode* inode = read_inode(disk,dirs[i].inode_number);
                if(inode->is_direcory == isDirectory)
                {
                    found_i = i;
                    if(isDirectory && inode->file_size_bytes > 2*sizeof(DirectoryEntry) )       // if the directory is not empty
                    {
                       // printf("size:%d %d",inode->file_size_bytes, 2*sizeof(DirectoryEntry));
                        fprintf(stderr, "The given directory is not empty \n");
                        return;
                    }    
                    break;
                }
                else{
                    if(isDirectory)
                        fprintf(stderr, "The given path is not a directory \n");
                    else
                        fprintf(stderr, "The given path is not a file \n");
                }
            }
        }

        if(found_i != -1){

            

            int inode_index = dirs[found_i].inode_number;
            dirs[found_i].inode_number = dirs[size-1].inode_number;
            strcpy( dirs[found_i].file_name, dirs[size-1].file_name  );
            write_inode_data(disk,inode, dirs, sizeof(DirectoryEntry)*(size-1),0);
            set_bit(disk, 0, inode_index, UNUSED);
        }
        else
        {
            if(isDirectory)
                fprintf(stderr,"There is no such directory to remove \n");
            else
                fprintf(stderr,"There is no such file to remove \n");
        }
    }
    else
        fprintf(stderr,"There is no such path \n");
    
}


int del(Disk* disk, char* path){
    rm_inode(disk, path, 0);
}


int rmdir(Disk* disk, char* path){
    rm_inode(disk, path, 1);
}







int main11111(int argc, char const *argv[])
{
    make_file_system(4,"disk");
    
    Disk * disk = disk_open("disk");
    // Inode inode;
    // strcpy(inode.name,"\\");
    // inode.is_direcory = 1;
    // inode.file_size_bytes = 0;
    // for (int i = 0; i < DIRECT_BLOCK_SIZE; i++)
    //     inode.direct_blocks[i] = 0;
    // inode.single_indirect_block = 0;
    // inode.double_indirect_block = 0;
    // inode.triple_indirect_block = 0;
    // inode.index = 1;

    // write_inode(disk,&inode);
    

    Inode* inode2 = read_inode(disk,1);
    printf("isDir:%d Name:%s\n",inode2->is_direcory, inode2->name);
    


    DirectoryEntry dirs[2] = {  {.file_name=".",.inode_number=1},
                                {.file_name="..",.inode_number=1}};


    
    // char test[] = "asdf1234";
    // char test1[8];
    
   // write_data_block(disk,disk->superblock.data_block_addr+200,test,9);
   // read_data_block(disk,disk->superblock.data_block_addr+200,test1,9);

   
//    int size = sizeof(test);
    write_inode_data(disk,inode2,dirs,sizeof(dirs),0);
   
    
    DirectoryEntry* dirTest;
 //   read_data_block(disk,1,test1,size);

    

    read_inode_data(disk,1,&dirTest,-1);
    DirectoryEntry* di2 = &dirTest[1];
    //DirectoryEntry* di3 = &dirTest[1];
    

    dir(disk,"\\");
    mkdir(disk,"\\usr");
    
    // DirectoryEntry dirs[2];
    // int i = read_data_block(disk,1,&dirs,sizeof(dirs));

    char a[] = "\\";
    dir(disk,a);
    
    char path1[] = "\\usr\\test";
    write(disk, path1, "test.txt");
    read (disk, path1, "test1.txt");

    rmdir(disk,"\\usr");        // not empty dir

    rmdir(disk,"\\ad");         // wrong path

    char path2[] = "\\bin\\ysa";
    mkdir(disk, path2);    // mkdir with wrong path

    char path3[] = "\\usr\\ysa";
    mkdir(disk,path3);

    dir(disk,"\\usr");    

    del(disk,"\\usr");      // not a file

    //rmdir(disk, "");

    printf("asd\n");
    del(disk, "\\usr\\test");
    dir(disk,"\\usr");    

    return 0;
}


int main(int argc, char const *argv[])
{
    if(argc == 4 && !strcmp(argv[2],"dir")  )
    {
        Disk* disk = disk_open(argv[1]);
        dir(disk,argv[3]);
        disk_close(disk);
    }

    if(argc == 4 && !strcmp(argv[2],"mkdir")  )
    {
        Disk* disk = disk_open(argv[1]);
        mkdir(disk,argv[3]);
        disk_close(disk);
    }

    if(argc == 4 && !strcmp(argv[2],"rmdir")  )
    {
        Disk* disk = disk_open(argv[1]);
        rmdir(disk,argv[3]);
        disk_close(disk);
    }

    if(argc == 3 && !strcmp(argv[2],"dumpe2fs")  )
    {
        Disk* disk = disk_open(argv[1]);
        dumpe2fs(disk);
        disk_close(disk);
    }

    if(argc == 5 && !strcmp(argv[2],"write")  )
    {
        Disk* disk = disk_open(argv[1]);
        write(disk,argv[3],argv[4]);
        disk_close(disk);
    }

    if(argc == 5 && !strcmp(argv[2],"read")  )
    {
        Disk* disk = disk_open(argv[1]);
        read(disk,argv[3],argv[4]);
        disk_close(disk);
    }

    if(argc == 4 && !strcmp(argv[2],"del")  )
    {
        Disk* disk = disk_open(argv[1]);
        del(disk,argv[3]);
        disk_close(disk);
    }


    return 0;
}