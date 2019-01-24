#include <classes/sicet7/Application/Views/Light/Light.h>
#include <mbed.h>
#include <classes/sicet7/Application/Views/MainMenu/MainMenu.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    namespace Application{
        namespace Views{

            Light* Light::instance = 0;
            
            rtos::Mutex* Light::instanceLock = new rtos::Mutex("LightSensorViewInstanceLock");

            Light* Light::GetInstance(){

                Light::instanceLock->lock();
                if(Light::instance == 0){
                    Light::instance = new Light();
                }
                Light::instanceLock->unlock();
                return Light::instance;

            }

            Light::~Light(){}
            Light::Light(){
                Light::SetupDisplay();
                Light::Button1();
            }

            void Light::CustomActivate(){}
            void Light::CustomDeactivate(){}
            void Light::CustomUpdate(){}

            void Light::Button_Trigger(Lcd::TouchObject* obj){

                if(obj->GetName() == "Button1"){
                    if(obj->IsPress() == false){
                        Lcd::Get()->ActivateView(
                            sicet7::Application::Views::MainMenu::GetInstance()
                        );
                    }
                    return;
                }

                sicet7::Serial::Console::Output("No Action Bound to this button.");

            }

            void Light::SetupDisplay(){
                Lcd::Get()->Display()->SetBackColor(LCD_COLOR_BLACK);
                Lcd::Get()->Display()->SetTextColor(LCD_COLOR_GREEN);
            }

            void Light::Button1(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{0,0},
                    Lcd::Size{120,68}
                );

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{1,1},
                    Lcd::Position{119,67},
                    "Main\nMenu",
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

                touchObj->triggerFunction = &Light::Button_Trigger;
                Light::AddTouchObject(touchObj);

                Light::AddDisplayObject("Light_Button1_Container",rectangle);
                Light::AddDisplayObject("Light_Button1_Text",text);
                Light::AddRelationship("Light_Button1_Container","Light_Button1_Text");
            }

        }
    }
}