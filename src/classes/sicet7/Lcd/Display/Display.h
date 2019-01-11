#ifndef MY_DISPLAY_CLASS
    #define MY_DISPLAY_CLASS

    #include <structs/sicet7/Button/Button.h>
    #include <structs/sicet7/Area/Area.h>
    #include <enums/TouchState/TouchState.h>
    #include <TS_DISCO_F746NG.h>
    #include <vector>

    namespace sicet7{
        namespace Lcd{
            class Display{

                public:
                    //Properties
                    bool flipped = false;

                    std::vector<Button> buttons;

                    //Constructor
                    Display();

                    //Methods
                    bool EnableTouch();
                    void RunTouch();
                    void Clear(uint32_t color);
                    void DrawButtons();
                    void ClearButtons();
                    void SetBackgroundColor(uint32_t color);
                    uint32_t GetTextColor();
                    void SetTextColor(uint32_t color);
                    void ClearStringLine(uint32_t line);
                    void RenderTextAt(uint16_t xPos,u_int16_t yPos, char* text, Text_AlignModeTypdef mode);
                    bool IsTouchEnabled();
                    void AddButton(Button but);
                    uint32_t GetBackgroundColor();
                    Area GetButtonArea(Button bp);

                private:
                    bool touchEnabled = false;
                    uint8_t lastIterationTouches = 0;
                    void ProcessTouchPosition();

            };
        }
    }

#endif