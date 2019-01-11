#include <classes/sicet7/Lcd/Display/Display.h>
#include <structs/sicet7/Button/Button.h>
#include <structs/sicet7/Area/Area.h>
#include <structs/sicet7/Position/Position.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <classes/sicet7/Convert.h>
#include <TS_DISCO_F746NG.h>
#include <math.h>
#include <algorithm>

namespace sicet7{
    namespace Lcd{

        LCD_DISCO_F746NG screen;
        TS_DISCO_F746NG touch;

        Display::Display(){}

        uint32_t Display::GetBackgroundColor(){
            return sicet7::Lcd::screen.GetBackColor();
        }

        void Display::SetBackgroundColor(uint32_t color){
            sicet7::Lcd::screen.SetBackColor(color);
        }

        uint32_t Display::GetTextColor(){
            return sicet7::Lcd::screen.GetTextColor();
        }

        void Display::SetTextColor(uint32_t color){
            sicet7::Lcd::screen.SetTextColor(color);
        }

        void Display::ClearStringLine(uint32_t line){
            sicet7::Lcd::screen.ClearStringLine(line);
        }

        bool Display::EnableTouch(){
            uint8_t status;
            status = sicet7::Lcd::touch.Init(sicet7::Lcd::screen.GetXSize(),sicet7::Lcd::screen.GetYSize());
            Display::touchEnabled = (status == TS_OK);
            return Display::touchEnabled;
        }

        bool Display::IsTouchEnabled(){
            return Display::touchEnabled;
        }

        void Display::RunTouch(){

            if(!Display::touchEnabled) return;

            TS_StateTypeDef TS_State;
            sicet7::Lcd::touch.GetState(&TS_State);

            if(TS_State.touchDetected != Display::lastIterationTouches){
                Display::ProcessTouchPosition();
                Display::lastIterationTouches = TS_State.touchDetected;

            }

        }

        void Display::AddButton(Button but){
            Display::buttons.push_back(but);
        }

        void Display::ClearButtons(){
            if(Display::buttons.size() >= 1){
                Display::buttons.clear();
            }
        }

        void Display::RenderTextAt(uint16_t xPos,u_int16_t yPos, char* text, Text_AlignModeTypdef mode){
            sicet7::Lcd::screen.DisplayStringAt(xPos,yPos,((uint8_t *)text),mode);
        }

        void Display::DrawButtons(){

            for(std::vector<sicet7::Button>::iterator butPointer = Display::buttons.begin(); butPointer != Display::buttons.end(); ++butPointer){

                uint16_t lcdMaxWidth = sicet7::Convert::ToUInt16(sicet7::Lcd::screen.GetXSize());
                uint16_t lcdMaxHeight = sicet7::Convert::ToUInt16(sicet7::Lcd::screen.GetYSize());

                /** @var b.pos Area */
                /** @var b.pos.pos1 Position */
                Area buttonArea = sicet7::Lcd::Display::GetButtonArea((*butPointer));

                uint16_t buttonWidth;
                uint16_t buttonHeight;

                bool isLeftSideButton = (buttonArea.pos1.x >= 1);
                bool isTopButton = (buttonArea.pos1.y >= 1);

                //TODO: Make fixes to box sizes!!

                //buttonWidth = (!isLeftSideButton ? (buttonArea.pos2.x-(buttonArea.pos1.x-1)) : (buttonArea.pos2.x-buttonArea.pos1.x));
                buttonWidth = buttonArea.pos2.x-buttonArea.pos1.x;
                /*if(!isLeftSideButton && ((buttonArea.pos1.x-1)+buttonWidth) >= lcdMaxWidth){
                    buttonWidth = lcdMaxWidth-(buttonArea.pos1.x-1);
                }*/

                //buttonHeight = (!isTopButton ? (buttonArea.pos2.y-(buttonArea.pos1.y-1)) : (buttonArea.pos2.y-buttonArea.pos1.y));
                buttonHeight = buttonArea.pos2.y-buttonArea.pos1.y;


                /*if(!isTopButton && ((buttonArea.pos1.y-1)+buttonHeight) >= lcdMaxHeight){
                    buttonHeight = lcdMaxHeight-(buttonArea.pos1.y-1);
                }*/

                uint32_t oldBackColor = sicet7::Lcd::screen.GetBackColor();
                uint32_t oldTextColor = sicet7::Lcd::screen.GetTextColor();

                sicet7::Lcd::screen.SetTextColor((*butPointer).textColor);
                sicet7::Lcd::screen.SetBackColor((*butPointer).color);
                if((*butPointer).filled){
                    sicet7::Lcd::screen.FillRect(buttonArea.pos1.x,buttonArea.pos1.y,buttonWidth,buttonHeight);
                }else{
                    sicet7::Lcd::screen.DrawRect(buttonArea.pos1.x,buttonArea.pos1.y,buttonWidth,buttonHeight);
                }

                sicet7::Lcd::screen.SetTextColor(oldTextColor);
                sicet7::Lcd::screen.SetBackColor(oldBackColor);

            }

            //b.
            //sicet7::Lcd::lcdScreen.
        }

        Area Display::GetButtonArea(Button bp){

            Area buttonArea;

            bool isFlipped = sicet7::Lcd::Display::flipped;

            Position pos1;
            Position pos2;

            uint16_t lcdMaxWidth = sicet7::Convert::ToUInt16(sicet7::Lcd::screen.GetXSize());
            uint16_t lcdMaxHeight = sicet7::Convert::ToUInt16(sicet7::Lcd::screen.GetYSize());

            uint16_t lcdMinHeight = 0;
            uint16_t lcdMinWidth = 0;

            uint16_t buttonWidth = sicet7::Convert::ToUInt16(std::floor((lcdMaxWidth/bp.GetColumns())));
            uint16_t buttonHeight = sicet7::Convert::ToUInt16(std::floor((lcdMaxHeight/bp.GetRows())));
            
            uint16_t positionInt = bp.GetPosition();

            uint16_t divLeftOver = ((uint16_t)positionInt%bp.GetColumns());

            uint16_t columnNumber = (divLeftOver == 0 ? bp.GetColumns() : divLeftOver);
            uint16_t rowNumber = ((positionInt-1) == 0 ? 0 : ((uint16_t)std::floor(((positionInt-1)/bp.GetRows()))))+1;

            pos1.x = buttonWidth*(columnNumber-1);
            pos2.x = buttonWidth*columnNumber;
            pos1.y = buttonHeight*(rowNumber-1);
            pos2.y = buttonHeight*rowNumber;

            pos1.x = (pos1.x != 0 ? pos1.x+1 : pos1.x);//if not first column, Then add column offset.
            pos1.y = (pos1.y != 0 ? pos1.y+1 : pos1.y);//if not first row, then add row offset.

            buttonArea.pos1 = pos1;
            buttonArea.pos2 = pos2;

            return buttonArea;

        }

        void Display::Clear(uint32_t color){
            sicet7::Lcd::screen.Clear(color);
            //Display::ClearButtons();
        }

        void Display::ProcessTouchPosition(){

            TS_StateTypeDef TS_State;
            sicet7::Lcd::touch.GetState(&TS_State);

            uint16_t* xPos = TS_State.touchX;
            uint16_t* yPos = TS_State.touchY;

            for(std::vector<sicet7::Button>::iterator itera = Display::buttons.begin(); itera != Display::buttons.end(); ++itera){

                Button & but = *itera;

                Area currentArea = Display::GetButtonArea(but);

                bool isBeingTouched = false;

                if(TS_State.touchDetected >= 1){
                    for(int j = 0; j < TS_State.touchDetected; j++){

                        uint16_t xPosition = xPos[j];
                        uint16_t yPosition = yPos[j];

                        if(
                            xPosition >= currentArea.pos1.x && xPosition <= currentArea.pos2.x &&
                            yPosition >= currentArea.pos1.y && yPosition <= currentArea.pos2.y
                        ){
                            isBeingTouched = true;
                        }

                    }
                }

                TouchState newState;

                if(isBeingTouched == true){
                    newState = Down;
                }else{
                    newState = Up;
                }

                if(newState != but.state){
                    but.SetState(newState);
                    if(but.click != 0){
                        but.click(but);
                    }
                }

                
            }

        }

    }
}