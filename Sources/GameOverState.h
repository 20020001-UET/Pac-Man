///GameOverState [Header]
#ifndef GAME_OVER_STATE_H_
#define GAME_OVER_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"
#include "Point.h"

///Score Point
const Point SCORE_GAME_OVER_POINT = Point(80*3, 72*3);
const Point LEVEL_GAME_OVER_POINT = Point(111*3, 112*3);

///GameOverState class
class GameOverState:
    public State
{
    public:
        //Constructor:
        GameOverState();

        //Destructor:
        ~GameOverState();

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

#endif // GAME_OVER_STATE_H_


