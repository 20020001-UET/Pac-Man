///AboutState [Header]
#ifndef ABOUT_STATE_H_
#define ABOUT_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"

///AboutState class
class AboutState:
    public State
{
    public:
        //Constructor:
        AboutState();

        //Destructor:
        ~AboutState();

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

#endif // ABOUT_STATE_H_

