#pragma once
#include <classes/sicet7/Lcd/Lcd.h>
namespace sicet7{
    namespace Application{
        namespace Views{
            class Light : public Lcd::View{
                private: static Light* instance;
                private: static rtos::Mutex* instanceLock;
                
                public: static Lcd::UpdatableOutput* output;
                public: static AnalogIn* analogInput;

                public: static Light* GetInstance();

                private: Light();
                public: ~Light();

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