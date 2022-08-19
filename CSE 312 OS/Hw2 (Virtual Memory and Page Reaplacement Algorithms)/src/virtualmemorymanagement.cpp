#include <virtualmemorymanagement.h>

using namespace myos;
using namespace myos::common;

        void printf(char* str);
        void printfHex(uint8_t);



        MemoryManager* VirtualMemoryManager::mem_manager = nullptr;
        MemoryManager* VirtualMemoryManager::disk_manager = nullptr;

        VirtualMemoryManager* VirtualMemoryManager::activeVMM = 0;




    char* itoa(int value, char* result, int base) {
        // check that the base if valid
        if (base < 2 || base > 36) { *result = '\0'; return result; }

        char* ptr = result, *ptr1 = result, tmp_char;
        int tmp_value;

        do {
            tmp_value = value;
            value /= base;
            *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
        } while ( value );

        // Apply negative sign
        if (tmp_value < 0) *ptr++ = '-';
        *ptr-- = '\0';
        while(ptr1 < ptr) {
            tmp_char = *ptr;
            *ptr--= *ptr1;
            *ptr1++ = tmp_char;
        }
        return result;
    }


    void printint(int num){
        char s[150];
        itoa(num,s,10);
        printf(s);
    }



    void * memcpy(void* dst, const void* src, unsigned int cnt)
    {
        char *pszDest = (char *)dst;
        const char *pszSource =( const char*)src;
        if((pszDest!= 0) && (pszSource!= 0))
        {
            while(cnt) //till cnt
            {
                //Copy byte by byte
                *(pszDest++)= *(pszSource++);
                --cnt;
            }
        }
        return dst;
    }





    void VirtualMemoryManager::print_entry (TableEntry* entry){
        printf("\nindex :");
        printint(entry->page_index);

        printf(" physical addr:");
        printint(((int)entry->physical_address));

        printf(" present:");
        if(entry->present)
            printf("yes ");
        else
            printf("no ");

        printf("r_count:");
        printint(entry->last_referenced_counter);

        printf(" r:");
        printint(entry->referenced);


    }



        VirtualMemoryManager::VirtualMemoryManager(int page_size1, MemoryManager* mem_manager1, MemoryManager* disk_manager1)            // Constructor -- page_size in bytes
        {
            va_count = 0;
            this->page_size = page_size1;
            this->mem_manager = mem_manager1;
            this->disk_manager = disk_manager1;
            activeVMM = this;

            // printf("Page Size: ");
            // printint(page_size);
            // // printf(" KB \n");

            mem_page_table = nullptr;
            disk_page_table = nullptr;
            last_disk_page = nullptr;
            last_mem_page = nullptr;


            hit = 0;
            miss = 0;
            page_load = 0;
            page_write = 0;

        }


        VirtualMemoryManager::~VirtualMemoryManager()                        // Destructor
        {
            if(activeVMM == this)
                activeVMM = 0;
        }



        VA VirtualMemoryManager::allocate(common::size_t size)               // allocation of pages in given size
        {
            void* addr;
            TableEntry* entry;
            VA va;

            int page_num =  size / page_size + (size % page_size != 0);

            
             // entry allocation
            for (int i = 0; i < page_num; i++)
            {
                entry = entry_allocate();

                addr = page_allocate(MEMORY);

                if(addr == nullptr)
                {
                    addr = page_allocate(DISK);
                    if(addr == nullptr)
                    {
                        printf("\nThere is no any page space on memory or on disk ");
                        return VA{-1,-1};
                    }
                    else        //  if page is allocated at disk
                    {
                      //  printf(" at disk ");
                        entry->present = false;
                        entry->page_index = ++va_count;
                        entry->physical_address = addr;
                        entry->present = true;
                        if(i==0)
                            va.page_num = entry->page_index;

                        push_entry(1,entry);
                        page_write++;
                    }
                }

                else                               // if page is allocated at memory
                {
                    entry->page_index = ++va_count;
                    entry->physical_address = addr;
                    entry->present = true;
                    if(i==0)
                        va.page_num = entry->page_index;

                  //  printf(" at memo entry:");
                    entry->present = true;
                    push_entry(0,entry);
                }

            }
            va.address = 0;
            // printf("vaaa:");
            // printint(va.page_num);
            return va;



        }


        void VirtualMemoryManager::free(VA virtual_addr)                     // deallocation of pages
        {
            // TableEntry* entry = find_entry(virtual_addr.page_num);

            // // if there is no such virtual address
            // if(entry == nullptr)
            //     return;


            // // entry is at head
            // if(entry->page_index == page_table->page_index)
            //     page_table = 0;


            // // entry is at last
            // if(last_page->page_index == entry->page_index)
            // {
            //     last_page = last_page->prevEntry;
            //     last_page->nextEntry = nullptr;
            // }

            // // entr is middle
            // else
            //     entry->prevEntry->nextEntry = entry->nextEntry;


            // // making page free
            // if(entry->on_disk)
            //     disk_manager->free(entry->physical_address);
            // else
            //     mem_manager->free(entry->physical_address);


            // // making entry free
            // mem_manager->free(entry);

        }

        void VirtualMemoryManager::clean_all_reference()        // cleans all referenced bits of entries
        {
            TableEntry* entry;

            for ( entry = mem_page_table; entry != nullptr; entry = entry->nextEntry)
                entry->referenced = false;

            for ( entry = disk_page_table; entry != nullptr; entry = entry->nextEntry)
                entry->referenced = false;

            reference_count = 0;
        }


        void* VirtualMemoryManager::operator[](VA virtual_address)           // converts the virtual adress to physical address.
        {
             if( reference_count == REFERENCED_CLEAN_PERIOD )
                 clean_all_reference();

            TableEntry* entry = find_entry(0, virtual_address.page_num);
            if(entry)
            {
                entry->referenced = true;
                hit++;
                reference_count++;
                increase_last_references();
                entry->last_referenced_counter = 0;
                return entry->physical_address + virtual_address.address;
            }
            // page fault
            miss++;


          //  printint(virtual_address.page_num);
            entry = remove_entry(1, virtual_address.page_num);

            //remove fo not forget
           // printint(virtual_address.page_num);

            if(entry)
            {
              //  printf("\nPage Fault for page number:");                  // if its not in memory

                // takes the disk entry and replace with a memory entry by using these algorithmsy
                switch (REPLACEMENT_ALGORITHM)
                {
                case FIFO:
                     page_replace_fifo(entry);
                    break;

                case SECOND_CHANCE:
                    page_replace_second_chance(entry);
                    break;

                case LRU:
                    page_replace_LRU(entry);
                    break;

                default:
                    printf("\nWrong Replacement algorithm selection !!! (Only 1,2,3)\n");
                    break;
                }


              //  Setting all required entry fields and counters
                increase_last_references();
                entry->last_referenced_counter = 0;
                page_load++;
                page_write++;
                entry->referenced = true;
                reference_count++;
                
                return entry->physical_address + virtual_address.address;
            }
            else
               printf(" \nNo such va address ");
            return nullptr;
        }


        bool VirtualMemoryManager::is_on_disk(VA va)                         // returns if corresponding physical address of given virtual address is
        {
            TableEntry* entry = find_entry(1,va.page_num);
            if(entry == nullptr)
            {
                printf("There is no such virtual address");
                return false;
            }
            return !entry->present;
        }


        short VirtualMemoryManager::page_replace(TableEntry* entry1,TableEntry* entry2){

            void* ptr1 = entry1->physical_address;
            void* ptr2 = entry2->physical_address;

            if(entry1 < 0 || entry2 < 0 )
                printf("The given pages not found to replace \n");
            else if(ptr1 == nullptr || ptr2 == nullptr)
                    printf("The given entries does not have physical address \n");
            else
            {
                uint8_t backup[page_size];
                memcpy(backup,ptr1,page_size);
                memcpy(ptr1,ptr2,page_size);
                memcpy(ptr2,backup,page_size);

                bool prsnt = entry2->present;
                entry2->present = entry1->present;
                entry1->present = prsnt;

                entry1->physical_address = ptr2;
                entry2->physical_address = ptr1;
            }


        }


        // page replacement functions with different algoritms

        short VirtualMemoryManager::page_replace_fifo(TableEntry* disk_entry){
            TableEntry* oldMemEntry = pop_entry(0);
            page_replace(oldMemEntry, disk_entry);
            push_entry(1, oldMemEntry);
            push_entry(0, disk_entry);
        }


        short VirtualMemoryManager::page_replace_second_chance(TableEntry* disk_entry){
            TableEntry* oldMemEntry;
            // finding the not referenced entry
            while( (oldMemEntry = pop_entry(0))->referenced )
                push_entry(0,oldMemEntry);

            // if the entry is not referenced then we replace it
            page_replace(oldMemEntry, disk_entry);
            push_entry(1, oldMemEntry);
            push_entry(0, disk_entry);
        }


        int VirtualMemoryManager::find_least_recently_used_mem_entry()
        {
            int max = mem_page_table->last_referenced_counter;
            TableEntry* lru = mem_page_table;

            TableEntry* entry;
            for ( entry = mem_page_table; entry != nullptr; entry = entry->nextEntry)
                if(max <= entry->last_referenced_counter)
                {
                    max = entry->last_referenced_counter;
                    lru = entry;
                }

            if(lru == nullptr)
                printf("\nThere is no any memory entry !!! \n");

            return lru->page_index;
        }


        short VirtualMemoryManager::page_replace_LRU(TableEntry* disk_entry){

            int lru_index = find_least_recently_used_mem_entry();
            TableEntry* oldMemEntry = remove_entry(0,lru_index);

            page_replace(oldMemEntry,disk_entry);
            push_entry(1, oldMemEntry);
            push_entry(0, disk_entry);

        }


        void* VirtualMemoryManager::page_allocate(short disk_or_mem )            //  DISK | MEMORY
        {

            if(disk_or_mem == DISK)
                return disk_manager->malloc(page_size);

            return mem_manager->malloc(page_size);
        }


        TableEntry* VirtualMemoryManager::entry_allocate( )
        {

            return (TableEntry*) disk_manager->malloc(sizeof(TableEntry));
        }




        TableEntry* VirtualMemoryManager::find_entry(short onDisk, int page_index)    // find the page entry by virtual address
        {
            TableEntry* last = last_disk_page;
            TableEntry* page_table = disk_page_table;

            if(!onDisk)
            {
                last = last_mem_page;
                page_table = mem_page_table;
            }

            TableEntry* entry;
            for ( entry = page_table; entry != nullptr; entry = entry->nextEntry)
                if(entry->page_index == page_index)          // if th entry is not in the page table
                    return entry;
            return nullptr;
        }




        TableEntry* VirtualMemoryManager::pop_entry(bool on_disk){

            TableEntry* firstEntry;

            if(on_disk)
            {    if(disk_page_table == nullptr)
                    printf("\nThere is no disk entry to pop");
                else{
                    firstEntry = disk_page_table;
                    disk_page_table = disk_page_table->nextEntry;
                    firstEntry->nextEntry = nullptr;
                    disk_page_table->prevEntry = nullptr;
                }
            }
            else{
                if(mem_page_table == nullptr)
                    printf("\nThere is no mem entry to pop");
                else{
                    firstEntry = mem_page_table;
                    mem_page_table = mem_page_table->nextEntry;
                    firstEntry->nextEntry = nullptr;
                    mem_page_table->prevEntry = nullptr;
                }
            }
            return firstEntry;

        }

        void VirtualMemoryManager::push_entry(int on_disk, TableEntry* new_entry){

            new_entry->nextEntry = nullptr;

            if(on_disk){
                if(last_disk_page == nullptr)
                {
                    disk_page_table = new_entry;
                    last_disk_page = new_entry;
                    new_entry->prevEntry = nullptr;
                    return;
                }

                last_disk_page->nextEntry = new_entry;
                new_entry->prevEntry = last_disk_page;
                last_disk_page = new_entry;
            }
            else
            {
                if(last_mem_page == nullptr)
                {
                    mem_page_table = new_entry;
                    last_mem_page = new_entry;
                    new_entry->prevEntry = nullptr;
                    return;
                }



             //   printf("\nadded..\n");
             //   printint(mem_page_table->page_index);
             //   printf("----");
              //  printint(new_entry->page_index);

                last_mem_page->nextEntry = new_entry;
                new_entry->prevEntry = last_mem_page;
                last_mem_page = new_entry;
            }


        }


        TableEntry* VirtualMemoryManager::remove_entry(bool on_disk, int index){
            TableEntry* entry = find_entry(on_disk,index);

            if(entry == nullptr)
                return nullptr;

            if(on_disk)
            {
                if(entry == disk_page_table)        // if the entry is at first
                    return pop_entry(1);

                if(entry == last_disk_page)         // if the entry is at last
                {
                    last_disk_page = last_disk_page->prevEntry;
                    entry->prevEntry = nullptr;
                    last_disk_page->nextEntry = nullptr;
                }
                else{                               // if the entry is at middle
                    entry->prevEntry->nextEntry = entry->nextEntry;
                    entry->nextEntry->prevEntry = entry->prevEntry;
                    entry->nextEntry = nullptr;
                    entry->prevEntry = nullptr;
                }
            }
            else{
                if(entry == mem_page_table)        // if the entry is at first
                    return pop_entry(0);

                if(entry == last_mem_page)         // if the entry is at last
                {
                    last_mem_page = last_mem_page->prevEntry;
                    entry->prevEntry = nullptr;
                    last_mem_page->nextEntry = nullptr;
                }
                else{                               // if the entry is at middle
                    entry->prevEntry->nextEntry = entry->nextEntry;
                    entry->nextEntry->prevEntry = entry->prevEntry;
                    entry->nextEntry = nullptr;
                    entry->prevEntry = nullptr;
                }
            }
            return entry;
        }


        int* VirtualMemoryManager::get(VA baseVa, int index){
            baseVa.page_num += index*sizeof(int) / page_size;
            baseVa.address = index*sizeof(int) % page_size;

            int* addr = (int*) operator[](baseVa) ;
            if(!addr){
                printf("index:");
                printint(index);
            }
            return addr;
        }


        void VirtualMemoryManager::increase_last_references(){

            TableEntry* entry;

            for ( entry = mem_page_table; entry != nullptr; entry = entry->nextEntry )
                    entry->last_referenced_counter++;

            // for ( entry = disk_page_table; entry != nullptr; entry = entry->nextEntry )
            //         entry->last_referenced_counter++;
        }




        int main(int argc, char const *argv[])
        {
            size_t heap_addr = 10*1024*1024;


            size_t mem_size = 10 * 1024;     // 10 KB
            int page_size = 512 * 1024;


            TableEntry* page_table = (TableEntry*) heap_addr;
            int mem_addr = heap_addr + ENTRY_MAX * sizeof(TableEntry);

            MemoryManager memoryManager(mem_addr,mem_size );
            MemoryManager diskManager(mem_addr + mem_size, mem_size );



            VirtualMemoryManager vmm(page_size, &memoryManager, &diskManager);

            return 0;
        }