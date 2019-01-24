#include <classes/sicet7/Lcd/Lcd.h>
#include <mbed.h>
#include <rtos.h>
#include <LCD_DISCO_F746NG.h>
#include <TS_DISCO_F746NG.h>
#include <vector>
#include <classes/sicet7/Serial/Console/Console.h>
namespace sicet7{

    /// Static pointer default (private)
    Lcd* Lcd::instance = NULL;

    /// Static pointer default (private)
    rtos::Mutex* Lcd::lcdAccessLock = new rtos::Mutex("lcdAccessLock");

    rtos::Mutex* Lcd::subInstanceLock = new rtos::Mutex("lcdSubClassInstanceLock");

    /// Static pointer methods (public)
    Lcd* Lcd::Get(){
        
        //Lock to prevent accidental mutiple instances
        Lcd::lcdAccessLock->lock();

        if(Lcd::instance == NULL){
            Lcd::instance = new Lcd();
        }

        Lcd::lcdAccessLock->unlock();

        return Lcd::instance;

    }

    /// Private contructor
    Lcd::Lcd(){

        Lcd::DrawLock()->lock();
        Lcd::Display();
        Lcd::DrawLock()->unlock();

        Lcd::TouchLock()->lock();
        Lcd::Touch();
        Lcd::TouchLock()->unlock();

    }

    rtos::Mutex* Lcd::DrawLock(){

        Lcd::subInstanceLock->lock();

        if(Lcd::drawLockInstance == NULL){
            Lcd::drawLockInstance = new rtos::Mutex("DrawLock");
        }
    
        Lcd::subInstanceLock->unlock();

        return Lcd::drawLockInstance;

    }

    rtos::Mutex* Lcd::TouchLock(){

        Lcd::subInstanceLock->lock();

        if(Lcd::touchLockInstance == NULL){
            Lcd::touchLockInstance = new rtos::Mutex("TouchLock");
        }

        Lcd::subInstanceLock->unlock();

        return Lcd::touchLockInstance;

    }

    rtos::Mutex* Lcd::ViewLock(){
        Lcd::subInstanceLock->lock();

        if(Lcd::viewLockInstance == NULL){
            Lcd::viewLockInstance = new rtos::Mutex("ViewLock");
        }

        Lcd::subInstanceLock->unlock();

        return Lcd::viewLockInstance;
    }

    LCD_DISCO_F746NG* Lcd::Display(){
        Lcd::subInstanceLock->lock();

        if(Lcd::displayInstance == NULL){
            Lcd::displayInstance = new LCD_DISCO_F746NG();
            //Default Setup.
            Lcd::displayInstance->SetTextColor(LCD_COLOR_WHITE);
            Lcd::displayInstance->SetBackColor(LCD_COLOR_BLACK);
            Lcd::displayInstance->Clear(LCD_COLOR_BLACK);
        }

        Lcd::subInstanceLock->unlock();

        return Lcd::displayInstance;
    }

    TS_DISCO_F746NG* Lcd::Touch(){

        uint16_t xSize = Lcd::Display()->GetXSize();
        uint16_t ySize = Lcd::Display()->GetYSize();

        Lcd::subInstanceLock->lock();

        if(Lcd::touchInstance == NULL){
            Lcd::touchInstance = new TS_DISCO_F746NG();
        }

        if(Lcd::touchInstance->ITGetStatus() != TS_OK){
            if(Lcd::touchInstance->Init(xSize,ySize) != TS_OK){
                sicet7::Serial::Console::Output("Failed to Initialize Touch.");
            }
        }

        Lcd::subInstanceLock->unlock();
        
        return Lcd::touchInstance;
    }

    Lcd::~Lcd(){

        //de-allocation of memory
        delete Lcd::touchInstance;
        delete Lcd::displayInstance;
        delete Lcd::drawLockInstance;
        delete Lcd::touchLockInstance;
        delete Lcd::instance;

    }

    void Lcd::ActivateView(Lcd::View* view){
        Lcd::ViewLock()->lock();
        if(Lcd::CurrentView() != 0){
            Lcd::CurrentView()->Deactivate();
        }
        Lcd::currentView = view;
        Lcd::CurrentView()->Activate();
        Lcd::ViewLock()->unlock();
    }

    Lcd::View* Lcd::CurrentView(){
        return Lcd::currentView;
    }

    void Lcd::Clear(uint32_t color){

        if(Lcd::CurrentView() != 0){
            Lcd::CurrentView()->Deactivate();
        }
        Lcd::DrawLock()->lock();
        Lcd::currentView = 0;
        Lcd::Display()->Clear(color);
        Lcd::DrawLock()->unlock();

    }

}