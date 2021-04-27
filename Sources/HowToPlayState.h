///HowToPlayState [Header]
#ifndef HOW_TO_PLAY_STATE_H_
#define HOW_TO_PLAY_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"

///HowToPlayState class
class HowToPlayState:
    public State
{
    public:
        //Constructor:
        HowToPlayState();

        //Destructor:
        ~HowToPlayState();

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

#endif // HOW_TO_PLAY_STATE_H_

