#ifndef MENU_STATE_H_
#define MENU_STATE_H_

#include "State.h"
#include "Console.h"
#include "Background.h"
#include "Button.h"

const Point button_point[5] = { Point(6, 15), Point(6, 18), Point(6, 21), Point(6, 24), Point(6, 27)};

///MenuState class
class MenuState :
    public State
{
    public:
        void init();
        void loop();
        void render();
        void keyPressed(int key_sym);
        void keyReleased(int key_sym);
        void close();

        void handleButton();

    private:
        Console* console;

        Background* background;
        int cur_button;
        Button* button;

};

#endif // MENU_STATE_H_
