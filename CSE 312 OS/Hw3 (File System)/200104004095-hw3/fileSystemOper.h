#ifndef FILE_SYSTEM_OPER_H
#define FILE_SYSTEM_OPER_H

#include"file_system.h"

int add_file(Disk* disk, int dest_inode_num, Inode* new_inode);           // adds the given i-node to the given destination directory
void dir(Disk* disk, char * path);                                        // lists all files and directories in the given path
void mkdir(Disk* disk, char* path);                                       // makes a directory in the given path
Inode new_file(Disk* disk, char name[FILE_NAME_MAX], int isDirecory);     // creates a inode in the disk and returns the inode 
int write(Disk* disk, char* path, char* file_name);                       // creates a file and writes the contents of the other file
int read(Disk* disk, char* path, char* file_name);                        // reads the given file and writes it to linux file
int rm_inode(Disk* disk, char* path, int isDirectory);                    // removes the given i-node by specifying the inode is directory or not.
int del(Disk* disk, char* path);                                          // deletes the file at specified path
int rmdir(Disk* disk, char* path);                                        // reamoves the directory at specified directory.
void dumpe2fs(Disk* disk);                                                // Gives information about the file system.
int get_free_block_size(Disk* disk, int type);

#endif