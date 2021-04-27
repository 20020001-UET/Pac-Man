///Game Status [Header]
#ifndef GAME_STATUS_H_
#define GAME_STATUS_H_

#include "Pacman.h"
#include "Graphic.h"
#include "Timer.h"

const NUMBER_TYPE NUMBER_TYPE_AT[NUMBER_TYPE_TOTAL] = { NUMBER_BLUE, NUMBER_DEFAULT };

const int GAMESTATUS_FRAME_VALUE = 5;
const int SCORE_ANIMATED_TIME = 2500;

class GameStatus
{
    public:
        //Contructor:
        GameStatus();

        //Destructor:
        ~GameStatus();

        ///main function:
        void init(Pacman* _pacman, Graphic* _graphic, Timer* _timer, Point _highscore_point, Point _score_point, Point _life_point, Point _level_point);

        //load highscore

        //update level

        ///update loop
        void update();

        void render();

        ///update animation
        void setAnimated(bool _animated = true);

        ///update level
        void updateLevel();

    private:
        ///Pacman
        Pacman* pacman;

        ///System
        Graphic* graphic;
        Timer* timer;

        Uint16 score, bonus, highscore;
        int score_state;
        int pacman_life;
        int level;

        ///Point
        Point highscore_point;
        Point score_point;
        Point life_point;
        Point level_point;

        ///Animation
        bool animated;
        Uint32 startAnimated;
        int frame, frame_value;

};

#endif // GAME_STATUS_H_
