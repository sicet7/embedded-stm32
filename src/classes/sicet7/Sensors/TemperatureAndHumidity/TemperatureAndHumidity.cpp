#include <classes/sicet7/Sensors/TemperatureAndHumidity/TemperatureAndHumidity.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    namespace Sensors{

        TemperatureAndHumidity* TemperatureAndHumidity::instance = 0;

        rtos::Mutex* TemperatureAndHumidity::lockable = new rtos::Mutex("TemperatureAndHumiditySensor");

        TemperatureAndHumidity* TemperatureAndHumidity::Get(){

            if(TemperatureAndHumidity::IsDefined() != true) return 0;

            return TemperatureAndHumidity::instance;

        }

        void TemperatureAndHumidity::Set(DHT* dhtPtr){
            TemperatureAndHumidity::lockable->lock();
            if(TemperatureAndHumidity::IsDefined() == true){
                delete TemperatureAndHumidity::instance;
            }
            TemperatureAndHumidity::instance = new TemperatureAndHumidity(dhtPtr);
            TemperatureAndHumidity::lockable->unlock();
        }

        TemperatureAndHumidity::TemperatureAndHumidity(DHT* dhtPtr){
            TemperatureAndHumidity::input = dhtPtr;
        }

        TemperatureAndHumidity::~TemperatureAndHumidity(){
            delete TemperatureAndHumidity::input;
        }

        bool TemperatureAndHumidity::IsDefined(){
            return (TemperatureAndHumidity::instance != 0);
        }

        void TemperatureAndHumidity::Read(){

            TemperatureAndHumidity::lockable->lock();
            int err = TemperatureAndHumidity::input->readData();

            if(err == ERROR_NONE){
                TemperatureAndHumidity::humidity = TemperatureAndHumidity::input->ReadHumidity();
                TemperatureAndHumidity::celcius = TemperatureAndHumidity::input->ReadTemperature(CELCIUS);
                TemperatureAndHumidity::farenheit = TemperatureAndHumidity::input->ReadTemperature(FARENHEIT);
                TemperatureAndHumidity::kelvin = TemperatureAndHumidity::input->ReadTemperature(KELVIN);
            }

            TemperatureAndHumidity::HandleError(err);
            TemperatureAndHumidity::lockable->unlock();

        }

        void TemperatureAndHumidity::HandleError(int errorCode){

            if(errorCode == ERROR_NONE) return;

            switch(errorCode){
                case BUS_BUSY:
                    sicet7::Serial::Console::Output("Bus Busy.");
                break;
                case ERROR_NOT_PRESENT:
                    sicet7::Serial::Console::Output("Not Present.");
                break;
                case ERROR_ACK_TOO_LONG:
                    sicet7::Serial::Console::Output("ACK too Long.");
                break;
                case ERROR_SYNC_TIMEOUT:
                    sicet7::Serial::Console::Output("Sync Timeout.");
                break;
                case ERROR_DATA_TIMEOUT:
                    sicet7::Serial::Console::Output("Data Timeout.");
                break;
                case ERROR_CHECKSUM:
                    sicet7::Serial::Console::Output("Checksum Error.");
                break;
                case ERROR_NO_PATIENCE:
                    sicet7::Serial::Console::Output("No Patience.");
                break;
                default:
                    sicet7::Serial::Console::Output("Unknown Error.");
                break;
            }
        }

        float TemperatureAndHumidity::ReadHumidity(){
            return TemperatureAndHumidity::humidity;
        }

        float TemperatureAndHumidity::ReadCelcius(){
            return TemperatureAndHumidity::celcius;
        }

        float TemperatureAndHumidity::ReadFarenheit(){
            return TemperatureAndHumidity::farenheit;
        }

        float TemperatureAndHumidity::ReadKelvin(){
            return TemperatureAndHumidity::kelvin;
        }

    }
}