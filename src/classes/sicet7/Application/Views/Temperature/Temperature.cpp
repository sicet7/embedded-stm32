#include <classes/sicet7/Application/Views/Temperature/Temperature.h>
#include <classes/sicet7/Application/Views/MainMenu/MainMenu.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    namespace Application{
        namespace Views{
            
            Temperature* Temperature::instance = 0;

            rtos::Mutex* Temperature::instanceLock = new rtos::Mutex("TemperatureInstanceLock");

            void Temperature::CustomActivate(){}
            void Temperature::CustomDeactivate(){}
            void Temperature::CustomUpdate(){}

            Temperature* Temperature::GetInstance(){
                Temperature::instanceLock->lock();
                if(Temperature::instance == 0){
                    Temperature::instance = new Temperature();
                }
                Temperature::instanceLock->unlock();
                return Temperature::instance;
            }

            Temperature::~Temperature(){
                delete Temperature::instance;
            }

            Temperature::Temperature(){
                Temperature::SetupDisplay();
                Temperature::Button1();
            }

            void Temperature::SetupDisplay(){
                Lcd::Get()->Display()->SetBackColor(LCD_COLOR_BLACK);
                Lcd::Get()->Display()->SetTextColor(LCD_COLOR_GREEN);
            }

            void Temperature::Button_Trigger(Lcd::TouchObject* obj){

                if(
                    obj->GetName() == "Button1" && 
                    obj->IsPress() == false
                ){
                    Lcd::Get()->ActivateView(
                        sicet7::Application::Views::MainMenu::GetInstance()
                    );
                }else{
                    sicet7::Serial::Console::Output("No Action Bound to this button.");
                }

            }

            void Temperature::Button1(){
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

                touchObj->triggerFunction = &Temperature::Button_Trigger;
                Temperature::AddTouchObject(touchObj);

                Temperature::AddDisplayObject("Temperature_Button1_Container",rectangle);
                Temperature::AddDisplayObject("Temperature_Button1_Text",text);
                Temperature::AddRelationship("Temperature_Button1_Container","Temperature_Button1_Text");
            }

        }
    }
}