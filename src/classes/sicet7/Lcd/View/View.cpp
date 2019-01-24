#include <classes/sicet7/Lcd/Lcd.h>
#include <classes/sicet7/Serial/Console/Console.h>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
namespace sicet7{
    
    Lcd::View::View(){}

    void Lcd::View::AddDisplayObject(std::string uniqueName, DisplayObject* dis){

        if(dis->AssignName(uniqueName) == true){
            Lcd::View::displayObjects.push_back(dis);
        }else{
            sicet7::Serial::Console::Output("Failed to Add \"DisplayObject\" name already exists or is already assigned.");
        }

    }

    void Lcd::View::AddTouchObject(Lcd::TouchObject* to){

        Lcd::View::touchObjects.push_back(to);

    }

    void Lcd::View::Update(){

        CustomUpdate();

        std::vector<Lcd::DisplayObject*>::iterator itera;

        for(itera = Lcd::View::displayObjects.begin(); itera != Lcd::View::displayObjects.end(); ++itera){
            (*itera)->Update(Lcd::Get()->Display());
        }

    }

    bool Lcd::View::IsActivated(){
        return Lcd::View::activated;
    }

    void Lcd::View::AddRelationship(std::string parentName, std::string childName){

        //prevent a pointer loop.
        if(parentName == childName) return;

        std::vector<Lcd::DisplayObject*>::iterator itera;
        Lcd::DisplayObject* parentPtr = 0;
        Lcd::DisplayObject* childPtr = 0;

        Lcd::Get()->DrawLock()->lock();

        for(itera = Lcd::View::displayObjects.begin(); itera != Lcd::View::displayObjects.end(); ++itera){

            if((*itera)->GetName() == parentName){
                parentPtr = (*itera);
            }

            if((*itera)->GetName() == childName){
                childPtr = (*itera);
            }

        }

        if(parentPtr == 0 || childPtr == 0){
            sicet7::Serial::Console::Output("Could not Add relationship, because of nullptr.");
            Lcd::Get()->DrawLock()->unlock();
            return;
        }

        if(childPtr->HasParent() == true){
            sicet7::Serial::Console::Output("Could not Add relationship. Child already has parent.");
            Lcd::Get()->DrawLock()->unlock();
            return;
        }

        std::vector<Lcd::DisplayObject*>::iterator it;

        for(it = parentPtr->GetChildren()->begin(); it != parentPtr->GetChildren()->end(); ++it){
            if((*it)->GetName() == childName){
                sicet7::Serial::Console::Output("Could not Add relationship. Parent already has the child.");
                Lcd::Get()->DrawLock()->unlock();
                return;
            }
        }

        childPtr->SetParent(parentPtr);
        parentPtr->AddChildObject(childPtr);

        Lcd::Get()->DrawLock()->unlock();

    }

    void Lcd::View::Activate(){

        for(std::vector<Lcd::DisplayObject*>::iterator itera = Lcd::View::displayObjects.begin(); itera != Lcd::View::displayObjects.end(); ++itera){

            if((*itera)->HasParent() == false){
                Lcd::Get()->DrawLock()->lock();
                (*itera)->Draw(Lcd::Get()->Display());
                Lcd::Get()->DrawLock()->unlock();
            }

        }

        CustomActivate();

        View::activated = true;
    }

    void Lcd::View::Deactivate(){

        for(std::vector<Lcd::DisplayObject*>::iterator itera = Lcd::View::displayObjects.begin(); itera != Lcd::View::displayObjects.end(); ++itera){

            if((*itera)->HasParent() == false){
                Lcd::Get()->DrawLock()->lock();
                (*itera)->Clear(Lcd::Get()->Display());
                Lcd::Get()->DrawLock()->unlock();
            }

        }

        CustomDeactivate();

        View::activated = false;
    }

    void Lcd::View::ProcessTouch(){
        
        std::vector<Lcd::TouchObject*>::iterator itera;

        for(itera = Lcd::View::touchObjects.begin(); itera != Lcd::View::touchObjects.end(); ++itera){
            (*itera)->Trigger();
        }

    }

    void Lcd::View::CustomActivate(){
        sicet7::Serial::Console::Output("Missing CustomActivate Implementation.");
    }

    void Lcd::View::CustomDeactivate(){
        sicet7::Serial::Console::Output("Missing CustomDeactivate Implementation.");
    }

    void Lcd::View::CustomUpdate(){
        sicet7::Serial::Console::Output("Missing CustomUpdate Implementation.");
    }

}