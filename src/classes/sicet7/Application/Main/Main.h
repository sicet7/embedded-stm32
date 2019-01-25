/**
 * @file Main.h
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Definition of the Application::Main class.
 * @version 0.1
 * @date 2019-01-25
 * 
 */
#pragma once

#include <mbed.h>
#include <classes/sicet7/Sensors/Temperature/Temperature.h>
#include <classes/sicet7/Lcd/Lcd.h>

namespace sicet7{

    namespace Application{

        class Main{

            public:

                DigitalOut* onBoardLed;

                static rtos::Mutex* singletonLock;

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