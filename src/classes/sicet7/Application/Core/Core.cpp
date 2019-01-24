#include <classes/sicet7/Application/Core/Core.h>
#include <mbed.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <cmath>
namespace sicet7{
    namespace Application{

        /**
         * @file Core.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/16/2019
         * 
         * @private
         * 
         * @return uint32_t
         */
        uint32_t Core::GetTickRateHz(){
            uint32_t tickrate;
            switch(HAL_GetTickFreq()){
                case HAL_TICK_FREQ_1KHZ:
                    tickrate = 1000;
                break;
                case HAL_TICK_FREQ_100HZ:
                    tickrate = 100;
                break;
                case HAL_TICK_FREQ_10HZ:
                    tickrate = 10;
                break;
                default:
                    tickrate = 1000;
                break;
            }
            return tickrate;
        }

        /**
         * @file Core.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/16/2019
         * 
         * @private
         * 
         * @return uint32_t
         */
        uint32_t Core::GetTickPerMs(){
            uint32_t tickPerMs;
            switch(HAL_GetTickFreq()){
                case HAL_TICK_FREQ_1KHZ:
                    tickPerMs = 1;
                break;
                case HAL_TICK_FREQ_100HZ:
                    tickPerMs = 10;
                break;
                case HAL_TICK_FREQ_10HZ:
                    tickPerMs = 100;
                break;
                default:
                    tickPerMs = 1;
                break;
            }
            return tickPerMs;
        }

        /**
         * @file Core.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/16/2019
         * 
         * @public
         * 
         * @return uint32_t
         */
        uint32_t Core::Millis(){
            
            uint32_t ticks = HAL_GetTick();
            uint32_t tpms = Core::GetTickPerMs();
            uint32_t millis = (uint32_t)std::floor(ticks/tpms);
            return millis;

        }

        /**
         * @file Core.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/16/2019
         * 
         * @public
         * 
         * @return void
         */
        void Core::PrintDeviceInfo(){

            char scc_buffer[64];
            sprintf(scc_buffer,"%u Hz",SystemCoreClock);
            sicet7::Serial::Console::Output("Core Clock = ",false);
            sicet7::Serial::Console::Output(scc_buffer,true,false);
            
            char tf_buffer[64];
            sprintf(tf_buffer,"%u Hz",Core::GetTickRateHz());
            sicet7::Serial::Console::Output("Tick Frequency = ",false);
            sicet7::Serial::Console::Output(tf_buffer,true,false);

            char tpms_buffer[32];
            sprintf(tpms_buffer,"%u t",Core::GetTickPerMs());
            sicet7::Serial::Console::Output("Tick Per Ms = ",false);
            sicet7::Serial::Console::Output(tpms_buffer,true,false);

        }

        bool Core::IsInterupt(){
            return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0 ;
        }

    }
}