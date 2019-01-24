/**
 * @file Rectangle.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief Implemetation of Lcd::Rectangle
 * @version 0.1
 * @date 2019-01-23 
 */
#include <classes/sicet7/Lcd/Lcd.h>
#include <mbed.h>
namespace sicet7{
    
    /**
     * @brief Construct a new Lcd::Rectangle object
     * 
     * @param topLeft 
     * @param initialSize 
     */
    Lcd::Rectangle::Rectangle(sicet7::Lcd::Position topLeft, sicet7::Lcd::Size initialSize){
        Lcd::Rectangle::initialPosition = topLeft;
        Lcd::Rectangle::size = initialSize;
        Lcd::Rectangle::filled = false;
    }

    /**
     * @brief Construct a new Lcd::Rectangle object
     * 
     * @param topLeft 
     * @param initialSize 
     * @param nFilled 
     */
    Lcd::Rectangle::Rectangle(sicet7::Lcd::Position topLeft, sicet7::Lcd::Size initialSize, bool nFilled){
        Lcd::Rectangle::initialPosition = topLeft;
        Lcd::Rectangle::size = initialSize;
        Lcd::Rectangle::filled = nFilled;
    }

    /**
     * @brief Implementation of Lcd::DisplayObject::CustomDraw
     * 
     * @param lcd 
     */
    void Lcd::Rectangle::CustomDraw(LCD_DISCO_F746NG* lcd) {
        if(Lcd::Rectangle::isDisplayed != true){
            if(Lcd::Rectangle::filled == true){
                lcd->FillRect(
                    Lcd::Rectangle::initialPosition.x,
                    Lcd::Rectangle::initialPosition.y,
                    Lcd::Rectangle::size.width,
                    Lcd::Rectangle::size.height
                );
            }else{
                lcd->DrawRect(
                    Lcd::Rectangle::initialPosition.x,
                    Lcd::Rectangle::initialPosition.y,
                    Lcd::Rectangle::size.width,
                    Lcd::Rectangle::size.height
                );
            }
        }
    }

    /**
     * @brief Implementation of Lcd::DisplayObject::CustomClear
     * 
     * @param lcd 
     */
    void Lcd::Rectangle::CustomClear(LCD_DISCO_F746NG* lcd){
        static uint32_t oldTextColor;
        //static uint32_t oldBackGroundcolor;
        oldTextColor = lcd->GetTextColor();
        lcd->SetTextColor(lcd->GetBackColor());
        lcd->FillRect(
            Lcd::Rectangle::initialPosition.x,
            Lcd::Rectangle::initialPosition.y,
            Lcd::Rectangle::size.width+1,
            Lcd::Rectangle::size.height+1
        );
        lcd->SetTextColor(oldTextColor);
    }

}