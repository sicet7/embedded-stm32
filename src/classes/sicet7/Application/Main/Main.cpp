#include <classes/sicet7/Application/Main/Main.h>
#include <classes/sicet7/Application/Core/Core.h>
#include <classes/sicet7/Application/Action/Action.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <mbed.h>
#include <LCD_DISCO_F746NG.h>
#include <classes/sicet7/Convert.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Sensors/Temperature/Temperature.h>
#include <classes/sicet7/Lcd/Lcd.h>
#include <classes/sicet7/Application/Views/MainMenu/MainMenu.h>

//A0 is used for Temperature Sensor

namespace sicet7{
    namespace Application{

        /*InterruptIn Main::obb_ub(USER_BUTTON);
        DigitalOut Main::obl_l1(LED1);
        AnalogIn Main::bb_aia0(A0);
        AnalogIn Main::bb_aia1(A1);
        AnalogIn Main::bb_aia2(A2);*/

        Main* Main::instance = 0;
        Lcd::View* Main::activeView = 0;
        uint16_t state = 0;

        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/11/2019
         * 
         * @constructor
         * 
         * @private
         * 
         * @return Main
         */
        Main::Main(){//TODO: Move this to the Setup method.

            //static InterruptIn obb_ub(USER_BUTTON);
            static DigitalOut obl_l1(LED1);

            //create pointer to USER_BUTTON
            //Main::onBoardButton = &obb_ub;
            
            //create pointer to LED1
            Main::onBoardLed = &obl_l1;

        }

        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/10/2019
         * 
         * @public
         * @static
         * 
         * @return Main&
         */
        Main* Main::GetInstance(){
            if(instance == 0){
                instance = new Main();
            }
            return instance;
        }

        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/10/2019
         * 
         * @private
         * 
         * @return int
         */
        int Main::Setup(){

            //instantiate display object.
            sicet7::Serial::Console::Output("Booting Display (setup)");
            Main::activeView = sicet7::Application::Views::MainMenu::GetInstance();

            sicet7::Serial::Console::Output("Booting Temperature Sensor (setup)");
            sicet7::Sensors::Temperature::Set(A0,4250,100000);

            return 0;
        }

        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/10/2019
         * 
         * @private
         * 
         * @return int
         */
        int Main::Loop(){
            

            if(Main::activeView->IsActivated() != true){
                Lcd::Get()->ActivateView(Main::activeView);
            }else{
                Main::activeView->Update();
            }
            Main::onBoardLed->write((Main::onBoardLed->read() == 1 ? 0 : 1));
            ThisThread::sleep_for(1000);

            return 0;

        }

        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/10/2019
         * 
         * @private
         * 
         * @return int
         */
        int Main::CleanUp(){
            return 0;
        }

        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/10/2019
         * 
         * @public
         * 
         * @return bool
         */
        bool Main::IsSetupComplete(){
            return Main::setupComplete;
        }

        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/10/2019
         * 
         * @public
         * 
         * @return bool
         */
        bool Main::IsCleanUpComplete(){
            return Main::cleanUpComplete;
        }


        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/10/2019
         * 
         * @public
         * 
         * @return void
         */
        void Main::Stop(){
            Main::running = false;
        }

        /**
         * @file Main.cpp
         * @auther Martin René Sørensen <martin@randomphp.com>
         * @date 1/10/2019
         * 
         * @public
         * 
         * @return int
         */
        int Main::Run(){

            int returnCode = 0;

            Main::running = true;

            sicet7::Serial::Console::Output("--- Device Information ---",true,false);
            sicet7::Application::Core::PrintDeviceInfo();
            sicet7::Serial::Console::Output("--------------------------",true,false);
            sicet7::Serial::Console::Output("",true,false);

            sicet7::Serial::Console::Output("--- Application Setup Starting ---",true,false);
            Main::setupComplete = false;
            returnCode = Main::Setup();
            if(returnCode != 0){
                sicet7::Serial::Console::Output("--- Application Setup Failed! ---",true,false);
                sicet7::Serial::Console::Output("Return code: ",false,false);
                char buffer[32];
                sprintf(buffer,"%d",returnCode);
                sicet7::Serial::Console::Output(buffer,true,false);
                return returnCode;
            }else{
                sicet7::Serial::Console::Output("--- Application Setup Finished ---",true,false);
                sicet7::Serial::Console::Output("",true,false);
                Main::setupComplete = true;
            }

            sicet7::Serial::Console::Output("--- Application Loop Starting ---");
            while(Main::running == true && returnCode == 0){
                returnCode = Main::Loop();
            }

            if(returnCode != 0){
                sicet7::Serial::Console::Output("--- Application Loop Failed! ---");
                sicet7::Serial::Console::Output("Return code: ",false,false);
                char buffer[32];
                sprintf(buffer,"%d",returnCode);
                sicet7::Serial::Console::Output(buffer,true,false);
                return returnCode;
            }else{
                sicet7::Serial::Console::Output("--- Application Loop Finished! ---");
                sicet7::Serial::Console::Output("",true,false);
            }

            sicet7::Serial::Console::Output("--- Application CleanUp Starting ---",true,false);
            cleanUpComplete = false;
            returnCode = Main::CleanUp();

            if(returnCode != 0){
                sicet7::Serial::Console::Output("--- Application CleanUp Failed! ---");
                sicet7::Serial::Console::Output("Return code: ",false,false);
                char buffer[32];
                sprintf(buffer,"%d",returnCode);
                sicet7::Serial::Console::Output(buffer,true,false);
                return returnCode;
            }else{
                sicet7::Serial::Console::Output("--- Application CleanUp Finished! ---");
                sicet7::Serial::Console::Output("",true,false);
                cleanUpComplete = true;
            }

            return returnCode;

        }

    }

}