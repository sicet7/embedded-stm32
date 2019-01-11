#include <structs/sicet7/Button/Button.h>
namespace sicet7{
    uint16_t Button::GetRows(){
        return Button::rows;
    }
    uint16_t Button::GetColumns(){
        return Button::columns;
    }
    uint16_t Button::GetPosition(){
        return Button::pos;
    }
    void Button::SetPosition(uint16_t position){
        if(position <= 0 || position > (rows*columns)) return;
        Button::pos = position;
    }
    void Button::SetColumns(uint16_t cols){
        if(cols <= 1) return;
        Button::columns = cols;
    }
    void Button::SetRows(uint16_t rowNumber){
        if(rowNumber <= 1) return;
        Button::rows = rowNumber;
    }
    void Button::SetState(TouchState newState){
        Button::state = newState;
    }
}