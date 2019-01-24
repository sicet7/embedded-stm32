#pragma once
#include <mbed.h>
#include <DHT.h>
namespace sicet7{
    namespace Sensors{
        class TemperatureAndHumidity{

            private: DHT* input = 0;

            private: float humidity = 0.0f;
            private: float celcius = 0.0f;
            private: float farenheit = 0.0f;
            private: float kelvin = 0.0f;

            private: TemperatureAndHumidity(DHT* dhtPtr);

            private: static TemperatureAndHumidity* instance;
            private: static rtos::Mutex* lockable;

            private: void HandleError(int errorCode);
            public: void Read();

            public: static bool IsDefined();
            public: static TemperatureAndHumidity* Get();
            public: static void Set(DHT* dhtPtr);
            public: ~TemperatureAndHumidity();

            public: float ReadHumidity();

            public: float ReadCelcius();

            public: float ReadFarenheit();

            public: float ReadKelvin();


        };
    }
}