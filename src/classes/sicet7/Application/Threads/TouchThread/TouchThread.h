#pragma once
#include <mbed.h>
#include <rtos.h>
namespace sicet7{
    namespace Application{
        namespace Threads{
            class TouchThread{

                private: static TouchThread* instance;
                private: static rtos::Mutex* singletonLock;
                private: static TouchThread* GetInstance();
                
                private: volatile bool run = false;
                private: rtos::Mutex* runLock;
                private: Thread thread;

                private: TouchThread();
                public: ~TouchThread();

                public: static osStatus Start();
                public: static void Stop();

                private: osStatus InternalStart();
                private: void InternalStop();
                private: void Process();

            };
        }
    }
}