#ifndef ABOUT_STATE_H_
#define ABOUT_STATE_H_

#include "State.h"
#include "Console.h"
#include "Background.h"
#include "Button.h"

///AboutState class
class AboutState :
    public State
{
    public:
        void init();
        void loop();
        void render();
        void keyPressed(int key_sym);
        void keyReleased(int key_sym);
        void close();

    private:
        Console* console;

        Background* background;

};

#endif // ABOUT_STATE_H_


