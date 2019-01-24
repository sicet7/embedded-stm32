#include <classes/sicet7/Application/Views/Sound/Sound.h>
#include <mbed.h>
#include <classes/sicet7/Application/Views/MainMenu/MainMenu.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    namespace Application{
        namespace Views{
            
            Sound* Sound::instance = 0;
            
            rtos::Mutex* Sound::instanceLock = new rtos::Mutex("SoundSensorViewInstanceLock");

            Sound* Sound::GetInstance(){

                Sound::instanceLock->lock();
                if(Sound::instance == 0){
                    Sound::instance = new Sound();
                }
                Sound::instanceLock->unlock();
                return Sound::instance;

            }

            Sound::~Sound(){}
            Sound::Sound(){
                Sound::SetupDisplay();
                Sound::Button1();
            }

            void Sound::CustomActivate(){}
            void Sound::CustomDeactivate(){}
            void Sound::CustomUpdate(){}

            void Sound::Button_Trigger(Lcd::TouchObject* obj){

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

            void Sound::SetupDisplay(){
                Lcd::Get()->Display()->SetBackColor(LCD_COLOR_BLACK);
                Lcd::Get()->Display()->SetTextColor(LCD_COLOR_GREEN);
            }

            void Sound::Button1(){
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

                touchObj->triggerFunction = &Sound::Button_Trigger;
                Sound::AddTouchObject(touchObj);

                Sound::AddDisplayObject("Sound_Button1_Container",rectangle);
                Sound::AddDisplayObject("Sound_Button1_Text",text);
                Sound::AddRelationship("Sound_Button1_Container","Sound_Button1_Text");
            }

        }
    }
}