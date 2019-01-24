/**
 * @file DisplayObject.cpp
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief This is the implementation of the Lcd::DisplayObject Class.
 * @version 0.1
 * @date 2019-01-22
 * 
 */
#include <classes/sicet7/Lcd/Lcd.h>
#include <mbed.h>
#include <rtos.h>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{
    
    /**
     * @brief This is the vector that is used to hold all the names of the DisplayObject Instances.
     * 
     */
    vector<std::string> Lcd::DisplayObject::allNames = vector<std::string>();

    /**
     * @brief This is the mutex used to prevent douplicate name definitions when working with multi-threading.
     * 
     */
    rtos::Mutex* Lcd::DisplayObject::nameManagementLock = new rtos::Mutex("displayObjectNameManagementLock");

    /**
     * @brief Destroy the Lcd::DisplayObject object
     * 
     */
    Lcd::DisplayObject::~DisplayObject(){

        if(Lcd::DisplayObject::name != "default"){

            vector<std::string>::iterator iter;

            iter = std::find(
                Lcd::DisplayObject::allNames.begin(),
                Lcd::DisplayObject::allNames.end(), 
                Lcd::DisplayObject::name
            );

            if(iter != Lcd::DisplayObject::allNames.end()){
                Lcd::DisplayObject::allNames.erase(iter);
            }

        }

    }

    /**
     * @brief Assigns a name to the DisplayObject
     * 
     * @param aName std::string object of the wanted name.
     * @return true 
     * @return false 
     */
    bool Lcd::DisplayObject::AssignName(std::string aName){

        if(aName == "default" || Lcd::DisplayObject::name != "default"){
            return false;
        }

        Lcd::DisplayObject::nameManagementLock->lock();

        if(std::find(
                Lcd::DisplayObject::allNames.begin(),
                Lcd::DisplayObject::allNames.end(), 
                aName
            ) != Lcd::DisplayObject::allNames.end()
        ){
            return false;
        }

        Lcd::DisplayObject::name = aName;
        Lcd::DisplayObject::allNames.push_back(aName);

        Lcd::DisplayObject::nameManagementLock->unlock();

        return true;

    }

    /**
     * @brief returns the name of the DisplayObject
     * 
     * @return std::string 
     */
    std::string Lcd::DisplayObject::GetName(){
        return Lcd::DisplayObject::name;
    }

    /**
     * @brief This will return the text color of the Lcd::DisplayObject.
     * 
     * @return uint32_t 
     */
    uint32_t Lcd::DisplayObject::GetTextColor(){
        return Lcd::DisplayObject::textColor;
    }

    /**
     * @brief This will return the background color of the Lcd::DisplayObject
     * 
     * @return uint32_t 
     */
    uint32_t Lcd::DisplayObject::GetBackgroundColor(){
        return Lcd::DisplayObject::backgroundColor;
    }

    /**
     * @brief This is used to set the text color of the Lcd::DisplayObject.
     * 
     * @param color 
     */
    void Lcd::DisplayObject::SetTextColor(uint32_t color){
        Lcd::DisplayObject::textColor = color;
    }

    /**
     * @brief This is used to set the background color of the Lcd::DisplayObject.
     * 
     * @param color 
     */
    void Lcd::DisplayObject::SetBackgroundColor(uint32_t color){
        Lcd::DisplayObject::backgroundColor = color;
    }

    /**
     * @brief This returns a boolean representing whether or not the Lcd::DisplayObject is currently being shown on the screen.
     * 
     * @return true 
     * @return false 
     */
    bool Lcd::DisplayObject::IsDisplayed(){
        return Lcd::DisplayObject::isDisplayed;
    }

    /**
     * @brief Return a boolean value that represents whether or not the Lcd::DisplayObject has a parent object.
     * 
     * @return true 
     * @return false 
     */
    bool Lcd::DisplayObject::HasParent(){
        return (Lcd::DisplayObject::parent != 0);
    }

    /**
     * @brief Return a boolean value that represents whether or not the Lcd::DisplayObject has children.
     * 
     * @return true 
     * @return false 
     */
    bool Lcd::DisplayObject::HasChildren(){
        return (Lcd::DisplayObject::children.empty() != true);
    }

    /**
     * @brief Returns a pointer to the vector containing the pointers to the children objects.
     * 
     * @return vector<Lcd::DisplayObject*>* 
     */
    vector<Lcd::DisplayObject*>* Lcd::DisplayObject::GetChildren(){
        return &children;
    }

    /**
     * @brief Returns a pointer to the parent object.
     * 
     * @return Lcd::DisplayObject* 
     */
    Lcd::DisplayObject* Lcd::DisplayObject::GetParent(){
        return Lcd::DisplayObject::parent;
    }

    /**
     * @brief Sets the parent pointer to the one provided to this method.
     * 
     * @param parentPtr 
     */
    void Lcd::DisplayObject::SetParent(Lcd::DisplayObject* parentPtr){
        Lcd::DisplayObject::parent = parentPtr;
    }

    /**
     * @brief Adds a child pointer to the vector containing all the child pointers
     * 
     * @param childPtr 
     */
    void Lcd::DisplayObject::AddChildObject(Lcd::DisplayObject* childPtr){
        Lcd::DisplayObject::children.push_back(childPtr);
    }

    /**
     * @brief Returns the time since the program was started, in milliseconds.
     * 
     * @return uint32_t 
     */
    uint32_t Lcd::DisplayObject::GetMillis(){

        uint32_t tickPerMs;
        switch(HAL_GetTickFreq()){
            case HAL_TICK_FREQ_1KHZ:
                tickPerMs = 1;
            break;
            case HAL_TICK_FREQ_100HZ:
                tickPerMs = 10;
            break;
            case HAL_TICK_FREQ_10HZ:
                tickPerMs = 100;
            break;
            default:
                tickPerMs = 1;
            break;
        }

        return (uint32_t)std::floor(HAL_GetTick()/tickPerMs);

    }

    /**
     * @brief Redraws the DisplayObject if the UpdateInterval has passed.
     * 
     * @param lcd 
     */
    void Lcd::DisplayObject::Update(LCD_DISCO_F746NG* lcd){
        if(
            (Lcd::DisplayObject::GetMillis()-Lcd::DisplayObject::LastUpdated())
                > Lcd::DisplayObject::UpdateInterval() &&
                Lcd::DisplayObject::UpdateInterval() > 0
        ){
            Lcd::DisplayObject::Clear(lcd);
            Lcd::DisplayObject::Draw(lcd);
            Lcd::DisplayObject::lastUpated = Lcd::DisplayObject::GetMillis();
        }
    }

    /**
     * @brief Returns the Millis Timestamp when the DisplayObject last was updated.
     * 
     * @return uint32_t 
     */
    uint32_t Lcd::DisplayObject::LastUpdated(){
        return Lcd::DisplayObject::lastUpated;
    }

    /**
     * @brief Returns the Millis Interval in witch the DisplayObject should be updated.
     * 
     * @return u_int32_t 
     */
    u_int32_t Lcd::DisplayObject::UpdateInterval(){
        return Lcd::DisplayObject::updateMillis;
    }

    /**
     * @brief Is used to set the Update Interval of the DisplayObject.
     * 
     * @param millis 
     */
    void Lcd::DisplayObject::SetUpdateInterval(uint32_t millis){
        Lcd::DisplayObject::updateMillis = millis;
    }

    /**
     * @brief This method should be called when the display object should be drawn.
     * 
     * @param lcd 
     */
    void Lcd::DisplayObject::Draw(LCD_DISCO_F746NG* lcd){
        
        static uint32_t oldTextColor;
        static uint32_t oldBackgroundColor;
        
        Lcd::Get()->DrawLock()->lock();
        oldTextColor = lcd->GetTextColor();
        oldBackgroundColor = lcd->GetBackColor();
        lcd->SetTextColor(Lcd::DisplayObject::GetTextColor());
        lcd->SetBackColor(Lcd::DisplayObject::GetBackgroundColor());
        
        CustomDraw(lcd);
        
        lcd->SetTextColor(oldTextColor);
        lcd->SetBackColor(oldBackgroundColor);
        oldTextColor = NULL;
        oldBackgroundColor = NULL;
        Lcd::DisplayObject::isDisplayed = true;
        Lcd::Get()->DrawLock()->unlock();
        
        vector<Lcd::DisplayObject*>::iterator iter;

        for(iter = Lcd::DisplayObject::children.begin(); iter != Lcd::DisplayObject::children.end(); ++iter){
            (*iter)->Draw(lcd);
        }

    }

    /**
     * @brief This method should be called when the display object should be removed from the display.
     * 
     * @param lcd 
     */
    void Lcd::DisplayObject::Clear(LCD_DISCO_F746NG* lcd){

        vector<Lcd::DisplayObject*>::iterator iter;

        for(iter = Lcd::DisplayObject::children.begin(); iter != Lcd::DisplayObject::children.end(); ++iter){
            (*iter)->Clear(lcd);
        }

        Lcd::Get()->DrawLock()->lock();
        
        CustomClear(lcd);
        
        Lcd::DisplayObject::isDisplayed = false;
        Lcd::Get()->DrawLock()->unlock();
    }

    /**
     * @brief This method is called by the Draw method.
     * @warning When this method is called from the Draw method, the drawlock has alreadt been optained.
     * @param lcd 
     */
    /*void Lcd::DisplayObject::CustomDraw(LCD_DISCO_F746NG* lcd){
        sicet7::Serial::Console::Output("Missing CustomDraw Implementation!");
    }*/

    /**
     * @brief This method is called by the Clear method.
     * @warning When this method is called from the Clear method, the drawlock has already been optained.
     * @param lcd 
     */
    /*void Lcd::DisplayObject::CustomClear(LCD_DISCO_F746NG* lcd){
        sicet7::Serial::Console::Output("Missing Clear Implementation!");
    }*/

}