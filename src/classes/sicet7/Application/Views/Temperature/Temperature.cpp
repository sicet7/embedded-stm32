#include <classes/sicet7/Application/Views/Temperature/Temperature.h>
#include <classes/sicet7/Sensors/Temperature/Temperature.h>
#include <classes/sicet7/Application/Views/MainMenu/MainMenu.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Application/Threads/TemperatureThread/TemperatureThread.h>
namespace sicet7{
    namespace Application{
        namespace Views{
            
            Temperature* Temperature::instance = 0;

            rtos::Mutex* Temperature::instanceLock = new rtos::Mutex("TemperatureInstanceLock");

            void Temperature::CustomActivate(){
                osStatus err = sicet7::Application::Threads::TemperatureThread::Start();
                if(err){
                    sicet7::Serial::Console::Output("Failed to start TemperatureThread.");
                }
            }
            void Temperature::CustomDeactivate(){
                sicet7::Application::Threads::TemperatureThread::Pause();
            }
            void Temperature::CustomUpdate(){
                if(Temperature::temp != 0){
                    char buffer[30];
                    float temperature;
                    char* format = "%f C";
                    switch(Temperature::temperatureFormat){
                        case 1:
                            temperature = sicet7::Sensors::Temperature::Get()->Fahrenheit();
                            format = "%f F";
                        break;
                        case 2:
                            temperature = sicet7::Sensors::Temperature::Get()->Kelvin();
                            format = "%f K";
                        break;
                        default:
                            temperature = sicet7::Sensors::Temperature::Get()->Celsius();
                        break;
                    }
                    sprintf(buffer,(const char*)format,temperature);
                    Temperature::temp->Update(buffer);
                }
            }

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
                sicet7::Sensors::Temperature::Set(A0,4250,100000);
                Temperature::SetupDisplay();
                Temperature::Button1();
                Temperature::Button2();
                Temperature::Button3();
                Temperature::Button4();
                Temperature::MainText();
            }

            void Temperature::SetupDisplay(){
                Lcd::Get()->Display()->SetBackColor(LCD_COLOR_BLACK);
                Lcd::Get()->Display()->SetTextColor(LCD_COLOR_GREEN);
            }

            void Temperature::Button_Trigger(Lcd::TouchObject* obj){

                if(obj->GetName() == "Button1"){
                    if(obj->IsPress() == false){
                        Lcd::Get()->ActivateView(
                            sicet7::Application::Views::MainMenu::GetInstance()
                        );
                    }
                    return;
                }

                if(obj->GetName() == "Button2"){
                    if(obj->IsPress() == false){
                        sicet7::Application::Views::Temperature::GetInstance()->temperatureFormat = 0;
                    }
                    return;
                }

                if(obj->GetName() == "Button3"){
                    if(obj->IsPress() == false){
                        sicet7::Application::Views::Temperature::GetInstance()->temperatureFormat = 1;
                    }
                    return;
                }

                if(obj->GetName() == "Button4"){
                    if(obj->IsPress() == false){
                        sicet7::Application::Views::Temperature::GetInstance()->temperatureFormat = 2;
                    }
                    return;
                }

                sicet7::Serial::Console::Output("No Action Bound to this button.");

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

            void Temperature::Button2(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{120,0},
                    Lcd::Size{120,68}
                );

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{121,1},
                    Lcd::Position{239,67},
                    "Celsius",
                    &Font16,
                    CENTER_MODE,
                    0,
                    28
                );

                Lcd::TouchObject* touchObj = new Lcd::TouchObject(
                    "Button2",
                    Lcd::Position{121,1},
                    Lcd::Position{239,67}
                );

                touchObj->triggerFunction = &Temperature::Button_Trigger;
                Temperature::AddTouchObject(touchObj);

                Temperature::AddDisplayObject("Temperature_Button2_Container",rectangle);
                Temperature::AddDisplayObject("Temperature_Button2_Text",text);
                Temperature::AddRelationship("Temperature_Button2_Container","Temperature_Button2_Text");
            }

            void Temperature::Button3(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{240,0},
                    Lcd::Size{120,68}
                );

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{241,1},
                    Lcd::Position{359,67},
                    "Fahrenheit",
                    &Font16,
                    CENTER_MODE,
                    0,
                    28
                );

                Lcd::TouchObject* touchObj = new Lcd::TouchObject(
                    "Button3",
                    Lcd::Position{241,1},
                    Lcd::Position{359,67}
                );

                touchObj->triggerFunction = &Temperature::Button_Trigger;
                Temperature::AddTouchObject(touchObj);

                Temperature::AddDisplayObject("Temperature_Button3_Container",rectangle);
                Temperature::AddDisplayObject("Temperature_Button3_Text",text);
                Temperature::AddRelationship("Temperature_Button3_Container","Temperature_Button3_Text");
            }

            void Temperature::Button4(){
                Lcd::Rectangle* rectangle = new Lcd::Rectangle(
                    Lcd::Position{360,0},
                    Lcd::Size{119,68}
                );

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{361,1},
                    Lcd::Position{478,67},
                    "Kelvin",
                    &Font16,
                    CENTER_MODE,
                    0,
                    28
                );

                Lcd::TouchObject* touchObj = new Lcd::TouchObject(
                    "Button4",
                    Lcd::Position{361,1},
                    Lcd::Position{478,67}
                );

                touchObj->triggerFunction = &Temperature::Button_Trigger;
                Temperature::AddTouchObject(touchObj);

                Temperature::AddDisplayObject("Temperature_Button4_Container",rectangle);
                Temperature::AddDisplayObject("Temperature_Button4_Text",text);
                Temperature::AddRelationship("Temperature_Button4_Container","Temperature_Button4_Text");
            }

            //Width: 480
            //Height: 272
            void Temperature::MainText(){

                Temperature::temp = new Lcd::UpdatableOutput{"Loading..."};

                Lcd::Text* text = new Lcd::Text(
                    Lcd::Position{0,69},
                    Lcd::Position{478,271},
                    Temperature::temp,
                    &Font24,
                    CENTER_MODE,
                    0,
                    100
                );

                text->SetUpdateInterval(500);

                Temperature::AddDisplayObject("Temperature_MainText",text);

            }

        }
    }
}