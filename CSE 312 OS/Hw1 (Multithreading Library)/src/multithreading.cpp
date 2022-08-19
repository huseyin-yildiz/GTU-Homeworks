#include "multithreading.h"

using namespace myos;
using namespace myos::common;

GlobalDescriptorTable* Threading::gdt = nullptr;
TaskManager* Threading::taskManager = nullptr;


Thread::Thread(void entrypoint()) : Task(Threading::gdt,entrypoint){
    is_yield = false;
    isThread = true;
}

Threading::Threading(GlobalDescriptorTable *mygdt, TaskManager *mytaskManager){
    gdt = mygdt;
    taskManager = mytaskManager;
}

Threading::Threading(){
    // intentionally left blank 
}

void Threading::create(Thread* thread ){
    int id = taskManager->AddTask(thread);
    thread->task_id = id;    
}

bool Thread::terminate(){
    is_finished = true;
}


void Thread::join(){        
    while(!is_finished);
}

void Thread::yield(){
    is_yield = true;
}