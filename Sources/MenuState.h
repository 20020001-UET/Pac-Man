///MenuState [Header]
#ifndef MENU_STATE_H_
#define MENU_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"
#include "Button.h"
#include "Point.h"

///Menu button
enum MENU_BUTTON
{
    MENU_BUTTON_START = 0,
    MENU_BUTTON_HOW_TO_PLAY,
    MENU_BUTTON_SETTING,
    MENU_BUTTON_HIGHSCORE,
    MENU_BUTTON_ABOUT,
    MENU_BUTTON_EXIT,
    MENU_BUTTON_TOTAL
};

///Menu button tile + type
const Point MENU_BUTTON_TILE[MENU_BUTTON_TOTAL] = { Point(7, 16), Point(7, 19), Point(7, 22), Point(7, 25), Point(7, 28), Point(7, 31) };
const BUTTON_TYPE MENU_BUTTON_TYPE_AT[BUTTON_TYPE_TOTAL] = { BUTTON_START,
                                                        BUTTON_HOW_TO_PLAY,
                                                        BUTTON_SETTING,
                                                        BUTTON_HIGHSCORE,
                                                        BUTTON_ABOUT,
                                                        BUTTON_EXIT };

///MenuState class
class MenuState:
    public State
{
    public:
        //Constructor:
        MenuState();

        //Destructor:
        ~MenuState();

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
        Button* button[MENU_BUTTON_TOTAL];
        //the current button
        int curButton;
};

#endif // MENU_STATE_H_

