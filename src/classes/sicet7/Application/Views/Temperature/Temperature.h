#pragma once
#include <classes/sicet7/Lcd/Lcd.h>
namespace sicet7{
    namespace Application{
        namespace Views{
            class Temperature : public sicet7::Lcd::View{

                private: static Temperature* instance;
                private: static rtos::Mutex* instanceLock;

                public: static Temperature* GetInstance();

                public: Lcd::UpdatableOutput* temp = 0;
                public: uint8_t temperatureFormat = 0;

                private: Temperature();
                public: ~Temperature();

                public: virtual void CustomActivate() override;
                public: virtual void CustomDeactivate() override;
                public: virtual void CustomUpdate() override;

                public: static void Button_Trigger(Lcd::TouchObject* obj);

                private: void SetupDisplay();

                private: void Button1();
                private: void Button2();
                private: void Button3();
                private: void Button4();
                private: void MainText();

            };
        }
    }
}