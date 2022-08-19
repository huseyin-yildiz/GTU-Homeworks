#include "file_system.h"


int main(int argc, char const *argv[])
{
    int block_size = 4;

    if(argc != 3)
        fprintf(stderr,"Wrong parameters !!! Example: makeFileSystem 4 mySystem.dat \n");
    else{
     //   printf("%s %s %s %s",argv[0],argv[1],argv[2],argv[3]);
        sscanf("argv[1]","%d",block_size);
        make_file_system(block_size,argv[2]);
        
        Disk * disk = disk_open(argv[2]);
        Inode* inode2 = read_inode(disk,1);
        printf("isDir:%d Name:%s\n",inode2->is_direcory, inode2->name);
        DirectoryEntry dirs[2] = {  {.file_name=".",.inode_number=1},
                                    {.file_name="..",.inode_number=1}};
        write_inode_data(disk,inode2,dirs,sizeof(dirs),0);

        disk_close(disk);
  }  

    return 0;
}
