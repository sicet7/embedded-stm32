#include <classes/sicet7/Application/Threads/TemperatureThread/TemperatureThread.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Sensors/Temperature/Temperature.h>
namespace sicet7{
    namespace Application{
        namespace Threads{

            TemperatureThread* TemperatureThread::instance = 0;
            rtos::Mutex* TemperatureThread::singletonLock = new rtos::Mutex("TemperatureThreadSingletonLock");

            TemperatureThread* TemperatureThread::GetInstance(){
                TemperatureThread::singletonLock->lock();
                if(TemperatureThread::instance == 0){
                    TemperatureThread::instance = new TemperatureThread();
                }
                TemperatureThread::singletonLock->unlock();
                return TemperatureThread::instance;
            }

            osStatus TemperatureThread::Start(){
                return TemperatureThread::GetInstance()->InternalStart();
            }

            void TemperatureThread::Stop(){
                TemperatureThread::GetInstance()->InternalStop();
            }

            void TemperatureThread::Pause(){
                TemperatureThread::GetInstance()->InternalPause();
            }

            TemperatureThread::TemperatureThread(){
                TemperatureThread::runLock = new rtos::Mutex("TemperatureThreadRunLock");
            }

            TemperatureThread::~TemperatureThread(){
                delete TemperatureThread::runLock;
            }

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

            void TemperatureThread::InternalStop(){
                TemperatureThread::run = false;
                TemperatureThread::active = false;
                TemperatureThread::stopped = true;
                TemperatureThread::thread.join();
                TemperatureThread::runLock->unlock();
            }

            void TemperatureThread::InternalPause(){
                if(TemperatureThread::stopped == true) return;
                TemperatureThread::active = false;
            }

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
