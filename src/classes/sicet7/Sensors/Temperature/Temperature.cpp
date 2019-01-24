#include <classes/sicet7/Sensors/Temperature/Temperature.h>
#include <DHT.h>
#include <cmath>
#include <mbed.h>
#include <classes/sicet7/Serial/Console/Console.h>

namespace sicet7{
    namespace Sensors{

        //Default Values
        AnalogIn* Temperature::analogInput = 0;
        Temperature* Temperature::instance = 0;
        rtos::Mutex* Temperature::lockable = new rtos::Mutex("sicet7::Sensors::Temperature");

        bool Temperature::IsDefined(){
            return (Temperature::instance != 0);
        }

        Temperature::Temperature(PinName pin, int b, uint64_t resistance){
            
            if(b >= 4250 && b <= 4299){
                Temperature::bConstant = b;
            }else{
                Temperature::bConstant = 4250;
            }

            if(resistance >= 1 && resistance <= 9100000){
                Temperature::resistance = resistance;
            }else{
                Temperature::resistance = 100000;
            }

            if(Temperature::analogInput == 0){
                Temperature::analogInput = new AnalogIn(pin);
            }

        }

        Temperature* Temperature::Get() { 
            lockable->lock();
            if(Temperature::instance == 0){
                Temperature::instance = new Temperature(A0,-1,0);
            }
            lockable->unlock();
            return Temperature::instance;
        }

        void Temperature::Set(PinName pin, int b, uint64_t res){
            Temperature::instance = new Temperature(pin,b,res);
        }
        
        void Temperature::Set(PinName pin, int b){
            Temperature::instance = new Temperature(pin,b,0);
        }

        void Temperature::Set(PinName pin){
            Temperature::instance = new Temperature(pin,-1,0);
        }

        int Temperature::B(){
            return Temperature::bConstant;
        }

        uint64_t Temperature::Resistance(){
            return Temperature::resistance;
        }

        float Temperature::Read(bool update){
            lockable->lock();
            float tmp;
            if(update == true){
                tmp = Temperature::analogInput->read();
                Temperature::lastReadValue = tmp;
            }
            tmp = Temperature::lastReadValue;
            lockable->unlock();
            return tmp;
        }

        float Temperature::Celsius(){
            float lRV = Temperature::Read(false);//update if updateThread is not running.
            float temperature;
            int B = Temperature::B();               // B value of the thermistor
            uint64_t R0 = Temperature::Resistance();            // R0 = 100k
            float R = 1.0f/lRV-1.0f;
            R = R0*R;
            temperature = 1.0/(log(R/100000)/B+1/298.15)-273.15;
            return temperature;

        }

        float Temperature::Fahrenheit(){
            return (Temperature::Celsius()*1.8f)+32;
        }

        float Temperature::Kelvin(){
            return Temperature::Celsius()+273.15f;
        }

    }
}