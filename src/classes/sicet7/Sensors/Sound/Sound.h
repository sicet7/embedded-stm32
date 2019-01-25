#pragma once
#include <mbed.h>
namespace sicet7{
    namespace Sensors{
        class Sound{

            private: static Sound* instance;

            private: static rtos::Mutex* singletonLock;

            protected: AnalogIn* anInput = 0;

            public: static Sound* GetInstance();

            public: void AnalogInput(AnalogIn* ai);

            private: rtos::Mutex* readLock;

            protected: uint32_t InternalRead(uint32_t length);

            private: uint32_t previusReading = 0;

            private: Sound();

            public: ~Sound();

            public: struct Reading{
                public: uint32_t previusValue = 0;
                public: uint32_t newValue = 0;
                public: uint32_t difference = 0;
                public: uint32_t percentDifference = 0;
                public: bool rise = false;
            };

            public: Reading Read();

        };
    }
}