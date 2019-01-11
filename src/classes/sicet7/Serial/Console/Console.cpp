#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Serial/Serial.h>
namespace sicet7{
    namespace Serial{
        void Console::Output(const char* customString){
            sicet7::Serial::serialConnection.printf(customString);
            sicet7::Serial::serialConnection.printf("\r\n");
        }
    }
}