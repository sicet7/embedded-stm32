/**
 * @file TemperatureThread.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Implements the TemperatureThread class.
 * @version 0.1
 * @date 2019-01-25
 * 
 */
#include <classes/sicet7/Application/Threads/TemperatureThread/TemperatureThread.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Sensors/Temperature/Temperature.h>
namespace sicet7{
    namespace Application{
        namespace Threads{

            TemperatureThread* TemperatureThread::instance = 0;
            rtos::Mutex* TemperatureThread::singletonLock = new rtos::Mutex("TemperatureThreadSingletonLock");

            /**
             * @brief Returns a pointer to the current instance of the class.
             * 
             * @return TemperatureThread* 
             */
            TemperatureThread* TemperatureThread::GetInstance(){
                TemperatureThread::singletonLock->lock();
                if(TemperatureThread::instance == 0){
                    TemperatureThread::instance = new TemperatureThread();
                }
                TemperatureThread::singletonLock->unlock();
                return TemperatureThread::instance;
            }

            /**
             * @brief Starts the thread.
             * 
             * @return osStatus 
             */
            osStatus TemperatureThread::Start(){
                return TemperatureThread::GetInstance()->InternalStart();
            }

            /**
             * @brief Stop's the thread.
             * @warning THE THREAD CANNOT BE RESTARTED AFTER CALING THIS.
             * 
             */
            void TemperatureThread::Stop(){
                TemperatureThread::GetInstance()->InternalStop();
            }

            /**
             * @brief Pause's the thread.
             * 
             */
            void TemperatureThread::Pause(){
                TemperatureThread::GetInstance()->InternalPause();
            }

            /**
             * @brief Construct a new Temperature Thread object
             * 
             */
            TemperatureThread::TemperatureThread(){
                TemperatureThread::runLock = new rtos::Mutex("TemperatureThreadRunLock");
            }

            /**
             * @brief Destroy the Temperature Thread object
             * 
             */
            TemperatureThread::~TemperatureThread(){
                delete TemperatureThread::runLock;
                delete TemperatureThread::instance;
            }

            /**
             * @brief Implements the Start method.
             * 
             * @return osStatus 
             */
            osStatus TemperatureThread::InternalStart(){
                if(TemperatureThread::stopped == true) return true;

                if(TemperatureThread::run != true){
                    if(TemperatureThread::runLock->trylock() == false){
                        return true;
                    }
                    mbed::Callback<void()> callback = mbed::Callback<void()>(
                        TemperatureThread::GetInstance(),
                        &TemperatureThread::Process
                    );
                    
                    TemperatureThread::run = true;
                    TemperatureThread::active = true;
                    return TemperatureThread::thread.start(callback);

                }

                if(
                    TemperatureThread::active != true
                ){
                    TemperatureThread::active = true;
                }

                return false;
                
            }

            /**
             * @brief Implements the Stop method.
             * 
             */
            void TemperatureThread::InternalStop(){
                TemperatureThread::run = false;
                TemperatureThread::active = false;
                TemperatureThread::stopped = true;
                TemperatureThread::thread.join();
                TemperatureThread::runLock->unlock();
            }

            /**
             * @brief Implements the Pause method.
             * 
             */
            void TemperatureThread::InternalPause(){
                if(TemperatureThread::stopped == true) return;
                TemperatureThread::active = false;
            }

            /**
             * @brief The process that will be run in the thread.
             * 
             */
            void TemperatureThread::Process(){
                sicet7::Serial::Console::Output("Temperature Thread Starting.");
                do{
                    if(TemperatureThread::GetInstance()->active == true){
                        if(sicet7::Sensors::Temperature::IsDefined() == true){
                            sicet7::Sensors::Temperature::Get()->Read(true);
                        }
                    }
                    ThisThread::sleep_for(1);
                }while(TemperatureThread::GetInstance()->run == true);
                sicet7::Serial::Console::Output("Temperature Thread Stopping.");
            }

        }
    }
}
