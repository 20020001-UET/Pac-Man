#ifndef HOW_TO_PLAY_H_
#define HOW_TO_PLAY_H_

#include "State.h"
#include "Console.h"
#include "Background.h"
#include "Button.h"

const int HOW_TO_PLAY_GIF_WIDTH = 550;
const int HOW_TO_PLAY_GIF_HEIGHT = 150;

///HowToPlayState class
class HowToPlayState :
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

#endif // HOW_TO_PLAY_H_

