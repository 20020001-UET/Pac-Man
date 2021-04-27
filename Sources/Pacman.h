///Pacman [Header]
#ifndef PACMAN_H_
#define PACMAN_H_

///Include header
#include "Entity.h"
#include "Direction.h"
#include <queue>
#include <deque>

///Pacman constance value
const int PACMAN_SPEED = 3;
const int PACMAN_FRAME_VALUE = 4;
const int PACMAN_LIFE = 5;

///Pacman state
enum PACMAN_STATE
{
    PACMAN_INIT_STATE = 0,
    PACMAN_NEW_STATE,
    PACMAN_STAND_STATE,
    PACMAN_RUNNING_STATE,
    PACMAN_EATING_STATE,
    PACMAN_DEATH_STATE,
    PACMAN_STATE_TOTAL
};

const int PACMAN_EATING_STATE_TIME = 960;

///Pacman power state
enum PACMAN_POWER_STATE
{
    NORMAL_PACMAN = 0,
    POWER_PACMAN,
    SPEED_PACMAN,
    INVISIBLE_PACMAN,
    FREE_TIME_PACMAN,
    PACMAN_POWER_STATE_TOTAL
};
const int POWER_TIME[PACMAN_POWER_STATE_TOTAL] = {0, 8300, 4000, 4000, 7200};

///Pacman class
class Pacman :
    public Entity
{
    public:
        //Contructor:
        Pacman(PACMAN_TYPE _pacman_type = PACMAN_DEFAULT);

        //Destructor:
        ~Pacman();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* timer, Point _stand);

        //loop:
        void loop();

        //render:
        void render();

        ///state function:
        //state:
        PACMAN_STATE getState();
        void setState(PACMAN_STATE newState);
        void initState();
        void handleState();

        //power:
        void setPower(PACMAN_POWER_STATE newPower);
        void initPower(PACMAN_POWER_STATE curNewPower);
        void handlePower();
        void removePower(int curLastPower);

        //playing function:
        DIRECTION getCurDirection();
        DIRECTION getLastDirection();
        void setDirection(DIRECTION newDirection);
        void eatDot();
        void stop(bool canPacmanMove = true);

        bool isDead();
        void dead();

        //dot function:
        int getDotEaten() const;

        //life function:
        int getCurLife() const;

    private:
        ///Pacman type
        PACMAN_TYPE pacman_type;
        ///State
        PACMAN_STATE curState;
        Uint32 startState;
        bool power[PACMAN_POWER_STATE_TOTAL];
        Uint32 startPower[PACMAN_POWER_STATE_TOTAL];

        //Speed effect
        std::deque<Point> lastPoint;

        ///Playing value
        //Direction
        std::queue<Direction> direction;
        int speed;
        int dotEaten;
        int life;

        Point stand;

        ///Animation value
        bool animated;
        int sprite_val;
        int frame, frame_value;

        //queue function:
        void clearQueue();
};

#endif // PACMAN_H_
