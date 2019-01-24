#pragma once
#include <classes/sicet7/Lcd/Lcd.h>
namespace sicet7{
    namespace Application{
        namespace Views{
            class Humidity : public Lcd::View{
                private: static Humidity* instance;
                private: static rtos::Mutex* instanceLock;

                public: static Lcd::UpdatableOutput* output;

                public: static Humidity* GetInstance();

                private: Humidity();
                public: ~Humidity();

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