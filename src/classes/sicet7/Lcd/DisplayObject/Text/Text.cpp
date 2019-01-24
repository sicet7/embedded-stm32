/**
 * @file Text.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief This is the implementation of the Lcd::Text object.
 * @version 0.1
 * @date 2019-01-23
 */
#include <classes/sicet7/Lcd/Lcd.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <math.h>
namespace sicet7{

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::text = text;
        Lcd::Text::mode = LEFT_MODE;
        Lcd::Text::font = &Font16;
        Lcd::Text::bottomRight = pos2;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     * @param pFont 
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text, sFONT* pFont){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::text = text;
        Lcd::Text::mode = LEFT_MODE;
        Lcd::Text::font = pFont;
        Lcd::Text::bottomRight = pos2;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     * @param pFont 
     * @param pMode 
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text, sFONT* pFont, Text_AlignModeTypdef pMode){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::text = text;
        Lcd::Text::mode = pMode;
        Lcd::Text::font = pFont;
        Lcd::Text::bottomRight = pos2;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     * @param pFont 
     * @param pMode 
     * @param lineSpace
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text, sFONT* pFont, Text_AlignModeTypdef pMode, uint16_t lineSpace){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::text = text;
        Lcd::Text::mode = pMode;
        Lcd::Text::font = pFont;
        Lcd::Text::bottomRight = pos2;
        Lcd::Text::lineSpacing = lineSpace;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     * @param pFont 
     * @param pMode 
     * @param lineSpace
     * @param topPadd
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text, sFONT* pFont, Text_AlignModeTypdef pMode, uint16_t lineSpace, uint16_t topPadd){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::text = text;
        Lcd::Text::mode = pMode;
        Lcd::Text::font = pFont;
        Lcd::Text::bottomRight = pos2;
        Lcd::Text::lineSpacing = lineSpace;
        Lcd::Text::topPadding = topPadd;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, std::string text){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::textString = text;
        Lcd::Text::mode = LEFT_MODE;
        Lcd::Text::font = &Font16;
        Lcd::Text::bottomRight = pos2;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     * @param pFont 
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, std::string text, sFONT* pFont){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::textString = text;
        Lcd::Text::mode = LEFT_MODE;
        Lcd::Text::font = pFont;
        Lcd::Text::bottomRight = pos2;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     * @param pFont 
     * @param pMode 
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, std::string text, sFONT* pFont, Text_AlignModeTypdef pMode){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::textString = text;
        Lcd::Text::mode = pMode;
        Lcd::Text::font = pFont;
        Lcd::Text::bottomRight = pos2;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     * @param pFont 
     * @param pMode 
     * @param lineSpace
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, std::string text, sFONT* pFont, Text_AlignModeTypdef pMode, uint16_t lineSpace){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::textString = text;
        Lcd::Text::mode = pMode;
        Lcd::Text::font = pFont;
        Lcd::Text::bottomRight = pos2;
        Lcd::Text::lineSpacing = lineSpace;
    }

    /**
     * @brief Construct a new Lcd::Text object
     * 
     * @param pos 
     * @param text 
     * @param pFont 
     * @param pMode 
     * @param lineSpace
     * @param topPadd
     */
    Lcd::Text::Text(Lcd::Position pos, Lcd::Position pos2, std::string text, sFONT* pFont, Text_AlignModeTypdef pMode, uint16_t lineSpace, uint16_t topPadd){
        Lcd::Text::initialPosition = pos;
        Lcd::Text::textString = text;
        Lcd::Text::mode = pMode;
        Lcd::Text::font = pFont;
        Lcd::Text::bottomRight = pos2;
        Lcd::Text::lineSpacing = lineSpace;
        Lcd::Text::topPadding = topPadd;
    }

    uint32_t Lcd::Text::GetMaxCharsPerLine(){
        return ((uint32_t)(std::floor((Lcd::Text::GetTextAreaWidth()/Lcd::Text::font->Width))));
    }

    uint32_t Lcd::Text::GetTextAreaWidth(){
        return ((uint32_t)(Lcd::Text::bottomRight.x)-(Lcd::Text::initialPosition.x));
    }

    uint32_t Lcd::Text::GetTextAreaHeight(){
        return ((uint32_t)(Lcd::Text::bottomRight.y)-(Lcd::Text::initialPosition.y));
    }

    vector<std::string> Lcd::Text::SplitText(){

        std::string readString;

        if(Lcd::Text::text == 0){
            readString = Lcd::Text::textString;
        }else{
            readString = Lcd::Text::text->value;
        }

        vector<std::string> stringVector;
        std::stringstream ss(readString);
        std::string token;
        while(std::getline(ss,token,'\n')){

            if(token.length() > Lcd::Text::GetMaxCharsPerLine()){
                stringVector.push_back(token.substr(0,Lcd::Text::GetMaxCharsPerLine()));
            }else{
                stringVector.push_back(token);
            }
        
        }

        return stringVector;

    }

    void Lcd::Text::CustomDraw(LCD_DISCO_F746NG* lcd){
        if(Lcd::Text::isDisplayed != true){

            sFONT* oldPointer = lcd->GetFont();
            lcd->SetFont(Lcd::Text::font);

            vector<std::string> strings = Lcd::Text::SplitText();

            uint16_t lines = 1;

            for(vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it){

                uint16_t InitialXPosition = Lcd::Text::initialPosition.x;
                uint16_t InitialYPosition = Lcd::Text::initialPosition.y;

                if(Lcd::Text::topPadding > 0){
                    InitialYPosition += Lcd::Text::topPadding-1;
                }

                InitialYPosition += (Lcd::Text::font->Height*(lines-1))+(lines > 1 ? Lcd::Text::lineSpacing : 0);

                if(InitialYPosition + Lcd::Text::font->Height > Lcd::Text::bottomRight.y){
                    break;
                }

                switch(Lcd::Text::mode){
                    case CENTER_MODE:
                        InitialXPosition += (uint16_t)std::floor(((Lcd::Text::GetTextAreaWidth()-(Lcd::Text::font->Width*(it->length())))/2));
                    break;
                    case RIGHT_MODE:
                        InitialXPosition += (uint16_t)(Lcd::Text::GetTextAreaWidth()-(Lcd::Text::font->Width*it->length()));
                    break;
                    default:
                        InitialXPosition = InitialXPosition;
                    break;
                }

                lcd->DisplayStringAt(
                    InitialXPosition,
                    InitialYPosition,
                    ((uint8_t*)it->c_str()),
                    LEFT_MODE
                );

                lines++;
            }

            lcd->SetFont(oldPointer);

        }
    }

    void Lcd::Text::CustomClear(LCD_DISCO_F746NG* lcd){
        uint32_t oldTextColor = lcd->GetTextColor();
        lcd->SetTextColor(lcd->GetBackColor());
        lcd->FillRect(
            Lcd::Text::initialPosition.x,
            Lcd::Text::initialPosition.y,
            (uint32_t)Lcd::Text::GetTextAreaWidth(),
            (uint32_t)Lcd::Text::GetTextAreaHeight()
        );
        lcd->SetTextColor(oldTextColor);
    }

}