/**
 * @file MainMenu.h
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Defining the MainMenu View.
 * @version 0.1
 * @date 2019-01-23
 */
#include <classes/sicet7/Lcd/Lcd.h>
#include <mbed.h>
namespace sicet7{
    namespace Application{
        namespace Views{

            class MainMenu : public sicet7::Lcd::View{

                private: static MainMenu* instance;
                private: static rtos::Mutex* instanceLock;

                public: static MainMenu* GetInstance();

                private: MainMenu();
                public: ~MainMenu();

                public: virtual void CustomActivate() override;
                public: virtual void CustomDeactivate() override;
                public: virtual void CustomUpdate() override;

                private: void SetupDisplay();

                private: void Button1();
                private: void Button2();
                private: void Button3();
                private: void Button4();
                private: void Button5();
                private: void Button6();
                private: void Button7();
                private: void Button8();
                private: void Button9();
                private: void Button10();
                private: void Button11();
                private: void Button12();
                private: void Button13();
                private: void Button14();
                private: void Button15();
                private: void Button16();


            };

        }
    }
}