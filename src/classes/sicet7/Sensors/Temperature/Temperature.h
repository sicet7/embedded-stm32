#pragma once
#include <mbed.h>
namespace sicet7{
    namespace Sensors{
        class Temperature{

            private:

                //Selecting input pin
                static AnalogIn* analogInput;

                //Last read value
                mutable volatile float lastReadValue = 0.0f;

                //Device Constants
                int bConstant = 4250;//  = 4250
                uint64_t resistance = 100000;//  = 100000

                //singleton
                Temperature(PinName pin, int b, uint64_t resistance);
                static Temperature* instance;
                static rtos::Mutex* lockable;

            public:

                //Singleton Methods
                static Temperature* Get();
                static void Set(PinName pin);
                static void Set(PinName pin, int b);
                static void Set(PinName pin, int b, uint64_t resistance);
                ~Temperature();

                //Modify B Constant
                int B();

                //Set resistance
                uint64_t Resistance();

                //Read data methods.
                float Read(bool update);
                float Celsius();
                float Fahrenheit();
                float Kelvin();
                
        };
    }
}
