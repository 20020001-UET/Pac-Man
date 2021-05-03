///Ghost [Header]
#ifndef GHOST_H_
#define GHOST_H_

///Include header
#include "Console.h"
#include "Entity.h"
#include "Graphic.h"
#include "Timer.h"
#include "Direction.h"
#include "Point.h"
#include <queue>

///Ghost constance value
const int GHOST_SPEED = 2;
const int GHOST_FRAME_VALUE = 4;

///Ghost type
enum GHOST_TYPE
{
    GHOST_BLINKY,
    GHOST_PINKY,
    GHOST_INKY,
    GHOST_CLYDE,
    GHOST_TYPE_TOTAL
};

///Ghost behavior
enum GHOST_BEHAVIOR
{
    GHOST_UNSET = -1,
    GHOST_INIT,
    GHOST_STAND,
    GHOST_CHASE,
    GHOST_SCATTER,
    GHOST_FRIGHTENED,
    GHOST_BEING_EATEN,
    GHOST_EATEN,
    GHOST_REBORN,
    GHOST_BLIND,
    GHOST_FREEZING,
    GHOST_LEAVE_GHOST_HOUSE,
    GHOST_ENTER_GHOST_HOUSE,
    GHOST_UPGRADE_UNIQUE,
    GHOST_BEHAVIOR_TOTAL
};
const int GHOST_BEHAVIOR_TIME[GHOST_BEHAVIOR_TOTAL] = {0, 0, 20000, 7000, 8300, 960, -1, 240, 4000, 5600, -1, -1, 3200};

///Ghost mode
enum GHOST_MODE
{
    GHOST_NORMAL = 0,
    GHOST_FRIGHTENED_MODE,
    GHOST_BLIND_MODE,
    GHOST_FREEZING_MODE,
    GHOST_MODE_TOTAL
};
const int GHOST_MODE_TIME[GHOST_MODE_TOTAL] = {0, 8300, 4000, 5600};

///Ghost class
class Ghost:
    public Entity
{
    public:
        //Contructor:
        Ghost(GHOST_TYPE _ghost_type, Point _tile = Point());

        //Destructor:
        ~Ghost();

        ///function:
        //init:
        virtual void init(Graphic* _graphic, Timer* timer, Point _start_point, Point _stand, Point _scatter, Point _upgrade);

        //loop:
        void loop();

        //render:
        void handleRender();
        void render();

        ///behavior function:
        //behavior:
        void setBehavior(const GHOST_BEHAVIOR newBehavior);
        void initBehavior();
        void handleBehavior();
        void removeBehavior();

        GHOST_BEHAVIOR getBehavior();

        ///mode function:
        //mode:
        void setMode(const GHOST_MODE newMode);
        void initMode(const GHOST_MODE mode);
        void handleMode();
        void removeMode(const int mode);

        bool isGhostMode(const GHOST_MODE checkMode);

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
        Point getUpgrade();

        GHOST_TYPE getType();

        bool isUpgraded();

    protected:
        ///Ghost type
        GHOST_TYPE ghost_type;

        ///Console
        Console* console;

        ///Behavior
        std::queue<GHOST_BEHAVIOR> curBehavior;
        std::queue<Uint32> startBehavior;

        ///Mode
        bool curMode[GHOST_MODE_TOTAL];
        Uint32 startMode[GHOST_MODE_TOTAL];

        ///Playing value
        Point target;
        Point start_point, scatter, stand, upgrade;
        Direction direction;
        int speed;
        bool stop, upgraded;

        bool outGhostHouse;

        ///Animation value
        bool animated;
        int sprite_val, stand_val;
        int frame, frame_value;
};

#endif // GHOST_H_
