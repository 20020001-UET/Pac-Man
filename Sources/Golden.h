///Golden [Header]
#ifndef GOLDEN_H_
#define GOLDEN_H_

#include "Entity.h"
#include "Graphic.h"
#include "Timer.h"
#include "Direction.h"
#include "Point.h"
#include <deque>
#include <random>

///Golden State
enum GOLDEN_STATE_TYPE
{
    GOLDEN_INIT_STATE = 0,
    GOLDEN_SHOW_UP_STATE,
    GOLDEN_RUNNING_STATE,
    GOLDEN_DEATH_STATE,
    GOLDEN_STATE_TOTAL
};

struct GOLDEN_STATE
{
    GOLDEN_STATE() :
        type(GOLDEN_INIT_STATE), start(0), isInit(false) {};
    GOLDEN_STATE(GOLDEN_STATE_TYPE _type, Uint32 _start) :
        type(_type), start(_start), isInit(false) {};

    GOLDEN_STATE_TYPE type;
    Uint32 start;
    bool isInit;
};

///Golden Mode
enum GOLDEN_MODE_TYPE
{
    GOLDEN_NORMAL_MODE = 0,
    GOLDEN_SPEED_UP_MODE,
    GOLDEN_INVISIBLE_MODE,
    GOLDEN_EXHAUSTED_MODE,
    GOLDEN_MODE_TOTAL
};

const int GOLDEN_MODE_TIME[GOLDEN_MODE_TOTAL] = {0, 4000, 7200, 6400};

///Golden Damage
enum GOLDEN_DAMAGE_TYPE
{
    GOLDEN_DAMAGE_HIT = 0,
    GOLDEN_DAMAGE_SOUL_GHOST,
    GOLDEN_DAMAGE_DOT,
    GOLDEN_DAMAGE_BIG_DOT,
    GOLDEN_DAMAGE_TYPE_TOTAL
};

const Uint16 GOLDEN_DAMAGE_VALUE[GOLDEN_DAMAGE_TYPE_TOTAL] = {7680, 19200, 1, 5};

///Health Point
const Uint16 GOLDEN_HP = 38400;

///Speed
const int GOLDEN_SPEED = 2;
const int GOLDEN_SPEED_UP_SPEED = 4;
const int GOLDEN_EXHAUSTED_SPEED = 1;

///Animation value
const int GOLDEN_FRAME_VALUE = 4;
const int GOLDEN_DEATH_FRAME_VALUE = 18;
const int GOLDEN_SPEED_UP_FRAME_VALUE = 2;
const int GOLDEN_EXHAUSTED_FRAME_VALUE = 8;

///Generate value
enum DOT_GENERATE_VALUE
{
    NORMAL_DOT_GENERATE = 0,
    POWER_DOT_GENERATE,
    SPEED_DOT_GENERATE,
    INVISIBLE_DOT_GENERATE,
    FREEZE_DOT_GENERATE,
    DOT_GENERATE_VALUE_TOTAL
};

const Uint32 GENERATE_MAX = 1000000;
//const Uint32 GENERATE_FLAG = 96990;
const Uint32 GENERATE_FLAG = 90690;

enum SOUL_VALUE
{
    SOUL_BLINKY = 0,
    SOUL_PINKY,
    SOUL_INKY,
    SOUL_CLYDE,
    SOUL_TOTAL
};

class Golden:
    public Entity
{
    public:
        //Constructor:
        Golden(Point _tile = Point());

        //Destructor:
        ~Golden();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* timer, Point _start_point, Point _show_up);

        //loop:
        void loop();

        //render:
        void handleRender();
        void render();

        ///state:
        void setState(const GOLDEN_STATE_TYPE newState);
        void initState(const GOLDEN_STATE_TYPE state);
        void handleState();
        void removeState(const GOLDEN_STATE_TYPE state);

        GOLDEN_STATE_TYPE getState();

        ///mode:
        void setMode(const GOLDEN_MODE_TYPE newMode);
        void initMode(const GOLDEN_MODE_TYPE mode);
        void handleMode();
        void removeMode(const int mode);

        bool isGoldenMode(const GOLDEN_MODE_TYPE checkMode);

        ///Playing function:
        DIRECTION getCurDirection();
        void setDirection(const DIRECTION newDirection);
        void setStop(bool _stop = true);
        bool isStop();

        int dotGenerate();
        int soulGenerate();

        void setTarget(Point newTarget);
        Point getTarget();

        void setDanger(bool _danger = true);
        bool isDanger();

        bool isShowedUp();
        bool isDead();

        Uint16 getHP();
        void takeDamage(GOLDEN_DAMAGE_TYPE damage_type);

        Point getStartPoint();

    private:
        ///state
        GOLDEN_STATE curState;

        ///mode
        bool curMode[GOLDEN_MODE_TOTAL];
        Uint32 startMode[GOLDEN_MODE_TOTAL];

        ///Playing value
        Point target;
        Point start_point, show_up;

        Direction direction;
        int speed;
        int speed_up_time;
        bool stop, showed_up, dead, danger;

        Uint16 health_point;
        bool soul[SOUL_TOTAL];
        int soul_remain, cur_soul;

        ///Animation value
        bool animated;
        int sprite_val;
        int frame, frame_value;

        //Speed effect
        std::deque<Point> lastPoint;

};

#endif // GOLDEN_H_
