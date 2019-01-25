/**
 * @file TouchThread.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Implements the TouchThread class.
 * @version 0.1
 * @date 2019-01-25
 * 
 */
#include <classes/sicet7/Application/Threads/TouchThread/TouchThread.h>
#include <classes/sicet7/Lcd/Lcd.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    namespace Application{
        namespace Threads{

            TouchThread* TouchThread::instance = 0;
            rtos::Mutex* TouchThread::singletonLock = new rtos::Mutex("TouchThreadSingletonLock");

            /**
             * @brief Returns a pointer to the current instance of this class.
             * 
             * @return TouchThread* 
             */
            TouchThread* TouchThread::GetInstance(){
                TouchThread::singletonLock->lock();
                if(TouchThread::instance == 0){
                    TouchThread::instance = new TouchThread();
                }
                TouchThread::singletonLock->unlock();
                return TouchThread::instance;
            }

            /**
             * @brief Starts the thread.
             * 
             * @return osStatus 
             */
            osStatus TouchThread::Start(){
                return TouchThread::GetInstance()->InternalStart();
            }

            /**
             * @brief Stops the thread.
             * @warning The thread cannot be restarted after calling this.
             * 
             */
            void TouchThread::Stop(){
                TouchThread::GetInstance()->InternalStop();
            }

            /**
             * @brief Construct a new Touch Thread object
             * 
             */
            TouchThread::TouchThread(){
                TouchThread::runLock = new rtos::Mutex("TouchThreadRunLock");
            }

            /**
             * @brief Destroy the Touch Thread object
             * 
             */
            TouchThread::~TouchThread(){
                delete TouchThread::runLock;
                delete TouchThread::instance;
            }

            /**
             * @brief Implements the Start method.
             * 
             * @return osStatus 
             */
            osStatus TouchThread::InternalStart(){
                if(TouchThread::runLock->trylock() == false) return osErrorOS;
                mbed::Callback<void()> callback = mbed::Callback<void()>(
                    TouchThread::GetInstance(),
                    &TouchThread::Process
                );
                TouchThread::run = true;
                return TouchThread::thread.start(callback);
            }

            /**
             * @brief Implements the Stop method.
             * 
             */
            void TouchThread::InternalStop(){
                TouchThread::run = false;
                TouchThread::thread.join();
                TouchThread::runLock->unlock();
            }

            /**
             * @brief The method that will be run in the thread.
             * 
             */
            void TouchThread::Process(){
                sicet7::Serial::Console::Output("Touch Thread Starting.");
                while(TouchThread::GetInstance()->run == true){
                    if(Lcd::Get()->CurrentView() != 0){
                        Lcd::Get()->CurrentView()->ProcessTouch();
                    }
                    ThisThread::sleep_for(1);
                }
                sicet7::Serial::Console::Output("Touch Thread Stopping.");
            }

        }
    }
}
