#pragma once

#include <mbed.h>
#include <classes/sicet7/Lcd/Display/Display.h>

namespace sicet7{

    class Application{

        public:

            uint16_t menuStateDisplayed = 0;
            uint16_t textStateDisplayed = 0;

            uint16_t textState;
            uint16_t menuState;

            bool hasBeenCleared = false;

            uint32_t backgroundColor;
            uint32_t textColor;
            uint32_t clearColor;

            static Application* GetInstance();
            ~Application();

            //"Hardware" Mapping
            sicet7::Lcd::Display displayObj;

            //Run and Stop
            void Stop();
            int Run();

            //Sets the display up for a clear on next iteration of the loop.
            void ShouldClearDisplay(bool val);

            //For Display Output
            void RenderMenu();
            void RenderText();

            //Press detection limitors
            bool GetPressInProgress(int id);
            void SetPressInProgress(int id, bool state);

            //State checks
            bool IsSetupComplete();
            bool IsCleanUpComplete();

        private:

            bool running = false;
            bool pressInProgress[5];
            bool setupComplete;
            bool cleanUpComplete;
            bool doClearDisplay = false;

            void ClearDisplay();

            int Setup();
            int Loop();
            int CleanUp();

            //Singleton
            Application();
            static Application* instance;
    };

}