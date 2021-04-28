///Fruit [Header]
#ifndef FRUIT_H_
#define FRUIT_H_

///Include header
#include "Console.h"
#include "Entity.h"
#include "Graphic.h"
#include "Timer.h"
#include "Direction.h"
#include "Point.h"

///Fruit constance value
const int FRUIT_SPEED = 2;
const int FRUIT_FRAME_VALUE = 4;
const int FRUIT_WAIT_TIME = 5600;

const FRUIT_TYPE FRUIT_TYPE_AT[FRUIT_TYPE_TOTAL] = {FRUIT_CHERRY, FRUIT_STAWBERRY, FRUIT_ORANGE, FRUIT_APPLE, FRUIT_MELON, FRUIT_BANANA, FRUIT_WATER_MELON, FRUIT_MANGO };

///Fruit state
enum FRUIT_STATE
{
    FRUIT_INIT,
    FRUIT_STAND,
    FRUIT_MOVING,
    FRUIT_WAITING,
    FRUIT_RETURNING,
    FRUIT_STATE_TOTAL
};

///Fruit class
class Fruit:
    public Entity
{
    public:
        //Constructor:
        Fruit(Point _tile = Point());

        //Destructor:
        ~Fruit();

        ///main function:
        //init
        void init(Graphic* _graphic, Timer* timer, Point _stand, Point _wait);

        void setType(const int level);
        void setType(const FRUIT_TYPE new_fruit_type);

        //loop:
        void loop();

        //render:
        void render();

        ///state function:
        void setState(const FRUIT_STATE newState);
        void initState();
        void handleState();

        FRUIT_STATE getState();

        //playing function:
        DIRECTION getCurDirection();
        void setDirection(const DIRECTION newDirection);
        void setStop(bool _stop = true);
        bool isStop() const;

        bool isOutOfStandPosition();

        void setTarget(Point newTarget);
        Point getTarget();

        //point:
        Point getStand();
        Point getWait();

    private:
        ///Fruit type
        FRUIT_TYPE fruit_type;

        ///Console
        Console* console;

        ///State
        FRUIT_STATE curState;
        Uint32 startState;

        ///Playing value
        Point target;
        Point stand, wait;
        Direction direction;
        int speed;
        bool stop;

        bool outOfStandPosition;

        ///Animation value
        bool animated;
        int sprite_val;
        int frame, frame_value;
};

#endif // FRUIT_H_
