/*#include <iostream>
#include <math.h>
#include <mbed.h>
#include <LCD_DISCO_F746NG.h>
#include <classes/sicet7/Convert.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Lcd/Display/Display.h>
#include <structs/sicet7/Button/Button.h>
*/
#include <classes/sicet7/Application/Application.h>
/*
bool displayed = false;
bool pip = false;

void buttonRise(){
  
  if(pip) return;

  pip = true;
  sicet7::Serial::Console::Output("the output is still working.");
  displayed = false;

}

void buttonFall(){
  if(!pip) return;
  pip = false;
}
*/
int main()
{   
  
  return sicet7::Application::GetInstance()->Run();
  /*
    DigitalOut led1(LED1);
    InterruptIn onBoardButton(USER_BUTTON);
    LCD_DISCO_F746NG lcd;
    onBoardButton.rise(&buttonRise);
    onBoardButton.fall(&buttonFall);

    using sicet7::Convert;
    using sicet7::Serial::Console;
    using sicet7::Button;
    using sicet7::Lcd::Display;
    led1 = 1;

    sicet7::Lcd::Display myDisplay = sicet7::Lcd::Display();
  
    while(1)
    {

      uint32_t val = lcd.GetXSize();
      uint32_t val2 = lcd.GetYSize();

      const char* outVal = Convert::ToCharArray32(val);      
      const char* outVal2 = Convert::ToCharArray32(val2);

      if(!displayed){
        lcd.Clear(LCD_COLOR_GREEN);
        lcd.SetBackColor(LCD_COLOR_GREEN);
        //Console::Output(outVal);
        //Console::Output(outVal2);

        uint16_t rows = 3;
        uint16_t columns = 3;

        /*for(uint16_t i = 1; i <= (rows*columns); i++){
            sicet7::Button myButton;
            myButton.SetRows(rows);
            myButton.SetColumns(columns);
            myButton.SetPosition(i);
            myButton.filled = true;
            myButton.color = LCD_COLOR_BLACK;
            myButton.text = "testing123";
            myButton.textColor = LCD_COLOR_WHITE;
            myDisplay.DrawButton(myButton);
        }
        lcd.SetTextColor(LCD_COLOR_CYAN);
        lcd.DisplayStringAt(0, 0, (uint8_t *)outVal, LEFT_MODE);
        lcd.DisplayStringAt(0, LINE(2), (uint8_t *)outVal2, LEFT_MODE);
        lcd.SetTextColor(LCD_COLOR_BLUE);
        lcd.DrawRect(0, 0, 120, 18);
        lcd.DrawRect(360,0,120,18);
        displayed = true;
      }

      wait(1);

      led1 = !led1;
    }*/
}