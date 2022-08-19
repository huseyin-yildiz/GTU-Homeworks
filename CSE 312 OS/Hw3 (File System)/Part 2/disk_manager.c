#include "disk_manager.h"

Disk *  disk_open(char *name){
    Disk* disk = (Disk*) malloc(sizeof(Disk));
    disk->fptr = fopen(name,"rb+");

    if(disk->fptr == NULL)
        printf("Disk open Error");
    
    
    long int size = findSize(disk->fptr);
    char zero[] = "1234";
    if(size == 0)
        for (int i = 0; i < DISK_SIZE; i++)
            fwrite(&zero,sizeof(char),1,disk->fptr);
        
        
    else if(size != DISK_SIZE )
    {
        printf("Error: Disk size is wrong ");
        exit(EXIT_FAILURE);
    }
    return disk;
}



void disk_close(Disk *disk){
    fclose(disk->fptr);
    free (disk);
}


int disk_read(Disk *disk, int block_index, char *data){
    if(disk -> block_size == 0)
        printf("Error: Block Size not defined");

    int offset =  block_index*(disk->block_size );

    if ( fseek(disk->fptr, offset, SEEK_SET) )
        printf("Disk read error");    
    
    fread(data, disk->block_size, 1, disk->fptr);
    
}

int disk_write(Disk *disk, int block_index, char *data){
    if(disk -> block_size == 0)
        printf("Error: Block Size not defined");

    int offset =  block_index*(disk->block_size );

    if ( fseek(disk->fptr, offset, SEEK_SET) )
        printf("Disk read error");

    fwrite(data, disk->block_size, 1, disk->fptr);
}

uint8_t disk_read_byte(Disk *disk, int address){
    int cursor = ftell(disk->fptr);
    fseek(disk->fptr, address, SEEK_SET);
    uint8_t val;
    fread(&val,sizeof(uint8_t),1,disk->fptr);
    fseek(disk->fptr, cursor, SEEK_SET);
    return val;
}

void disk_write_byte(Disk *disk, int address, uint8_t byte){
    int cursor = ftell(disk->fptr);
    fseek(disk->fptr, address, SEEK_SET);
    uint8_t val;
    fwrite(&byte,sizeof(uint8_t),1,disk->fptr);
    fseek(disk->fptr, cursor, SEEK_SET);
    
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



Disk * disk_create(char* name, int block_size)
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
    return disk;
}


int main1(){         /* Disk manager test */

    Disk * disk = disk_open("disk1");
    // disk->block_size = 1 * KB;
    // char* data = (char*) malloc(1*KB);

    // disk_write(disk,2,data);
    // disk_close(disk);

    return 0;
}


