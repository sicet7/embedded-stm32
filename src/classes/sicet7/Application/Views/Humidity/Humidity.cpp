#include <classes/sicet7/Application/Views/Humidity/Humidity.h>
#include <mbed.h>
#include <classes/sicet7/Application/Views/MainMenu/MainMenu.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    namespace Application{
        namespace Views{

            Humidity* Humidity::instance = 0;
            
            Lcd::UpdatableOutput* Humidity::output = 0;

            rtos::Mutex* Humidity::instanceLock = new rtos::Mutex("HumiditySensorViewInstanceLock");

            Humidity* Humidity::GetInstance(){

                Humidity::instanceLock->lock();
                if(Humidity::instance == 0){
                    Humidity::instance = new Humidity();
                }
                Humidity::instanceLock->unlock();
                return Humidity::instance;

            }

            Humidity::~Humidity(){}
            Humidity::Humidity(){
                Humidity::SetupDisplay();
                Humidity::Button1();
                Humidity::MainText();
            }

            void Humidity::CustomActivate(){}
            void Humidity::CustomDeactivate(){}
            void Humidity::CustomUpdate(){}

            void Humidity::Button_Trigger(Lcd::TouchObject* obj){

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

            void Humidity::SetupDisplay(){
                Lcd::Get()->Display()->SetBackColor(LCD_COLOR_BLACK);
                Lcd::Get()->Display()->SetTextColor(LCD_COLOR_GREEN);
            }

            void Humidity::Button1(){
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

                touchObj->triggerFunction = &Humidity::Button_Trigger;
                Humidity::AddTouchObject(touchObj);

                Humidity::AddDisplayObject("Humidity_Button1_Container",rectangle);
                Humidity::AddDisplayObject("Humidity_Button1_Text",text);
                Humidity::AddRelationship("Humidity_Button1_Container","Humidity_Button1_Text");
            }

            void Humidity::MainText(){


                Humidity::output = new Lcd::UpdatableOutput{"Loading..."};

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{0,69},
                    Lcd::Position{478,271},
                    Humidity::output,
                    &Font24,
                    CENTER_MODE,
                    0,
                    100
                );

                text->SetUpdateInterval(500);

                Humidity::AddDisplayObject("Humidity_MainText",text);

            }

        }
    }
}