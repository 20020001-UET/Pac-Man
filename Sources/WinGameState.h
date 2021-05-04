///WinGameState [Header]
#ifndef WIN_GAME_STATE_H_
#define WIN_GAME_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"
#include "Point.h"

///Score Point
const Point SCORE_WIN_GAME_POINT = Point(80*3, 108*3);

///WinGameState class
class WinGameState:
    public State
{
    public:
        //Constructor:
        WinGameState();

        //Destructor:
        ~WinGameState();

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

    private:
        ///Console
        Console* console;

        ///Background
        Background* background;
};

#endif // WIN_GAME_STATE_H_


