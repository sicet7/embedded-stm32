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