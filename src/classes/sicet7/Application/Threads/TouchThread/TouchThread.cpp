#include <classes/sicet7/Application/Threads/TouchThread/TouchThread.h>
#include <classes/sicet7/Lcd/Lcd.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    namespace Application{
        namespace Threads{

            TouchThread* TouchThread::instance = 0;
            rtos::Mutex* TouchThread::singletonLock = new rtos::Mutex("TouchThreadSingletonLock");

            TouchThread* TouchThread::GetInstance(){
                TouchThread::singletonLock->lock();
                if(TouchThread::instance == 0){
                    TouchThread::instance = new TouchThread();
                }
                TouchThread::singletonLock->unlock();
                return TouchThread::instance;
            }

            osStatus TouchThread::Start(){
                return TouchThread::GetInstance()->InternalStart();
            }

            void TouchThread::Stop(){
                TouchThread::GetInstance()->InternalStop();
            }

            TouchThread::TouchThread(){
                TouchThread::runLock = new rtos::Mutex("TouchThreadRunLock");
            }

            TouchThread::~TouchThread(){
                delete TouchThread::runLock;
            }

            osStatus TouchThread::InternalStart(){
                if(TouchThread::runLock->trylock() == false) return osErrorOS;
                mbed::Callback<void()> callback = mbed::Callback<void()>(
                    TouchThread::GetInstance(),
                    &TouchThread::Process
                );
                TouchThread::run = true;
                return TouchThread::thread.start(callback);
            }

            void TouchThread::InternalStop(){
                TouchThread::run = false;
                TouchThread::thread.join();
                TouchThread::runLock->unlock();
            }

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
