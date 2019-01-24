#pragma once
#include <structs/sicet7/Button/Button.h>
namespace sicet7{
    namespace Application{
        class Action{
            public:

                static bool OnBoardButtonPressInProgress;

                static void OnBoardButtonRise();
                static void OnBoardButtonFall();
                static void TouchButtonPushed(Button but);
        };
    }
}