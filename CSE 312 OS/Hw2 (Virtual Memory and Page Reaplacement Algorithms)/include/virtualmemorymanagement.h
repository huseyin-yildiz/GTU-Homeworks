#ifndef __MYOS__VIRTUAL_MEMORY_MANAGEMENT_H
#define __MYOS__VIRTUAL_MEMORY_MANAGEMENT_H

#define ARRAY_CONSTANT 2.1
#define REPLACEMENT_ALGORITHM 2             // 1 --> FIFO   2 --> SECOND CHANCE     3--> LRU
#define SORT_ALGORITHM 1                    // 1 --> Bubble  2 --> Quick  3 --> Insertion
#define INITIAL_ARRAY 1                     // 0 --> Sorted     1 --> Random


#define ENTRY_MAX 100000
#define DISK 0
#define MEMORY 1



#define REFERENCED_CLEAN_PERIOD    5

#include <memorymanagement.h>


namespace myos
{
    enum Replacement_Alogithm{
        FIFO = 1,
        SECOND_CHANCE = 2,
        LRU = 3
    };


    //void printint(int num);

    struct TableEntry{

        int page_index;
        void* physical_address;
        bool present;                       // if the entry used or not used.
        bool referenced;                    // is referenced by read or write. For Fifo and Second chance
        int last_referenced_counter;        // it holds the last usage time by holding a counter. For LRU

        TableEntry* nextEntry;
        TableEntry* prevEntry;
    };

    typedef struct VA               // virtual address struct to hold virtual adressess.
    {                               // this prevents using the virtual adress as physical adress.
        int page_num;  
        int address;
    }VA;
     


    // Virtual memory manager class that manupulates virtual memory (memory and disk simulation)
    class VirtualMemoryManager
    {
    private:
        
        int va_count;
        int reference_count;

        struct TableEntry* last_mem_page;                   // Last mem page
        struct TableEntry* last_disk_page;                   // Last disk page

        void* page_allocate(short disk_or_mem );            //  DISK | MEMORY 
        TableEntry* entry_allocate( );                  //  DISK | MEMORY 
        


    public:
        int hit;
        int miss;
        int page_load;
        int page_write;

        int page_size;                                  // page size for every page in bytes.
        struct TableEntry* mem_page_table;              // Memory Page table 
        struct TableEntry* disk_page_table;             // Disk Page table 
        
        
        static MemoryManager* mem_manager;              // Holds the memory_manager
        static MemoryManager* disk_manager;             // Simulates the disk_manager
        static VirtualMemoryManager* activeVMM;

        VirtualMemoryManager(int page_size1, MemoryManager* mem_manager1, MemoryManager* disk_manager1);            // Constructor -- page_size in bytes 
        ~VirtualMemoryManager();                        // Destructor 


        VA allocate(common::size_t size);               // allocation of pages in given size
        void free(VA virtual_addr);                     // deallocation of pages
        void* operator[](VA virtual_address);           // converts the virtual adress to physical address.
        bool is_on_disk(VA va);                         // returns if corresponding physical address of given virtual address is 
        int* get(VA baseVa, int index);                 // returns the int index based given virtual address.
    

        
        short page_replace(TableEntry* entry1,TableEntry* entry2);
        // page replacement functions with different algoritms
        short page_replace_fifo(TableEntry* disk_entry);
        short page_replace_second_chance(TableEntry* disk_entry);
        short page_replace_LRU(TableEntry* disk_entry);


        void print_entry(TableEntry* entry);


        TableEntry* find_entry(short onDisk, int page_index);           // find the page entry by virtual address 
        TableEntry* pop_entry(bool on_disk);                            // removes the last entry of linked list and returns
        void push_entry(int on_disk, TableEntry* new_entry);            // adds the given entry to head of linked_list
        TableEntry* remove_entry(bool on_disk, int index);              // removes the entry with given index


        void clean_all_reference();
        void increase_last_references();
        int find_least_recently_used_mem_entry();
        
    };
    
    
    
    


}





#endif