#include <classes/sicet7/Application/Main/Main.h>
#include <classes/sicet7/Application/Action/Action.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    namespace Application{

        bool Action::OnBoardButtonPressInProgress = false;

        /**
         * @file Actions.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/11/2019
         * 
         * @global
         * 
         * @return void
         */
        void Action::OnBoardButtonRise(){

            if(sicet7::Application::Action::OnBoardButtonPressInProgress == true || sicet7::Application::Main::GetInstance()->IsSetupComplete() != true) return;

            sicet7::Application::Action::OnBoardButtonPressInProgress = true;

            sicet7::Serial::Console::Output("On Board Button Has been pressed!");

        }

        /**
         * @file Actions.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/11/2019
         * 
         * @global
         * 
         * @return void
         */
        void Action::OnBoardButtonFall(){

            if(sicet7::Application::Action::OnBoardButtonPressInProgress != true || sicet7::Application::Main::GetInstance()->IsSetupComplete() != true) return;

            sicet7::Application::Action::OnBoardButtonPressInProgress = false;

        }

        /**
         * @file Application.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/11/2019
         * 
         * @global
         * 
         * @return void
         */
        void Action::TouchButtonPushed(Button but){

            //sicet7::Serial::Console::Output(Convert::ToCharArray16(but.id));

            /*if(but.state == Up){
                sicet7::Serial::Console::Output("Button Released!");
                sicet7::Application::Main::GetInstance()->onBoardLed->write(0);
            }else{
                sicet7::Serial::Console::Output("Button Pushed!");
                sicet7::Application::Main::GetInstance()->onBoardLed->write(1);
            }

            if(
                (but.id == 1 || but.id == 2 || but.id == 3 || but.id == 4) &&
                    sicet7::Application::Main::GetInstance()->textState != but.id
            ){
                sicet7::Application::Main::GetInstance()->textState = but.id;
                sicet7::Application::Main::GetInstance()->ShouldClearDisplay(true);
            }

            sicet7::Serial::Console::Output("");*/

        }
    }
}