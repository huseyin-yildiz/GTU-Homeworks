
#include <multitasking.h>
#include "multithreading.h"
//#include <string.h>

using namespace myos;
using namespace myos::common;

 
void printf2(char* str)
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


Task::Task(GlobalDescriptorTable *gdt, void entrypoint())
{
    isThread = false;
    is_finished = false;        

    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
    
    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;
    
    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */
    
    // cpustate -> error = 0;    
   
    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)entrypoint;
    cpustate -> cs = gdt->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;
    
    code_limit = gdt->codeSegmentSelector.Limit();
}

Task::~Task()
{
}

        
TaskManager::TaskManager()
{
    numTasks = 0;
    currentTask = -1;
}

TaskManager::~TaskManager()
{
}

bool TaskManager::AddTask(Task* task)
{
    if(numTasks >= 256)
        return false;
    tasks[numTasks++] = task;
    return true;

}


// New Schedule algorithm to handle threading operations (terminate,yield etc.)
CPUState* TaskManager::Schedule(CPUState* cpustate)
{
    if(numTasks <= 0)
        return cpustate;        
    
    bool found = false;
    int count = 0;
    int next;
    while(++count <= numTasks){
        next = (currentTask+count) % numTasks ;



        if( is_thread(next) )
        {
            Thread* thread = (Thread*)tasks[next];
            if(thread->is_finished)
            {
                tasks[next] = nullptr;

            }
            else if(thread->is_yield)
                    ;
            else
            {
                found = true;
                break;
            }
        }
        else{
            found = true;
            break;
        }
    }

    if(found){
        
        tasks[currentTask]->cpustate = cpustate;        // backup the old task
        currentTask = next;
        return tasks[currentTask]->cpustate;
    }
    else
       return cpustate;

    
}

bool TaskManager::is_thread(int task_id){
    return tasks[task_id]->isThread;
}

bool TaskManager::terminate(int task_id){
    return false;
}
   
bool Task::isFinished(){
    return is_finished;
}

bool TaskManager::terminate_current(){              // terminates the current task
    tasks[currentTask]->is_finished = true;
    return true;
}