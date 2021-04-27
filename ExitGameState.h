///ExitGameState [Header]
#ifndef EXIT_GAME_STATE_H_
#define EXIT_GAME_STATE_H_

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
enum EXIT_GAME_BUTTON
{
    EXIT_GAME_BUTTON_YES = 0,
    EXIT_GAME_BUTTON_NO,
    EXIT_GAME_BUTTON_TOTAL
};

///Menu button tile + type
const Point EXIT_GAME_BUTTON_TILE[EXIT_GAME_BUTTON_TOTAL] = { Point(7, 17), Point(7, 20) };
const BUTTON_TYPE EXIT_GAME_BUTTON_TYPE_AT[EXIT_GAME_BUTTON_TOTAL] = { BUTTON_YES, BUTTON_NO };

///ExitGameState class
class ExitGameState:
    public State
{
    public:
        //Constructor:
        ExitGameState();

        //Destructor:
        ~ExitGameState();

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
        Button* button[EXIT_GAME_BUTTON_TOTAL];
        //the current button
        int curButton;
};

#endif // EXIT_GAME_STATE_H_


