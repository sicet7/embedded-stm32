/**
 * @file TemperatureAndHumidityThread.h
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Defines the Temperature And Humidity Thread class.
 * @version 0.1
 * @date 2019-01-25
 * 
 */
#pragma once
#include <mbed.h>
#include <rtos.h>
namespace sicet7{
    namespace Application{
        namespace Threads{
            class TemperatureAndHumidityThread{
                private: static TemperatureAndHumidityThread* instance;
                private: static rtos::Mutex* singletonLock;
                private: static TemperatureAndHumidityThread* GetInstance();
                
                private: volatile bool run = false;
                private: volatile bool active = false;
                private: bool stopped = false;
                private: rtos::Mutex* runLock;
                private: Thread thread;

                private: TemperatureAndHumidityThread();
                public: ~TemperatureAndHumidityThread();

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