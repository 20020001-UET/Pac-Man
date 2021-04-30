///HighScoreState [Header]
#ifndef HIGHSCORE_STATE_H_
#define HIGHSCORE_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"
#include <vector>

///Constance value
const int HIGHSCORE_TOTAL = 10;
const Point HIGHSCORE_TABLE_POINT[HIGHSCORE_TOTAL] = {Point(112*3, 80*3),
                                                Point(112*3, 100*3),
                                                Point(112*3, 120*3),
                                                Point(112*3, 140*3),
                                                Point(112*3, 160*3),
                                                Point(112*3, 180*3),
                                                Point(112*3, 200*3),
                                                Point(112*3, 220*3),
                                                Point(112*3, 240*3),
                                                Point(112*3, 260*3)};

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

        //Vector
        std::vector<Uint32> score;
};

#endif // HIGHSCORE_STATE_H_

