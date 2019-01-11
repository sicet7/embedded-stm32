#include <classes/sicet7/Application/Application.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <mbed.h>
#include <LCD_DISCO_F746NG.h>
#include <classes/sicet7/Convert.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Lcd/Display/Display.h>
#include <structs/sicet7/Button/Button.h>
#include <time.h>

//A0 is used for Temperature Sensor

namespace sicet7{
    
    InterruptIn onBoardButton(USER_BUTTON);
    DigitalOut onBoardLed(LED1);
    AnalogIn onBoardAnalogZero(A0);
    AnalogIn onBoardAnalogOne(A1);
    AnalogIn onBoardAnaligTwo(A2);

    Application* Application::instance = 0;
    uint16_t state = 0;

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/11/2019
     * 
     * @constructor
     * 
     * @private
     * 
     * @return Application
     */
    Application::Application(){}

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/11/2019
     * 
     * @global
     * 
     * @return void
     */
    void OnBoardButtonRise(){
    
        if(sicet7::Application::GetInstance()->GetPressInProgress(0) == true || sicet7::Application::GetInstance()->IsSetupComplete() != true) return;

        sicet7::Application::GetInstance()->SetPressInProgress(0,true);

        sicet7::Serial::Console::Output("On Board Button Has been pressed!");

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
    void OnBoardButtonFall(){

        if(sicet7::Application::GetInstance()->GetPressInProgress(0) != true || sicet7::Application::GetInstance()->IsSetupComplete() != true) return;

        sicet7::Application::GetInstance()->SetPressInProgress(0,false);

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
    void TouchButtonPushed(Button but){

        //sicet7::Serial::Console::Output(Convert::ToCharArray16(but.id));

        if(but.state == Up){
            sicet7::Serial::Console::Output("Button Released!");
            onBoardLed = 0;
        }else{
            sicet7::Serial::Console::Output("Button Pushed!");
            onBoardLed = 1;
        }

        if(
            (but.id == 1 || but.id == 2 || but.id == 3 || but.id == 4) &&
                Application::GetInstance()->textState != but.id
            ){
            Application::GetInstance()->textState = but.id;
            Application::GetInstance()->ShouldClearDisplay(true);
        }

        sicet7::Serial::Console::Output("");

    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * @static
     * 
     * @return Application&
     */
    Application* Application::GetInstance(){
        if(instance == 0){
            instance = new Application();
        }
        return instance;
    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @private
     * 
     * @return int
     */
    int Application::Setup(){

        sicet7::Serial::Console::Output("Running setup (setup)");

        //bind functions to button press.
        sicet7::Serial::Console::Output("Mapping Buttons (setup)");
        sicet7::onBoardButton.rise(&sicet7::OnBoardButtonRise);
        sicet7::onBoardButton.fall(&sicet7::OnBoardButtonFall);

        //set default value's in boolean array
        sicet7::Serial::Console::Output("Defining progress defaults (setup)");
        for(int i = 0; i < sizeof(Application::pressInProgress); i++){
            Application::pressInProgress[i] = false;
        }

        //instantiate display object.
        sicet7::Serial::Console::Output("Booting Display (setup)");
        Application::displayObj = sicet7::Lcd::Display();

        sicet7::Serial::Console::Output("Enabling Touch (setup)");
        Application::displayObj.EnableTouch();

        sicet7::Serial::Console::Output("Configuring display defaults (setup)");
        Application::menuState = 1;
        Application::textState = 1;
        Application::backgroundColor = LCD_COLOR_BLACK;
        Application::textColor = LCD_COLOR_GREEN;
        Application::clearColor = LCD_COLOR_BLACK;

        //register setup completion.
        Application::setupComplete = true;
        sicet7::Serial::Console::Output("Setup Completed (setup)");

        return 0;
    }
    
    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @private
     * 
     * @return int
     */
    int Application::Loop(){
        
        if(Application::doClearDisplay == true){
            Application::ClearDisplay();
        }
        Application::RenderMenu();
        Application::RenderText();

        Application::hasBeenCleared = false;

        if(Application::displayObj.IsTouchEnabled() == true){
            Application::displayObj.RunTouch();
        }

        return 0;

    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @private
     * 
     * @return int
     */
    int Application::CleanUp(){
        sicet7::Serial::Console::Output("Testing cleanup");
        Application::cleanUpComplete = true;
        return 0;
    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * 
     * @return void
     */
    void Application::RenderMenu(){
        
        if(
            Application::menuStateDisplayed != Application::menuState || 
            Application::menuStateDisplayed == 0 ||
            Application::hasBeenCleared == true
        ){

            if(Application::menuState == 1){
                Application::displayObj.SetBackgroundColor(Application::backgroundColor);
                Application::displayObj.SetTextColor(Application::textColor);

                Button button1;
                button1.color = LCD_COLOR_BLACK;
                button1.id = 1;
                button1.filled = false;
                button1.text = "testing";//this doesn't work yet... ::TODO::
                button1.textColor = LCD_COLOR_GREEN;
                button1.SetRows(4);
                button1.SetColumns(4);
                button1.SetPosition(1);
                button1.click = &TouchButtonPushed;

                Button button2;
                button2 = button1;
                button2.id = 2;
                button2.SetPosition(2);

                Button button3;
                button3 = button1;
                button3.id = 3;
                button3.SetPosition(3);

                Button button4;
                button4 = button1;
                button4.id = 4;
                button4.SetPosition(4);

                Application::displayObj.AddButton(button1);
                Application::displayObj.AddButton(button2);
                Application::displayObj.AddButton(button3);
                Application::displayObj.AddButton(button4);

                Application::displayObj.DrawButtons();
                Application::menuStateDisplayed = 1;
                return;
            }

            sicet7::Serial::Console::Output("Invalid Menu State! Resetting to \"1\"");
            Application::menuState = 1;
            Application::menuStateDisplayed = 0;
            Application::displayObj.Clear(Application::clearColor);
            Application::hasBeenCleared = true;

        }

    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * 
     * @return void
     */
    void Application::RenderText(){
        
        char* outputString;
        
        static uint32_t lastUpdated;

        time_t timer;
        uint32_t seconds;

        time(&timer);

        seconds = (uint32_t)timer;

        if(Application::textState == 1){

            float temperature;
            const int B = 4275;               // B value of the thermistor
            const int R0 = 100000;            // R0 = 100k

            float R = 1.0f/onBoardAnalogZero.read() - 1.0f;
            R = R0*R;

            temperature = 1.0/(log(R/100000)/B+1/298.15)-273.15;
            char buffer[20];
            sprintf(buffer,"%f C",temperature);
            outputString = buffer;
        }

        if(Application::textState == 2){
            uint16_t sensorValue = (uint16_t)onBoardAnalogOne.read_u16();
            char buffer[20];
            sprintf(buffer,"%u",sensorValue);
            outputString = buffer;
        }

        if(Application::textState == 3){

            float values[1000] = {};
            float sum = 0.0f;
            float average = 0.0f;
            float decibel = 0.0f;

            //read sensor output 1000 times
            for(int i = 0; i < 1000; i++){
                values[i] = (onBoardAnaligTwo.read()*(3.3f));
            }

            //calculates sum of values.
            for(int u = 0; u < 1000; u++){
                sum += values[u];
            }

            average = sum/1000;
            decibel = (average * 29);

            char buffer[20];
            sprintf(buffer,"%f dB",decibel);

            outputString = buffer;
        }

        if(Application::textState == 4){
            outputString = "testing4";
        }

        if(
            Application::textState != Application::textStateDisplayed ||
            (seconds-lastUpdated) >= 1
        ){
            Application::displayObj.SetBackgroundColor(Application::backgroundColor);
            Application::displayObj.SetTextColor(Application::textColor);
            Application::displayObj.ClearStringLine(5);
            Application::displayObj.RenderTextAt(0,LINE(5),outputString,CENTER_MODE);
            Application::textStateDisplayed = Application::textState;
            lastUpdated = seconds;
        }

    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * 
     * @return bool
     */
    bool Application::IsSetupComplete(){
        return Application::setupComplete;
    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * 
     * @return bool
     */
    bool Application::IsCleanUpComplete(){
        return Application::cleanUpComplete;
    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * 
     * @param int id
     * 
     * @return bool
     */
    bool Application::GetPressInProgress(int id){
        return Application::pressInProgress[id];
    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * 
     * @param int id
     * @param bool value
     * 
     * @return void
     */
    void Application::SetPressInProgress(int id, bool value){
        Application::pressInProgress[id] = value;
    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * 
     * @return void
     */
    void Application::Stop(){
        Application::running = false;
    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/10/2019
     * 
     * @public
     * 
     * @return int
     */
    int Application::Run(){

        int returnCode = 0;

        Application::running = true;

        returnCode = Application::Setup();
        if(returnCode != 0){
            sicet7::Serial::Console::Output("Setup Failed!");
        }

        while(Application::running == true && returnCode == 0){
            returnCode = Application::Loop();
        }

        if(returnCode != 0){
            sicet7::Serial::Console::Output("Loop Failed!");
            return returnCode;
        }

        returnCode = Application::CleanUp();

        if(returnCode != 0){
            sicet7::Serial::Console::Output("CleanUp Failed!");
        }

        return returnCode;

    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/11/2019
     * 
     * @public
     * 
     * @return void
     */
    void Application::ClearDisplay(){
        Application::displayObj.Clear(Application::clearColor);
        Application::hasBeenCleared = true;
        Application::doClearDisplay = false;
    }

    /**
     * @file Application.cpp
     * @auther Martin René Sørensen <martin@randomphp.com>
     * @date 1/11/2019
     * 
     * @public
     * 
     * @return void
     */
    void Application::ShouldClearDisplay(bool val){
        Application::doClearDisplay = true;
    }

}