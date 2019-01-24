/**
 * @file TouchObject.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief The Implementation of Lcd::TouchObject
 * @version 0.1
 * @date 2019-01-23 
 */
#include <classes/sicet7/Lcd/Lcd.h>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    
    /**
     * @brief Construct a new Lcd::TouchObject instance.
     * 
     * @param pName 
     * @param tl 
     * @param br 
     */
    Lcd::TouchObject::TouchObject(std::string pName, Lcd::Position tl, Lcd::Position br){
    
        Lcd::TouchObject::name = pName;
        Lcd::TouchObject::topLeft = tl;
        Lcd::TouchObject::bottomRight = br;

    }

    /**
     * @brief Returns the Postion in the Top Left Corner of the TouchObject's Area.
     * 
     * @return Lcd::Position 
     */
    Lcd::Position Lcd::TouchObject::TopLeft(){
        return Lcd::TouchObject::topLeft;
    }

    /**
     * @brief Returns the Postion in the Bottom Right Corner of the TouchObject's Area.
     * 
     * @return Lcd::Position 
     */
    Lcd::Position Lcd::TouchObject::BottomRight(){
        return Lcd::TouchObject::bottomRight;
    }

    /**
     * @brief This method triggers the triggerFunction if the TouchArea is being Touched.
     * 
     */
    void Lcd::TouchObject::Trigger(){
        Lcd::Get()->TouchLock()->lock();

        if(Lcd::TouchObject::triggerFunction == 0){
            Lcd::Get()->TouchLock()->unlock();
            return;
        }

        bool nState = Lcd::TouchObject::IsBeingTouched();

        if(Lcd::TouchObject::beingTouched != nState){
            Lcd::TouchObject::beingTouched = nState;
            Lcd::TouchObject::triggerFunction(this);
        }

        Lcd::Get()->TouchLock()->unlock();
    }

    /**
     * @brief returns true when the TouchArea is being touched, false otherwise.
     * 
     * @return true 
     * @return false 
     */
    bool Lcd::TouchObject::IsBeingTouched(){
        TS_StateTypeDef TS_State;
        if(Lcd::Get()->Touch()->GetState(&TS_State) == TS_OK){
            if(TS_State.touchDetected >= 1){
                for(int touchIndex = 0; touchIndex < TS_State.touchDetected; touchIndex++){
                    uint16_t xPos = TS_State.touchX[touchIndex];
                    uint16_t yPos = TS_State.touchY[touchIndex];
                    if(
                        xPos > Lcd::TouchObject::TopLeft().x &&
                        yPos > Lcd::TouchObject::TopLeft().y &&
                        xPos < Lcd::TouchObject::BottomRight().x &&
                        yPos < Lcd::TouchObject::BottomRight().y
                    ){
                        return true;
                    }
                }
            }
        }else{
            sicet7::Serial::Console::Output("Error When Trying To Aquire State Of Touch Panel.");
        }
        return false;
    }

}