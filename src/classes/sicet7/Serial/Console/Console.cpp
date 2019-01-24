#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Application/Core/Core.h>
#include <mbed.h>
namespace sicet7{
    namespace Serial{
        mbed::Serial* Console::serial = 0;
        void Console::Output(const char* customString, bool newline, bool threadPrefix){
            static rtos::Mutex _mtex;
            ScopedLock<rtos::Mutex> lock(_mtex);

            if(Console::serial == 0){
                Console::serial = new mbed::Serial(USBTX,USBRX,9600);
            }

            if(sicet7::Application::Core::IsInterupt() == true){
                threadPrefix = false;
            }

            char* newString;

            if(threadPrefix == true){
                char buffer[68];
                sprintf(buffer,"#%d : ",(uint64_t)ThisThread::get_id());
                newString = strcat(buffer,customString);
            }else{
                newString = (char*)customString;
            }

            Console::serial->printf(newString);
            
            if(newline == true){
                Console::serial->printf("\r\n");
            }
            
        }

        void Console::Output(const char* customString, bool newline){
            Console::Output(customString,newline,true);
        }

        void Console::Output(const char* customString){
            Console::Output(customString,true);
        }
    }
}