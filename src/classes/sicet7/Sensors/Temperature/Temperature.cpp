/*#include <classes/sicet7/Sensors/Temperature/Temperature.h>
#include <DHT.h>
#include <cmath>
namespace sicet7{
    namespace Sensors{
        int32_t Temperature::ReadC(){
            sicet7::Sensors::onBoardAnalogPinOne.readData();
            int32_t b = (int32_t)roundf(sicet7::Sensors::onBoardAnalogPinOne.ReadTemperature(CELCIUS));
            return b;
        }
        int32_t Temperature::ReadF(){
            sicet7::Sensors::onBoardAnalogPinOne.readData();
            int32_t b = (int32_t)roundf(sicet7::Sensors::onBoardAnalogPinOne.ReadTemperature(FARENHEIT));
            return b;
        }
        int32_t Temperature::ReadK(){
            sicet7::Sensors::onBoardAnalogPinOne.readData();
            int32_t b = (int32_t)roundf(sicet7::Sensors::onBoardAnalogPinOne.ReadTemperature(KELVIN));
            return b;
        }
    }
}*/