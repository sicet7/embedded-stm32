/**
 * @file Core.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Implements Core Application Functionality
 * @version 0.1
 * @date 2019-01-25
 * 
 */
#include <classes/sicet7/Application/Core/Core.h>
#include <mbed.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <cmath>
namespace sicet7{
    namespace Application{

        /**
         * @brief Returns the tickrate of the processor.
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
         * @brief returns the amount of milliseconds passed every tick.
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
         * @brief Returns the amount of milliseconds passed since the program started.
         * @warning CAN OVERFLOW.
         * @return uint32_t 
         */
        uint32_t Core::Millis(){
            
            uint32_t ticks = HAL_GetTick();
            uint32_t tpms = Core::GetTickPerMs();
            uint32_t millis = (uint32_t)std::floor(ticks/tpms);
            return millis;

        }

        /**
         * @brief Prints the Processor Information to the Serial Output.
         * 
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