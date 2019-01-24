/**
 * @file Lcd.h
 * @author Martin René Sørensen (sicet7@randomphp.com)
 * @brief This is a definition of the Lcd super class
 * @version 0.1
 * @date 2019-01-22
 * 
 */
#pragma once
#include <mbed.h>
#include <rtos.h>
#include <LCD_DISCO_F746NG.h>
#include <TS_DISCO_F746NG.h>
#include <vector>
#include <string>
#include <utility>
#include <fonts.h>
namespace sicet7{
    class Lcd{

        /// This property stores the pointer to the super class instance.
        private: static Lcd* instance;

        /// This property stores a pointer to the lock that prevents multible threads from accidentally instanziating multible instances of the super class.
        private: static rtos::Mutex* lcdAccessLock;

        /// This property stores a pointer to the lock that ensures singleton of subclasses.
        private: static rtos::Mutex* subInstanceLock;

        /// This property stores the pointer to the LCD_DISCO_F746NG instance.
        private: LCD_DISCO_F746NG* displayInstance = NULL;

        /// This property stores the pointer to the TS_DISCO_F746NG instance.
        private: TS_DISCO_F746NG* touchInstance = NULL;

        /// This property stores the pointer to the Draw Lock Mutex instance.
        private: rtos::Mutex* drawLockInstance = NULL;

        /// This property stores the pointer to the Touch Lock Mutex instance.
        private: rtos::Mutex* touchLockInstance = NULL;

        private: rtos::Mutex* viewLockInstance = NULL;

        /// Private constructor prevents manual instanziation of the super class.
        private: Lcd();

        /// This method should be used when an instance of the super class is wanted.(singleton)
        public: static Lcd* Get();

        /// This method should be used to get a pointer to the current instance of the LCD_DISCO_F746NG class.
        public: LCD_DISCO_F746NG* Display();

        /// This method should be used to get a pointer to the current instance of the TS_DISCO_F746NG class.
        public: TS_DISCO_F746NG* Touch();

        /// This method should return a pointer to the mutex that should be locked when drawing on the display.
        public: rtos::Mutex* DrawLock();

        /// This method should return a pointer to the mutex that should be locked while processing touch input.
        public: rtos::Mutex* TouchLock();

        public: rtos::Mutex* ViewLock();

        /// Public destructor to prevent a crash when the Application Reboots.
        public: ~Lcd();

        /// This method will clear the Lcd Display.
        public: void Clear(uint32_t color);

        /**
         * @brief This is a General Purpose Position struct to keep track of positions.
         */
        public: struct Position{
            public: uint16_t x;
            public: uint16_t y;
        };

        /**
         * @brief This is a General Purpose Size struct to keep track of sizes.
         */
        public: struct Size{
            public: uint16_t width;
            public: uint16_t height;
        };

        public: struct UpdatableOutput{
            public: std::string value;
            public: void Update(std::string val){
                Lcd::UpdatableOutput::value = val;
            }
        };

        public: class TouchObject{

            protected: std::string name;
            protected: Position topLeft;
            protected: Position bottomRight;
            protected: bool beingTouched = false;
            public: void (*triggerFunction)(TouchObject*) = 0;

            public: TouchObject(
                std::string name, 
                Position topLeft, 
                Position bottomRight
            );

            protected: bool IsBeingTouched();
            public: void Trigger();

            public: Position TopLeft();
            public: Position BottomRight();
            public: std::string GetName();
            public: bool IsPress();

        };

        /**
         * @brief This is a abstact definition of the way DisplayObject's is handled.
         * @warning This Object is Abstract and can therefor not be passed by copy.
         */
        public: class DisplayObject{
            protected: static vector<std::string> allNames;
            protected: static rtos::Mutex* nameManagementLock;
            protected: std::string name = "default";

            protected: Position initialPosition;
            protected: uint32_t textColor = LCD_COLOR_GREEN;
            protected: uint32_t backgroundColor = LCD_COLOR_BLACK;

            protected: uint32_t updateMillis = 0;
            protected: uint32_t lastUpated = 0;

            protected: bool isDisplayed = false;

            protected: vector<DisplayObject*> children;
            protected: DisplayObject* parent = 0;

            //Methods

            public: ~DisplayObject();

            //TODO: Make this name management system.
            public: bool AssignName(std::string name);
            public: std::string GetName();

            public: uint32_t GetTextColor();
            public: uint32_t GetBackgroundColor();
            public: void SetTextColor(uint32_t color);
            public: void SetBackgroundColor(uint32_t color);

            public: bool IsDisplayed();

            public: bool HasParent();
            public: bool HasChildren();
            public: vector<DisplayObject*>* GetChildren();
            public: DisplayObject* GetParent();
            public: void SetParent(DisplayObject* parentPtr);
            public: void AddChildObject(DisplayObject* child);

            private: uint32_t GetMillis();
            public: void Update(LCD_DISCO_F746NG* lcd);
            public: uint32_t LastUpdated();
            public: uint32_t UpdateInterval();
            public: void SetUpdateInterval(uint32_t value);

            public: void Draw(LCD_DISCO_F746NG* lcd);
            public: void Clear(LCD_DISCO_F746NG* lcd);

            public: virtual void CustomDraw(LCD_DISCO_F746NG* lcd) = 0;
            public: virtual void CustomClear(LCD_DISCO_F746NG* lcd) = 0;
        };

        public: class View{

            protected: View();
            public: ~View();

            /// This vector should contain all the touchObjects on the view.
            protected: vector<TouchObject*> touchObjects;

            /// This vector should contain all the displayObjects in the view.
            protected: vector<DisplayObject*> displayObjects;

            /// This indicates whether or not the view is activated.
            protected: bool activated = false;

            /// This method Add's a TouchObject Pointer to the View's "touchObjects" vector.
            public: void AddTouchObject(TouchObject* to);

            /// This method Add's a DisplayObject Pointer to the View's "displayObjects" vector.
            public: void AddDisplayObject(std::string uniqueName, DisplayObject* dis);

            /// This method is used to add a relationship between 2 display objects.
            public: void AddRelationship(std::string parentName, std::string childName);

            /// This method activates the view.
            public: void Activate();

            /// This method deactivates the view.
            public: void Deactivate();

            /// This method returns a boolean value that represents whether or not the view is activated.
            public: bool IsActivated();

            /// This method should be called when wanting to update DisplayObject's display state.
            public: void Update();

            /// This method should be called when wanting to process the current touch state.
            public: void ProcessTouch();

            /** This method is called after the "Activate" method.
              * This method should be implemented in classes that inherit from the "view" class. */
            public: virtual void CustomActivate();

            /** This method is called after the "Deactivate" method.
              * This method should be implemented in classes that inherit from the "view" class. */
            public: virtual void CustomDeactivate();

            public: virtual void CustomUpdate();

        };

        /// This property should store a pointer to the view that is currently active.
        public: View* currentView = 0;

        /// This method should return a pointer to the view that is currently active.
        public: View* CurrentView();

        /// This method will activate 
        public: void ActivateView(View* newView);

        public: class Rectangle : public Lcd::DisplayObject{

            protected: Lcd::Size size;
            protected: bool filled = false;

            public: Rectangle(Lcd::Position topLeft, Lcd::Size size);
            public: Rectangle(Lcd::Position topLeft, Lcd::Size size, bool filled);

            public: void CustomDraw(LCD_DISCO_F746NG* lcd) override;
            public: void CustomClear(LCD_DISCO_F746NG* lcd) override;

        };

        public: class Text : public Lcd::DisplayObject{

            protected: sFONT* font = &Font12;
            protected: Lcd::UpdatableOutput* text = 0;
            protected: std::string textString;
            protected: Text_AlignModeTypdef mode = LEFT_MODE;
            protected: Lcd::Position bottomRight;
            protected: uint16_t lineSpacing = 2;
            protected: uint16_t topPadding = 0;

            public: Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text);
            public: Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text, sFONT* font);
            public: Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text, sFONT* font, Text_AlignModeTypdef mode);
            public: Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text, sFONT* font, Text_AlignModeTypdef mode, uint16_t lineSpacing);
            public: Text(Lcd::Position pos, Lcd::Position pos2, Lcd::UpdatableOutput* text, sFONT* font, Text_AlignModeTypdef mode, uint16_t lineSpacing, uint16_t topPadding);

            public: Text(Lcd::Position pos, Lcd::Position pos2, std::string text);
            public: Text(Lcd::Position pos, Lcd::Position pos2, std::string text, sFONT* font);
            public: Text(Lcd::Position pos, Lcd::Position pos2, std::string text, sFONT* font, Text_AlignModeTypdef mode);
            public: Text(Lcd::Position pos, Lcd::Position pos2, std::string text, sFONT* font, Text_AlignModeTypdef mode, uint16_t lineSpacing);
            public: Text(Lcd::Position pos, Lcd::Position pos2, std::string text, sFONT* font, Text_AlignModeTypdef mode, uint16_t lineSpacing, uint16_t topPadding);


            protected: uint32_t GetMaxCharsPerLine();
            protected: uint32_t GetTextAreaWidth();
            protected: uint32_t GetTextAreaHeight();

            protected: vector<std::string> SplitText();

            public: void CustomDraw(LCD_DISCO_F746NG* lcd) override;
            public: void CustomClear(LCD_DISCO_F746NG* lcd) override;

        };

    };
}