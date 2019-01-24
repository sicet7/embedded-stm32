#pragma once

#include <mbed.h>
#include <classes/sicet7/Sensors/Temperature/Temperature.h>
#include <classes/sicet7/Lcd/Lcd.h>

namespace sicet7{

    namespace Application{

        class Main{

            public:

                DigitalOut* onBoardLed;

                static Lcd::View* activeView;

                static Main* GetInstance();
                ~Main();

                //Run and Stop
                void Stop();
                int Run();

                //Informational
                void PrintDeviceInfo();

                //State checks
                bool IsSetupComplete();
                bool IsCleanUpComplete();

            private:

                bool running = false;
                bool pressInProgress[5];
                bool setupComplete;
                bool cleanUpComplete;

                int Setup();
                int Loop();
                int CleanUp();

                //Singleton
                Main();
                static Main* instance;
        };

    }

}