#pragma once
#include <classes/sicet7/Lcd/Lcd.h>
namespace sicet7{
    namespace Application{
        namespace Views{
            class Sound : public Lcd::View{
                private: static Sound* instance;
                private: static rtos::Mutex* instanceLock;

                public: static Sound* GetInstance();

                private: Sound();
                public: ~Sound();

                public: virtual void CustomActivate() override;
                public: virtual void CustomDeactivate() override;
                public: virtual void CustomUpdate() override;

                public: static void Button_Trigger(Lcd::TouchObject* obj);

                private: void SetupDisplay();

                private: void Button1();

                private: void MainText();

            };
        }
    }
}