#ifndef __MYOS_MULTITHREADING__
#define __MYOS_MULTITHREADING__

#include "multitasking.h"


namespace myos{



    class Thread: public Task{
        private:
            int task_id;
            bool is_yield;
        public:
            Thread(void entrypoint());
            void join();        
            void yield();       
            bool terminate();
        friend class Threading;
        friend class TaskManager;
        friend class Task;
    };


    class Threading{
        private:
            static GlobalDescriptorTable* gdt;
            static TaskManager* taskManager;
            
        public:
            
            Threading(GlobalDescriptorTable *gdt, TaskManager *taskManager);
            Threading();
            static void create(Thread* thread );
        friend class Thread;
    };



}


#endif
