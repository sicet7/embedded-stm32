/**
 * @file MainMenu.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Implmentation of MainMenu View.
 * @version 0.1
 * @date 2019-01-23
 */
#include <classes/sicet7/Application/Views/MainMenu/MainMenu.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Sensors/Temperature/Temperature.h>
namespace sicet7{
    namespace Application{
        namespace Views{

            MainMenu* MainMenu::instance = 0;

            rtos::Mutex* MainMenu::instanceLock = new rtos::Mutex("MainMenuInstanceLock");

            void MainMenu::CustomActivate(){}
            void MainMenu::CustomDeactivate(){}
            void MainMenu::CustomUpdate(){}

            MainMenu* MainMenu::GetInstance(){
                MainMenu::instanceLock->lock();
                if(MainMenu::instance == 0){
                    MainMenu::instance = new MainMenu();
                }
                MainMenu::instanceLock->unlock();
                return MainMenu::instance;
            }

            MainMenu::~MainMenu(){
                delete MainMenu::instance;
            }

            //Width: 480
            //Height: 272
            MainMenu::MainMenu(){
                MainMenu::SetupDisplay();
                MainMenu::Button1();
                MainMenu::Button2();
                MainMenu::Button3();
                MainMenu::Button4();
                MainMenu::Button5();
                MainMenu::Button6();
                MainMenu::Button7();
                MainMenu::Button8();
                MainMenu::Button9();
                MainMenu::Button10();
                MainMenu::Button11();
                MainMenu::Button12();
                MainMenu::Button13();
                MainMenu::Button14();
                MainMenu::Button15();
                MainMenu::Button16();
            }

            void MainMenu::SetupDisplay(){
                Lcd::Get()->Display()->SetBackColor(LCD_COLOR_BLACK);
                Lcd::Get()->Display()->SetTextColor(LCD_COLOR_GREEN);
            }

            void MainMenu::Button1(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{0,0},
                    Lcd::Size{120,68}
                );

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{1,1},
                    Lcd::Position{119,67},
                    "Temp.\nSensor",
                    &Font16,
                    CENTER_MODE,
                    0,
                    19
                );

                MainMenu::AddDisplayObject("Button1_Container",rectangle);
                MainMenu::AddDisplayObject("Button1_Text",text);
                MainMenu::AddRelationship("Button1_Container","Button1_Text");
            }

            void MainMenu::Button2(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{120,0},
                    Lcd::Size{120,68}
                );

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{121,1},
                    Lcd::Position{239,67},
                    "Sound\nSensor",
                    &Font16,
                    CENTER_MODE,
                    0,
                    19
                );

                MainMenu::AddDisplayObject("Button2_Container",rectangle);
                MainMenu::AddDisplayObject("Button2_Text",text);
                MainMenu::AddRelationship("Button2_Container","Button2_Text");
            }
            void MainMenu::Button3(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{240,0},
                    Lcd::Size{120,68}
                );

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{241,1},
                    Lcd::Position{359,67},
                    "Light\nSensor",
                    &Font16,
                    CENTER_MODE,
                    0,
                    19
                );

                MainMenu::AddDisplayObject("Button3_Container",rectangle);
                MainMenu::AddDisplayObject("Button3_Text",text);
                MainMenu::AddRelationship("Button3_Container","Button3_Text");
            }
            void MainMenu::Button4(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{360,0},
                    Lcd::Size{119,68}
                );

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{361,1},
                    Lcd::Position{478,67},
                    "Humidity\nSensor",
                    &Font16,
                    CENTER_MODE,
                    0,
                    19
                );

                MainMenu::AddDisplayObject("Button4_Container",rectangle);
                MainMenu::AddDisplayObject("Button4_Text",text);
                MainMenu::AddRelationship("Button4_Container","Button4_Text");
            }
            void MainMenu::Button5(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{0,68},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("Button5_Container",rectangle);
            }
            void MainMenu::Button6(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{120,68},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("Button6_Container",rectangle);
            }
            void MainMenu::Button7(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{240,68},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("Button7_Container",rectangle);
            }
            void MainMenu::Button8(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{360,68},
                    Lcd::Size{119,68}
                );

                MainMenu::AddDisplayObject("Button8_Container",rectangle);
            }
            void MainMenu::Button9(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{0,136},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("Button9_Container",rectangle);
            }
            void MainMenu::Button10(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{120,136},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("Button10_Container",rectangle);
            }
            void MainMenu::Button11(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{240,136},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("Button11_Container",rectangle);
            }
            void MainMenu::Button12(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{360,136},
                    Lcd::Size{119,68}
                );

                MainMenu::AddDisplayObject("Button12_Container",rectangle);
            }
            void MainMenu::Button13(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{0,204},
                    Lcd::Size{120,67}
                );

                MainMenu::AddDisplayObject("Button13_Container",rectangle);
            }
            void MainMenu::Button14(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{120,204},
                    Lcd::Size{120,67}
                );

                MainMenu::AddDisplayObject("Button14_Container",rectangle);
            }
            void MainMenu::Button15(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{240,204},
                    Lcd::Size{120,67}
                );

                MainMenu::AddDisplayObject("Button15_Container",rectangle);
            }
            void MainMenu::Button16(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{360,204},
                    Lcd::Size{119,67}
                );

                MainMenu::AddDisplayObject("Button16_Container",rectangle);
            }
        }
    }
}