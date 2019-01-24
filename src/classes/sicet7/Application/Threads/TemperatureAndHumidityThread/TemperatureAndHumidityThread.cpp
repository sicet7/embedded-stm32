#include <classes/sicet7/Application/Threads/TemperatureAndHumidityThread/TemperatureAndHumidityThread.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Sensors/TemperatureAndHumidity/TemperatureAndHumidity.h>
namespace sicet7{
    namespace Application{
        namespace Threads{

            TemperatureAndHumidityThread* TemperatureAndHumidityThread::instance = 0;
            rtos::Mutex* TemperatureAndHumidityThread::singletonLock = new rtos::Mutex("TemperatureAndHumidityThreadSingletonLock");

            TemperatureAndHumidityThread* TemperatureAndHumidityThread::GetInstance(){
                TemperatureAndHumidityThread::singletonLock->lock();
                if(TemperatureAndHumidityThread::instance == 0){
                    TemperatureAndHumidityThread::instance = new TemperatureAndHumidityThread();
                }
                TemperatureAndHumidityThread::singletonLock->unlock();
                return TemperatureAndHumidityThread::instance;
            }

            osStatus TemperatureAndHumidityThread::Start(){
                return TemperatureAndHumidityThread::GetInstance()->InternalStart();
            }

            void TemperatureAndHumidityThread::Stop(){
                TemperatureAndHumidityThread::GetInstance()->InternalStop();
            }

            void TemperatureAndHumidityThread::Pause(){
                TemperatureAndHumidityThread::GetInstance()->InternalPause();
            }

            TemperatureAndHumidityThread::TemperatureAndHumidityThread(){
                TemperatureAndHumidityThread::runLock = new rtos::Mutex("TemperatureAndHumidityThreadRunLock");
            }

            TemperatureAndHumidityThread::~TemperatureAndHumidityThread(){
                delete TemperatureAndHumidityThread::runLock;
            }

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

            void TemperatureAndHumidityThread::InternalStop(){
                TemperatureAndHumidityThread::run = false;
                TemperatureAndHumidityThread::active = false;
                TemperatureAndHumidityThread::stopped = true;
                TemperatureAndHumidityThread::thread.join();
                TemperatureAndHumidityThread::runLock->unlock();
            }

            void TemperatureAndHumidityThread::InternalPause(){
                if(TemperatureAndHumidityThread::stopped == true) return;
                TemperatureAndHumidityThread::active = false;
            }

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