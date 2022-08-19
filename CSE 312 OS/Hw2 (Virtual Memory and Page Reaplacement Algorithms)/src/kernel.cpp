#include <common/types.h>
#include <gdt.h>
#include <memorymanagement.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <multitasking.h>
#include <virtualmemorymanagement.h>

// #define GRAPHICSMODE




using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;
using namespace myos::gui;


VirtualMemoryManager* v;

void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void printfHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    printf(foo);
}




class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
    void OnKeyDown(char c)
    {
        char* foo = " ";
        foo[0] = c;
        printf(foo);
    }
};

class MouseToConsole : public MouseEventHandler
{
    int8_t x, y;
public:
    
    MouseToConsole()
    {
        uint16_t* VideoMemory = (uint16_t*)0xb8000;
        x = 40;
        y = 12;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);        
    }
    
    virtual void OnMouseMove(int xoffset, int yoffset)
    {
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);

        x += xoffset;
        if(x >= 80) x = 79;
        if(x < 0) x = 0;
        y += yoffset;
        if(y >= 25) y = 24;
        if(y < 0) y = 0;

        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);
    }
    
};





void taskA()
{
    while(true)
        printf("A");
}
void taskB()
{
    while(true)
        printf("B");
}






typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


char* itoa(int value, char* result, int base);
void printint(int num);




void swap(int* i1, int* i2){
    int backup = *i1;
    *i1 = *i2;
    *i2 = backup;
}

void bubbleSort(VA base, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		for (j = 0; j < n - i - 1; j++){
			int* a = v->get(base,j);
            int* b = v->get(base,j+1);
            if( *a > *b )
				swap(a, b);
        }
}





// function to find the partition position
int partition(VA base, int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = *(v->get(base,high)) ;
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (*(v->get(base,j)) <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(v->get(base,i), v->get(base,j));
    }
  }

  // swap the pivot element with the greater element at i
  swap( v->get(base,i+1), v->get(base,high) );
  
  // return the partition point
  return (i + 1);
}

void quickSort(VA base, int low, int high) {
  if (low < high) {
    
    int pi = partition(base, low, high);
    
    // recursive call on the left of pivot
    quickSort(base, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(base, pi + 1, high);
  }
}


void insertionSort(VA base, int size) {
  for (int step = 1; step < size; step++) {
    int key = *(v->get(base,step));
    int j = step - 1;

    // For descending order, change key<array[j] to key>array[j].
    if(j>=0)
    while ( j >= 0 && key < *(v->get(base,j)) ) {
      *(v->get(base,j+1)) = *(v->get(base,j));
      --j;
    }
    *(v->get(base,j+1)) = key;
  }
}


static const int A = 15342; // any number in (0, RAND_MAX)
static const int C = 45194; // any number in [0, RAND_MAX)
static const int RAND_MAX = 500;

int rand(int base)
{
    base = ( base * A + C ) % RAND_MAX;
    return base;
}


void print_results(VirtualMemoryManager* vmm){
    

    printf("\nHit:");
    printint(vmm->hit);

    printf("\nMiss:");
    printint(vmm->miss);

    printf("\nPage Load:");
    printint(vmm->page_load);

    printf("\nPage Write:");
    printint(vmm->page_write);

    
}


void printEntries(VirtualMemoryManager* vmm){
    printf("\nMem Entries::\n");
    for(TableEntry* e = vmm->mem_page_table; e != nullptr; e = e->nextEntry )
        vmm->print_entry(e);
    
    printf("\nDisk Entries::\n");
    for(TableEntry* e = vmm->disk_page_table; e != nullptr; e = e->nextEntry )
        vmm->print_entry(e);
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{

    GlobalDescriptorTable gdt;
    
    uint32_t* memupper = (uint32_t*)(((size_t)multiboot_structure) + 8);
    size_t heap_addr = 10*1024*1024;

    size_t mem_size =  256 ;     // 4 Kbyte can be modifiable
    size_t disk_size = 1024 * 1024 * 10 ;
    size_t page_size = 64;       
    
    
    // // int mem_addr = heap_addr + ENTRY_MAX * sizeof(TableEntry);

    MemoryManager memoryManager(heap_addr,mem_size );
    MemoryManager diskManager(heap_addr + mem_size, disk_size );


    VirtualMemoryManager vmm(page_size, &memoryManager, &diskManager);
    
    v = &vmm;


    if(ARRAY_CONSTANT < 1)
        printf("\nThe array is smaller than memory \n");


    int num_of_pages = mem_size / ( page_size + sizeof(MemoryChunk) );
    int array_len = ARRAY_CONSTANT * page_size * num_of_pages / sizeof(int) ;

    
    VA va = vmm.allocate(sizeof(int)*array_len);


    printf("Before Sort:");
    if(INITIAL_ARRAY)       // if random
    {
        int base = REPLACEMENT_ALGORITHM * SORT_ALGORITHM;
        for (int i = 0; i < array_len; i++)
        {
            int* num = vmm.get(va,i);
            *num = rand(base);
            base = *num;
            printint(*num);
            printf(" ");
        }
    }
    else                    // sorted
        for (int i = 0; i < array_len; i++)
        {
            int* num = vmm.get(va,i);
            *num = i;
            printint(*num);
            printf(" ");
        }


    switch (SORT_ALGORITHM)
    {
    case 1:
        bubbleSort(va,array_len);
        break;
    
    case 2:
        quickSort(va,0,array_len-1);
        break;
    
    case 3:
        insertionSort(va,array_len);
        break;
    
    default:
        printf("\n Wrong sorting alogorithm selection !!! \n");
        break;
    }
      



     printf("\n\nAfter Sort:");
    
    for (int i = 0; i < array_len; i++)
    {
        int a = *(vmm.get(va,i));
        printint(a);
        printf(" ");
    }

    print_results(&vmm);

    printf("\nArray Length:");
    printint(array_len);


    
     //printEntries(&vmm);



    while(1);

















    // printf("heap_addr: 0x");
    // printfHex((heap_addr >> 24) & 0xFF);
    // printfHex((heap_addr >> 16) & 0xFF);
    // printfHex((heap_addr >> 8 ) & 0xFF);
    // printfHex((heap_addr      ) & 0xFF);
    
    // void* allocated = memoryManager.malloc(1024);
    // printf("\nallocated: 0x");
    // printfHex(((size_t)allocated >> 24) & 0xFF);
    // printfHex(((size_t)allocated >> 16) & 0xFF);
    // printfHex(((size_t)allocated >> 8 ) & 0xFF);
    // printfHex(((size_t)allocated      ) & 0xFF);
    // printf("\n");
    
    TaskManager taskManager;
    /*
    Task task1(&gdt, taskA);
    Task task2(&gdt, taskB);
    taskManager.AddTask(&task1);
    taskManager.AddTask(&task2);
    */
    
    InterruptManager interrupts(0x20, &gdt, &taskManager);
    
    printf("Initializing Hardware, Stage 1\n");
    
    #ifdef GRAPHICSMODE
        Desktop desktop(320,200, 0x00,0x00,0xA8);
    #endif
    
    DriverManager drvManager;
    
        #ifdef GRAPHICSMODE
            KeyboardDriver keyboard(&interrupts, &desktop);
        #else
            PrintfKeyboardEventHandler kbhandler;
            KeyboardDriver keyboard(&interrupts, &kbhandler);
        #endif
        drvManager.AddDriver(&keyboard);
        
    
        #ifdef GRAPHICSMODE
            MouseDriver mouse(&interrupts, &desktop);
        #else
            MouseToConsole mousehandler;
            MouseDriver mouse(&interrupts, &mousehandler);
        #endif
        drvManager.AddDriver(&mouse);
        
        PeripheralComponentInterconnectController PCIController;
        PCIController.SelectDrivers(&drvManager, &interrupts);

        VideoGraphicsArray vga;
        
    printf("Initializing Hardware, Stage 2\n");
        drvManager.ActivateAll();
        
    printf("Initializing Hardware, Stage 3\n");

    #ifdef GRAPHICSMODE
        vga.SetMode(320,200,8);
        Window win1(&desktop, 10,10,20,20, 0xA8,0x00,0x00);
        desktop.AddChild(&win1);
        Window win2(&desktop, 40,15,30,30, 0x00,0xA8,0x00);
        desktop.AddChild(&win2);
    #endif


    interrupts.Activate();
    
    while(1)
    {
        #ifdef GRAPHICSMODE
            desktop.Draw(&vga);
        #endif
    }
}
