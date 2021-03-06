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
#include <classes/sicet7/Application/Views/Temperature/Temperature.h>
#include <classes/sicet7/Application/Views/Sound/Sound.h>
#include <classes/sicet7/Application/Views/Light/Light.h>
#include <classes/sicet7/Application/Views/Humidity/Humidity.h>
#include <classes/sicet7/Lcd/Lcd.h>
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

            void MainMenu::Button_Trigger(Lcd::TouchObject* obj){

                if(obj->GetName() == "Button1"){
                    if(obj->IsPress() == false){
                        sicet7::Lcd::Get()->ActivateView(sicet7::Application::Views::Temperature::GetInstance());
                    }
                    return;
                }
                
                if(obj->GetName() == "Button2"){
                    if(obj->IsPress() == false){
                        sicet7::Lcd::Get()->ActivateView(sicet7::Application::Views::Sound::GetInstance());
                    }
                    return;
                }

                if(obj->GetName() == "Button3"){
                    if(obj->IsPress() == false){
                        sicet7::Lcd::Get()->ActivateView(sicet7::Application::Views::Light::GetInstance());
                    }
                    return;
                }

                if(obj->GetName() == "Button4"){
                    if(obj->IsPress() == false){
                        sicet7::Lcd::Get()->ActivateView(sicet7::Application::Views::Humidity::GetInstance());
                    }
                    return;
                }

                sicet7::Serial::Console::Output("No Action Bound to this button.");
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

                Lcd::TouchObject* touchObj = new Lcd::TouchObject(
                    "Button1",
                    Lcd::Position{1,1},
                    Lcd::Position{119,67}
                );

                touchObj->triggerFunction = &MainMenu::Button_Trigger;
                MainMenu::AddTouchObject(touchObj);

                MainMenu::AddDisplayObject("MainMenu_Button1_Container",rectangle);
                MainMenu::AddDisplayObject("MainMenu_Button1_Text",text);
                MainMenu::AddRelationship("MainMenu_Button1_Container","MainMenu_Button1_Text");
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

                Lcd::TouchObject* touchObj = new Lcd::TouchObject(
                    "Button2",
                    Lcd::Position{121,1},
                    Lcd::Position{239,67}
                );

                touchObj->triggerFunction = &MainMenu::Button_Trigger;
                MainMenu::AddTouchObject(touchObj);

                MainMenu::AddDisplayObject("MainMenu_Button2_Container",rectangle);
                MainMenu::AddDisplayObject("MainMenu_Button2_Text",text);
                MainMenu::AddRelationship("MainMenu_Button2_Container","MainMenu_Button2_Text");
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

                Lcd::TouchObject* touchObj = new Lcd::TouchObject(
                    "Button3",
                    Lcd::Position{241,1},
                    Lcd::Position{359,67}
                );

                touchObj->triggerFunction = &MainMenu::Button_Trigger;
                MainMenu::AddTouchObject(touchObj);

                MainMenu::AddDisplayObject("MainMenu_Button3_Container",rectangle);
                MainMenu::AddDisplayObject("MainMenu_Button3_Text",text);
                MainMenu::AddRelationship("MainMenu_Button3_Container","MainMenu_Button3_Text");
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

                Lcd::TouchObject* touchObj = new Lcd::TouchObject(
                    "Button4",
                    Lcd::Position{361,1},
                    Lcd::Position{478,67}
                );

                touchObj->triggerFunction = &MainMenu::Button_Trigger;
                MainMenu::AddTouchObject(touchObj);

                MainMenu::AddDisplayObject("MainMenu_Button4_Container",rectangle);
                MainMenu::AddDisplayObject("MainMenu_Button4_Text",text);
                MainMenu::AddRelationship("MainMenu_Button4_Container","MainMenu_Button4_Text");
            }
            void MainMenu::Button5(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{0,68},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("MainMenu_Button5_Container",rectangle);
            }
            void MainMenu::Button6(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{120,68},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("MainMenu_Button6_Container",rectangle);
            }
            void MainMenu::Button7(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{240,68},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("MainMenu_Button7_Container",rectangle);
            }
            void MainMenu::Button8(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{360,68},
                    Lcd::Size{119,68}
                );

                MainMenu::AddDisplayObject("MainMenu_Button8_Container",rectangle);
            }
            void MainMenu::Button9(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{0,136},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("MainMenu_Button9_Container",rectangle);
            }
            void MainMenu::Button10(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{120,136},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("MainMenu_Button10_Container",rectangle);
            }
            void MainMenu::Button11(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{240,136},
                    Lcd::Size{120,68}
                );

                MainMenu::AddDisplayObject("MainMenu_Button11_Container",rectangle);
            }
            void MainMenu::Button12(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{360,136},
                    Lcd::Size{119,68}
                );

                MainMenu::AddDisplayObject("MainMenu_Button12_Container",rectangle);
            }
            void MainMenu::Button13(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{0,204},
                    Lcd::Size{120,67}
                );

                MainMenu::AddDisplayObject("MainMenu_Button13_Container",rectangle);
            }
            void MainMenu::Button14(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{120,204},
                    Lcd::Size{120,67}
                );

                MainMenu::AddDisplayObject("MainMenu_Button14_Container",rectangle);
            }
            void MainMenu::Button15(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{240,204},
                    Lcd::Size{120,67}
                );

                MainMenu::AddDisplayObject("MainMenu_Button15_Container",rectangle);
            }
            void MainMenu::Button16(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{360,204},
                    Lcd::Size{119,67}
                );

                MainMenu::AddDisplayObject("MainMenu_Button16_Container",rectangle);
            }
        }
    }
}