/**
 * @file TemperatureAndHumidityThread.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Implementation of the Thread TemperatureAndHumidityThread.
 * @version 0.1
 * @date 2019-01-25
 * 
 */
#include <classes/sicet7/Application/Threads/TemperatureAndHumidityThread/TemperatureAndHumidityThread.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Sensors/TemperatureAndHumidity/TemperatureAndHumidity.h>
namespace sicet7{
    namespace Application{
        namespace Threads{

            TemperatureAndHumidityThread* TemperatureAndHumidityThread::instance = 0;
            rtos::Mutex* TemperatureAndHumidityThread::singletonLock = new rtos::Mutex("TemperatureAndHumidityThreadSingletonLock");

            /**
             * @brief Returns a pointer to the current instance of the class.
             * 
             * @return TemperatureAndHumidityThread* 
             */
            TemperatureAndHumidityThread* TemperatureAndHumidityThread::GetInstance(){
                TemperatureAndHumidityThread::singletonLock->lock();
                if(TemperatureAndHumidityThread::instance == 0){
                    TemperatureAndHumidityThread::instance = new TemperatureAndHumidityThread();
                }
                TemperatureAndHumidityThread::singletonLock->unlock();
                return TemperatureAndHumidityThread::instance;
            }

            /**
             * @brief Starts or Un-Pauses the thread.
             * 
             * @return osStatus 
             */
            osStatus TemperatureAndHumidityThread::Start(){
                return TemperatureAndHumidityThread::GetInstance()->InternalStart();
            }

            /**
             * @brief Stop's the thread.
             * @warning the thread cannot be restarted after calling this.
             * 
             */
            void TemperatureAndHumidityThread::Stop(){
                TemperatureAndHumidityThread::GetInstance()->InternalStop();
            }

            /**
             * @brief Pauses the thread.
             * 
             */
            void TemperatureAndHumidityThread::Pause(){
                TemperatureAndHumidityThread::GetInstance()->InternalPause();
            }

            /**
             * @brief Construct a new Temperature And Humidity Thread object
             * 
             */
            TemperatureAndHumidityThread::TemperatureAndHumidityThread(){
                TemperatureAndHumidityThread::runLock = new rtos::Mutex("TemperatureAndHumidityThreadRunLock");
            }

            /**
             * @brief Destroy the Temperature And Humidity Thread object
             * 
             */
            TemperatureAndHumidityThread::~TemperatureAndHumidityThread(){
                delete TemperatureAndHumidityThread::instance;
                delete TemperatureAndHumidityThread::runLock;
            }

            /**
             * @brief Implements the Start method.
             * 
             * @return osStatus 
             */
            osStatus TemperatureAndHumidityThread::InternalStart(){
                if(TemperatureAndHumidityThread::stopped == true) return true;

                if(TemperatureAndHumidityThread::run != true){
                    if(TemperatureAndHumidityThread::runLock->trylock() == false){
                        return true;
                    }
                    mbed::Callback<void()> callback = mbed::Callback<void()>(
                        TemperatureAndHumidityThread::GetInstance(),
                        &TemperatureAndHumidityThread::Process
                    );
                    
                    TemperatureAndHumidityThread::run = true;
                    TemperatureAndHumidityThread::active = true;
                    return TemperatureAndHumidityThread::thread.start(callback);

                }

                if(
                    TemperatureAndHumidityThread::active != true
                ){
                    TemperatureAndHumidityThread::active = true;
                }

                return false;
                
            }

            /**
             * @brief Implements the Stop method.
             * 
             */
            void TemperatureAndHumidityThread::InternalStop(){
                TemperatureAndHumidityThread::run = false;
                TemperatureAndHumidityThread::active = false;
                TemperatureAndHumidityThread::stopped = true;
                TemperatureAndHumidityThread::thread.join();
                TemperatureAndHumidityThread::runLock->unlock();
            }

            /**
             * @brief Implements the Pause Method.
             * 
             */
            void TemperatureAndHumidityThread::InternalPause(){
                if(TemperatureAndHumidityThread::stopped == true) return;
                TemperatureAndHumidityThread::active = false;
            }

            /**
             * @brief The process that is run in the thread.
             * 
             */
            void TemperatureAndHumidityThread::Process(){
                sicet7::Serial::Console::Output("TemperatureAndHumidity Thread Starting.");
                do{
                    if(TemperatureAndHumidityThread::GetInstance()->active == true){
                        if(sicet7::Sensors::TemperatureAndHumidity::IsDefined() == true){
                            sicet7::Sensors::TemperatureAndHumidity::Get()->Read();
                        }
                    }
                    ThisThread::sleep_for(2000);
                }while(TemperatureAndHumidityThread::GetInstance()->run == true);
                sicet7::Serial::Console::Output("TemperatureAndHumidity Thread Stopping.");
            }

        }
    }
}