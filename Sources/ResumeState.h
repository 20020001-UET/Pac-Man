
///ResumeState [Header]
#ifndef RESUME_STATE_H_
#define RESUME_STATE_H_

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
enum RESUME_BUTTON
{
    RESUME_BUTTON_REUSME = 0,
    RESUME_BUTTON_EXIT,
    RESUME_BUTTON_TOTAL
};

///Menu button tile + type
const Point RESUME_BUTTON_TILE[RESUME_BUTTON_TOTAL] = { Point(7, 17), Point(7, 20) };
const BUTTON_TYPE RESUME_BUTTON_TYPE_AT[RESUME_BUTTON_TOTAL] = { BUTTON_RESUME, BUTTON_EXIT };

///ResumeState class
class ResumeState:
    public State
{
    public:
        //Constructor:
        ResumeState();

        //Destructor:
        ~ResumeState();

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
        Button* button[RESUME_BUTTON_TOTAL];
        //the current button
        int curButton;
};

#endif // RESUME_STATE_H_


