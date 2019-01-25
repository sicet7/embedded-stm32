#include <classes/sicet7/Sensors/Sound/Sound.h>
#include <cmath>
namespace sicet7{
    namespace Sensors{

        Sound* Sound::instance = 0;

        rtos::Mutex* Sound::singletonLock = new rtos::Mutex("SoundSensorSingletonLock");

        Sound* Sound::GetInstance(){
            Sound::singletonLock->lock();
            if(Sound::instance == 0){
                Sound::instance = new Sound();
            }
            Sound::singletonLock->unlock();
            return Sound::instance;
        }

        Sound::Sound(){
            Sound::readLock = new rtos::Mutex("SoundSensorReadLock");
        }

        Sound::~Sound(){
            delete Sound::instance;
            delete Sound::readLock;
        }

        void Sound::AnalogInput(AnalogIn* in){
            Sound::anInput = in;
        }

        uint32_t Sound::InternalRead(uint32_t length){

            if(Sound::anInput == 0) return 0.0f;

            uint64_t sum = 0;

            for(uint32_t i = 0; i < length; i++){
                uint32_t value = (uint32_t)round((Sound::anInput->read()*100000));
                sum += value;
            }

            return (uint32_t)round((sum/length));

        }

        Sound::Reading Sound::Read(){

            if(Sound::anInput == 0){//If the analog input is not set.
                return Sound::Reading();
            }

            Sound::readLock->lock();

            uint32_t pV = Sound::previusReading;
            uint32_t nV = Sound::InternalRead(1000);
            bool r = (pV < nV);
            uint32_t d = (r == true ? nV-pV : pV-nV);
            uint32_t dP = (pV == 0 ? 100 : (uint32_t)round(((d/pV)*100)));
            Sound::previusReading = nV;

            Sound::Reading reading;

            reading.previusValue = pV;
            reading.newValue = nV;
            reading.difference = d;
            reading.percentDifference = dP;
            reading.rise = r;

            Sound::readLock->unlock();

            return reading;

        }

    }
}