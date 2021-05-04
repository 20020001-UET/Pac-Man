///Game Status [Header]
#ifndef GAME_STATUS_H_
#define GAME_STATUS_H_

#include "Console.h"
#include "Pacman.h"
#include "Graphic.h"
#include "Timer.h"
#include "System.h"
#include "Ghost.h"
#include "Golden.h"
#include <vector>

const NUMBER_TYPE NUMBER_TYPE_AT[NUMBER_TYPE_TOTAL] = { NUMBER_BLUE, NUMBER_DEFAULT };

const int GAMESTATUS_FRAME_VALUE = 5;
const int SCORE_ANIMATED_TIME = 2500;

enum UPDATE_SCORE
{
    UPDATE_SCORE_NORMAL_DOT = 0,
    UPDATE_SCORE_BIG_DOT,
    UPDATE_SCORE_EAT_GHOST,
    UPDATE_SCORE_EAT_FRUIT,
    UPDATE_SCORE_TOTAL
};
const Uint32 SCORE_NORMAL_DOT = 10;
const Uint32 SCORE_BIG_DOT = 50;
const Uint32 SCORE_EAT_GHOST_VALUE[GHOST_TYPE_TOTAL*2] = {200, 400, 800, 1600, 3200, 6400, 12800, 25600};
const Uint32 SCORE_EAT_FRUIT_VALUE[FRUIT_TYPE_TOTAL] = {500, 1000, 2000, 4000, 8000, 16000, 32000, 64000};

const int SCORE_TIME = 500;

struct ScoreObject
{
    Point screen;
    Uint32 start;
    int score_sprite;
    ScoreObject(Point _screen, Uint32 _start, int _score_sprite) :
        screen(_screen), start(_start), score_sprite(_score_sprite)
    {

    };
};

class GameStatus
{
    public:
        //Contructor:
        GameStatus();

        //Destructor:
        ~GameStatus();

        ///main function:
        void init(Pacman* _pacman, Graphic* _graphic, Timer* _timer, Uint32 _highscore, Point _highscore_point, Point _score_point, Point _life_point, Point _level_point, Point _power_point);
        void initBoss(Golden* _golden);

        ///push score
        void updateScore();
        void pushScore(const UPDATE_SCORE update_score, const Point screen);
        void setGhostEaten(int updateValue = 0);

        ///update loop
        void update();

        void render();
        void renderScore();

        Uint32 getScore();

        ///update animation
        void setAnimated(bool _animated = true);

        ///level
        int getLevel();
        void updateLevel();

        ///push hp
        void setHP();
        void updateHP();
        void pushDamage(const int damage_type);

    private:
        ///Console
        Console* console;

        ///Pacman
        Pacman* pacman;

        ///Boss
        Golden* golden;

        ///System
        Graphic* graphic;
        Timer* timer;

        ///Highscore
        Uint32 score, bonus, highscore;
        int score_state;
        int pacman_life;
        int level;

        Uint16 damageTaken;
        Uint16 healGiven;
        Uint16 BOSS_HP;

        ///Pacman power
        bool power[PACMAN_POWER_STATE_TOTAL];

        ///Point
        Point highscore_point;
        Point score_point;
        Point life_point;
        Point level_point;
        Point power_point;

        ///Animation
        bool animated;
        Uint32 startAnimated;
        int frame, frame_value;

        ///Render Score
        int curGhostEaten;
        std::vector<ScoreObject> scoreObject;

};

#endif // GAME_STATUS_H_
