///SettingState [Header]
#ifndef SETTING_STATE_H_
#define SETTING_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"
#include "SettingButton.h"
#include "Point.h"

///Setting button tile + type
const Point SETTING_BUTTON_TILE[SETTING_BUTTON_TYPE_TOTAL] = { Point(3, 9), Point(3, 13), Point(3, 19), Point(3, 26) };
const SETTING_BUTTON_TYPE SETTING_BUTTON_TYPE_AT[SETTING_BUTTON_TYPE_TOTAL] = { SETTING_BUTTON_VOLUME_MUSIC,
                                                                                SETTING_BUTTON_VOLUME_SOUND,
                                                                                SETTING_BUTTON_CONTROL,
                                                                                SETTING_BUTTON_GRAPHIC };

///SettingState
class SettingState:
    public State
{
    public:
        //Constructor:
        SettingState();

        //Destructor:
        ~SettingState();

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

        ///button function:
        void updateButton(int change);
        void updateState(int change);
        void handleButton();

        //close:
        void close();

    private:
        ///Console
        Console* console;

        ///Background
        Background* background;

        ///Setting button
        SettingButton* setting_button[SETTING_BUTTON_TYPE_TOTAL];
        int curButton;
        bool changed;
};

#endif // SETTING_STATE_H_
