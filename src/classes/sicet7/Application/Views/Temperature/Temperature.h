#pragma once
#include <classes/sicet7/Lcd/Lcd.h>
namespace sicet7{
    namespace Application{
        namespace Views{
            class Temperature : public sicet7::Lcd::View{

                private: static Temperature* instance;
                private: static rtos::Mutex* instanceLock;

                public: static Temperature* GetInstance();

                private: Temperature();
                public: ~Temperature();

                public: virtual void CustomActivate() override;
                public: virtual void CustomDeactivate() override;
                public: virtual void CustomUpdate() override;

                public: static void Button_Trigger(Lcd::TouchObject* obj);

                private: void SetupDisplay();

                private: void Button1();

            };
        }
    }
}