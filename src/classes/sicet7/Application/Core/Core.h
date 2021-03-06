/**
 * @file Core.h
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Definition of the Application::Core Class.
 * @version 0.1
 * @date 2019-01-25
 * 
 */
#pragma once
#include <mbed.h>
namespace sicet7{
    namespace Application{
        class Core{

            private:
                static uint32_t GetTickRateHz();
                static uint32_t GetTickPerMs();
            public:
                static void PrintDeviceInfo();
                static uint32_t Millis();
                static bool IsInterupt();

        };
    }
}