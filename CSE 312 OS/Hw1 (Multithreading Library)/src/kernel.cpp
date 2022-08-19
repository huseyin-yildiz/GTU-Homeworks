
#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <multitasking.h>
#include <multithreading.h>




// !!! The Thread3 (in kernelmain) can be uncomment  to test  functions
//  of the thread library. You should comment thread1 and thread2 to see outputs


// #define GRAPHICSMODE


using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;
using namespace myos::gui;

#define N 100
int count = 0;
bool p_sleep = false;
bool c_sleep = false;


char lastChar = 'a';
int queue[N];
int Rear = - 1;
int Front = - 1;
char item;
int semaphore = 0;


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





char ch[2] = "1";

void taskB()
{
    
    for (int i = 0; i < 3; i++)
    { 
        ch[0] = 'B';
        printf("Thred B: ch=");
        printf(ch);
        printf(". Doing some stuff...\n");
    }
    printf("Thread B: Done.\n");
    
}


void taskA()
{
    Thread thr1(taskB);
    
    int i = 0;
    for(int i=0; i<23; i++)
    {
        ch[0] = 'A';
        printf("Thread A: ch=");
        printf(ch);
        printf(". Doing some stuff...\n");

        for (int i = 0; i < 1000; i++);     // wait
        
        
        if(i == 12)
        {
            printf("Thread A: Creating the Thread B\n");
            Threading::create(&thr1);
            //thr1.terminate();
            
        }

        else if(i == 18)
        {
                printf("Thread A: Waiting for the thread B to join\n");
                thr1.join(); //thr1.terminate();
                printf("Thread A: Thread B joined here\n");
        }
    }
    printf("Thread A: Done.\n");
    
    while (true);
    
            
}


char produce(){             // produces the number between char value a-z
    semaphore++;
    if(lastChar == 'z'+1)
        lastChar = 'a';
    return lastChar++;
}

int cc = 0;
void consume(char a){       // consumes (prints) the given char
    semaphore--;
    printfHex(a);
    printf(" ");
    if(a == 'z')
        printf("\n");
    cc++;
    
}




char items[N];
int front = -1, rear = -1;          // variables for queue

int isFull() {                  
  if ((front == rear + 1) || (front == 0 && rear == N - 1)) return 1;
  return 0;
}

// Check if the queue is empty
int isEmpty() {
  if (front == -1) return 1;
  return 0;
}


// Adding an element
void insert_item() {
  if (isFull())
    printf("\n Queue is full!! \n");
  else {
    if (front == -1) front = 0;
    rear = (rear + 1) % N;
    items[rear] = item;

  }
}

// Removing an element
char remove_item() {
  int element;
  if (isEmpty()) {
    printf("\n Queue is empty !! \n");
    return '*';
  } else {
    element = items[front];
    items[front] = '-';
    if (front == rear) {
      front = -1;
      rear = -1;
    } 
    
    else {
      front = (front + 1) % N;
    }
    return (element);
  }
}





void pSleep(){              // to make sleep the producer
    p_sleep = true;
    while(p_sleep)
        ;
}

void cSleep(){              // to make sleep the consumer
    c_sleep = true;
    while(c_sleep)
        ;
}


int flag[2];
int turn;

void lock_init()            // initializes the lock
{
    flag[0] = flag[1] = 0;
    turn = 0;
}
 

void lock(int self)         // locks the critical region
{
    flag[self] = 1;
    turn = 1-self;
    while (flag[1-self]==1 && turn==1-self) ;
}
 

void unlock(int self)       // unlock th critical region
{
    flag[self] = 0;
}



void procuder(){            // produces numbers to the queue
    
    while(true){

        item = produce();
        if(count == N) 
            pSleep();
        
        lock(0);
        insert_item();          // Here may be race condition so i prevented it
        unlock(0);

        if(count++ == 0)
            c_sleep = false;        // wake consumer
      
    }
  

}

void consumer(){                // removes from the queue and consumes it. 
    while(true){

        if(count == 0) 
            cSleep();    

        lock(1);
        item = remove_item();           // Here may be race condition
        unlock(1);                      // if we remove this locking system there can be missremoved item because of count changed.

        if (count-- == N)
            p_sleep = false;        // wake producer
        consume(item);
  
    }
}




typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    printf("Hello World! --- http://www.AlgorithMan.de\n");

    GlobalDescriptorTable gdt;
    TaskManager taskManager;
    Threading threading(&gdt,&taskManager);

    InterruptManager interrupts(0x20, &gdt, &taskManager);
    
    lock_init();

    Thread thread1(procuder);
    threading.create(&thread1);
    
    Thread thread2(consumer);
    threading.create(&thread2);
    
//    Thread thread3(taskA);                  // !!! You may uncomment this 2 lines For testing threading library
//    threading.create(&thread3);             // You should comment Thread1 and thread2 to see outputs.
    


    
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
