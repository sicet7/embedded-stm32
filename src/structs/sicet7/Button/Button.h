#ifndef MY_BUTTON_STRUCT
    #define MY_BUTTON_STRUCT

    #include <stdint.h>
    #include <LCD_DISCO_F746NG.h>
    #include <enums/TouchState/TouchState.h>

    namespace sicet7{

        struct Button{

            private:

                uint16_t pos = 1;
                uint16_t rows = 2;
                uint16_t columns = 2;

            public:
                uint16_t id = 0;
                void (*click)(Button) = 0;
                TouchState state = Up;
                char* text;
                bool filled = false;
                uint32_t color = LCD_COLOR_BLACK;
                uint32_t textColor = LCD_COLOR_BLACK;
                void SetState(TouchState state);

                //Position

                void SetPosition(uint16_t pos);
                uint16_t GetPosition();

                //Rows

                void SetRows(uint16_t rowNumber);
                uint16_t GetRows();

                //Columns

                void SetColumns(uint16_t columnNumber);
                uint16_t GetColumns();

        };

    }

#endif