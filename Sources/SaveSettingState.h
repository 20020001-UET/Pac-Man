///SaveSettingState [Header]
#ifndef SAVE_SETTING_STATE_H_
#define SAVE_SETTING_STATE_H_

///Include header
#include <SDL.h>
#include "Graphic.h"
#include "Audio.h"
#include "Timer.h"
#include "State.h"
#include "Console.h"
#include "Background.h"
#include "Button.h"
#include "Point.h"

///Menu button
enum SAVE_SETTING_BUTTON
{
    SAVE_SETTING_BUTTON_YES = 0,
    SAVE_SETTING_BUTTON_NO,
    SAVE_SETTING_BUTTON_TOTAL
};

///Menu button tile + type
const Point SAVE_SETTING_BUTTON_TILE[SAVE_SETTING_BUTTON_TOTAL] = { Point(7, 17), Point(7, 20) };
const BUTTON_TYPE SAVE_SETTING_BUTTON_TYPE_AT[SAVE_SETTING_BUTTON_TOTAL] = { BUTTON_YES, BUTTON_NO };

///SaveSettingState class
class SaveSettingState:
    public State
{
    public:
        //Constructor:
        SaveSettingState();

        //Destructor:
        ~SaveSettingState();

        ///function:
        //init:
        void init(System* _system);

        //loop:
        void loop();

        //render:
        void render();

        //handle key event:
        void keyPressed(const int key_code);
        void keyReleased(const int key_code);

        //close:
        void close();

        //button function:
        void updateButton(int change);
        void handleButton();

    private:
        ///Console
        Console* console;

        ///Background & Button
        Background* background;
        Button* button[SAVE_SETTING_BUTTON_TOTAL];
        //the current button
        int curButton;
};

#endif // SAVE_SETTING_STATE_H_


