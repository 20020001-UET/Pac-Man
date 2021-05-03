///Unique Ghost [Header]
#ifndef UNIQUE_GHOST_H_
#define UNIQUE_GHOST_H_

///Include header
#include "Console.h"
#include "Entity.h"
#include "Graphic.h"
#include "Timer.h"
#include "Direction.h"
#include "Point.h"
#include <queue>
#include <deque>

///Unique Ghost constance value
const int UNIQUE_GHOST_SPEED = 2;
const int UNIQUE_GHOST_FRAME_VALUE = 4;

///Unique Ghost behavior
enum UNIQUE_GHOST_BEHAVIOR
{
    UNIQUE_GHOST_UNSET = -1,
    UNIQUE_GHOST_INIT,
    UNIQUE_GHOST_SHOW_UP,
    UNIQUE_GHOST_STAND,
    UNIQUE_GHOST_WAIT,
    UNIQUE_GHOST_CHASE,
    UNIQUE_GHOST_SCATTER,
    UNIQUE_GHOST_FRIGHTENED,
    UNIQUE_GHOST_BEING_EATEN,
    UNIQUE_GHOST_EATEN,
    UNIQUE_GHOST_REBORN,
    UNIQUE_GHOST_BLIND,
    UNIQUE_GHOST_FREEZING,
    UNIQUE_GHOST_LEAVE_GHOST_HOUSE,
    UNIQUE_GHOST_ENTER_GHOST_HOUSE,
    UNIQUE_GHOST_BEHAVIOR_TOTAL
};
const int UNIQUE_GHOST_BEHAVIOR_TIME[UNIQUE_GHOST_BEHAVIOR_TOTAL] = {0, 1000, 0, 0, 20000, 7000, 8300, 960, -1, 240, 4000, 5600, -1, -1};

///Unique Ghost mode
enum UNIQUE_GHOST_MODE
{
    UNIQUE_GHOST_NORMAL = 0,
    UNIQUE_GHOST_SPEED_UP_MODE,
    UNIQUE_GHOST_SLOW_DOWN_MODE,
    UNIQUE_GHOST_INVISIBLE_MODE,
    UNIQUE_GHOST_FRIGHTENED_MODE,
    UNIQUE_GHOST_BLIND_MODE,
    UNIQUE_GHOST_FREEZING_MODE,
    UNIQUE_GHOST_MODE_TOTAL
};
const int UNIQUE_GHOST_MODE_TIME[UNIQUE_GHOST_MODE_TOTAL] = {0, 2000, 400, 5200, 8300, 4000, 5600};
const int UNIQUE_GHOST_SPEED_SPEED_UP = 4;

///Unique Ghost class
class UniqueGhost:
    public Entity
{
    public:
        //Contructor:
        UniqueGhost(UNIQUE_GHOST_TYPE _unique_ghost_type, Point _tile = Point());

        //Destructor:
        ~UniqueGhost();

        ///function:
        //init:
        virtual void init(Graphic* _graphic, Timer* timer, Point _show_up, Point _start_point, Point _stand, Point _scatter);

        //loop:
        void loop();

        //render:
        void handleRender();
        void render();

        ///behavior function:
        //behavior:
        void setBehavior(const UNIQUE_GHOST_BEHAVIOR newBehavior);
        void initBehavior();
        void handleBehavior();
        void removeBehavior();

        UNIQUE_GHOST_BEHAVIOR getBehavior();

        ///mode function:
        //mode:
        void setMode(const UNIQUE_GHOST_MODE newMode);
        void initMode(const UNIQUE_GHOST_MODE mode);
        void handleMode();
        void removeMode(const int mode);

        bool isGhostMode(const UNIQUE_GHOST_MODE checkMode);

        //playing function:
        DIRECTION getCurDirection();
        void setDirection(const DIRECTION newDirection);
        void setStop(bool _stop = true);
        bool isStop() const;

        bool isOutGhostHouse();

        void setTarget(Point newTarget);
        Point getTarget();

        virtual void leaveGhostHouse();

        //get:
        Point getScatter();
        Point getStand();
        Point getStartPoint();

        UNIQUE_GHOST_TYPE getType();

        bool isShowedUp();

    protected:
        ///UniqueGhost type
        UNIQUE_GHOST_TYPE unique_ghost_type;

        ///Behavior
        std::queue<UNIQUE_GHOST_BEHAVIOR> curBehavior;
        std::queue<Uint32> startBehavior;

        ///Mode
        bool curMode[UNIQUE_GHOST_MODE_TOTAL];
        Uint32 startMode[UNIQUE_GHOST_MODE_TOTAL];

        //Speed effect
        std::deque<Point> lastPoint;

        ///Playing value
        Point show_up;
        Point target;
        Point start_point, scatter, stand;
        Direction direction;
        int speed;
        bool stop, showed_up;

        bool outGhostHouse;

        ///Animation value
        bool animated;
        int sprite_val, stand_val;
        int frame, frame_value;
};

#endif // UNIQUE_GHOST_H_
