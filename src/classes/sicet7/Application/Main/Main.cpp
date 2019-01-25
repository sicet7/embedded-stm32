/**
 * @file Main.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Implements the Application::Main class.
 * @version 0.1
 * @date 2019-01-25
 * 
 */
#include <classes/sicet7/Application/Main/Main.h>
#include <classes/sicet7/Application/Core/Core.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <mbed.h>
#include <rtos.h>
#include <LCD_DISCO_F746NG.h>
#include <classes/sicet7/Convert.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Sensors/Temperature/Temperature.h>
#include <classes/sicet7/Lcd/Lcd.h>
#include <classes/sicet7/Application/Views/MainMenu/MainMenu.h>
#include <classes/sicet7/Application/Threads/TouchThread/TouchThread.h>

namespace sicet7{
    namespace Application{

        Main* Main::instance = 0;
        rtos::Mutex* Main::singletonLock = new rtos::Mutex("ApplicationMainSingletonLock");

        /**
         * @brief Construct a new Application::Main object
         * 
         */
        Main::Main(){

//            static DigitalOut obl_l1(LED1);

//            Main::onBoardLed = &obl_l1;

        }

        /**
         * @brief This method should be used to get a pointer to the current Application::Main instance.
         * 
         * @return Main* 
         */
        Main* Main::GetInstance(){
            Main::singletonLock->lock();
            if(Main::instance == 0){
                Main::instance = new Main();
            }
            Main::singletonLock->unlock();
            return Main::instance;
        }

        /**
         * @brief This Method is Part of the Run stack. This method is the Setup function in the Application, meaning that it is only run once.
         * 
         * @return int 
         */
        int Main::Setup(){

            osStatus err = sicet7::Application::Threads::TouchThread::Start();

            if(err){
                sicet7::Serial::Console::Output("Failed to Start TouchThread.");
            }else{
                sicet7::Serial::Console::Output("TouchThread Started.");
            }

            return 0;
        }

        /**
         * @brief This Method is a part of the Run Stack. This method is the main loop of the Application.
         * 
         * @return int 
         */
        int Main::Loop(){
            
            if(Lcd::Get()->CurrentView() == 0){//fallback view if no view has been activated.
                Lcd::Get()->ActivateView(sicet7::Application::Views::MainMenu::GetInstance());
            }else{
                Lcd::Get()->CurrentView()->Update();
                //Lcd::Get()->CurrentView()->ProcessTouch();
            }

            //Main::onBoardLed->write((Main::onBoardLed->read() == 1 ? 0 : 1));
            ThisThread::sleep_for(1);//This is to reduse screen flicker.

            return 0;

        }

        /**
         * @brief This method is part of the Run Stack. This method is used to Cleanup after the Main::Loop has finished.
         * 
         * @return int 
         */
        int Main::CleanUp(){
            sicet7::Application::Threads::TouchThread::Stop();
            return 0;
        }

        /**
         * @brief Returns a boolean value that represents whether or not the Setup method is finished running. 
         * 
         * @return true 
         * @return false 
         */
        bool Main::IsSetupComplete(){
            return Main::setupComplete;
        }

        /**
         * @brief Returns a boolean value that represents whether or not the CleanUp method is finished running.
         * 
         * @return true 
         * @return false 
         */
        bool Main::IsCleanUpComplete(){
            return Main::cleanUpComplete;
        }


        /**
         * @brief This method when called will break the Loop method.
         * 
         */
        void Main::Stop(){
            Main::running = false;
        }

        /**
         * @brief Implementation of the Run Stack.
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