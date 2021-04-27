///HighScoreState [Header]
#ifndef HIGHSCORE_STATE_H_
#define HIGHSCORE_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"

///HighScoreState
class HighScoreState:
    public State
{
    public:
        //Constructor:
        HighScoreState();

        //Destructor:
        ~HighScoreState();

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

#endif // HIGHSCORE_STATE_H_

