#pragma once
#include <mbed.h>
#include <rtos.h>
namespace sicet7{
    namespace Application{
        namespace Threads{
            class TemperatureThread{

                private: static TemperatureThread* instance;
                private: static rtos::Mutex* singletonLock;
                private: static TemperatureThread* GetInstance();
                
                private: volatile bool run = false;
                private: volatile bool active = false;
                private: bool stopped = false;
                private: rtos::Mutex* runLock;
                private: Thread thread;

                private: TemperatureThread();
                public: ~TemperatureThread();

                public: static osStatus Start();
                public: static void Stop();
                public: static void Pause();

                private: osStatus InternalStart();
                private: void InternalStop();
                private: void InternalPause();
                private: void Process();

            };
        }
    }
}