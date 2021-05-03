///Mystery [Header]
#ifndef MYSTERY_H_
#define MYSTERY_H_

///Include header
#include "Console.h"
#include "Entity.h"
#include "Graphic.h"
#include "Timer.h"
#include "Direction.h"
#include "Point.h"

///Mystery constance value
const int MYSTERY_SPEED = 1;
const int MYSTERY_FRAME_VALUE = 8;

///Mystery state
enum MYSTERY_STATE
{
    MYSTERY_INIT,
    MYSTERY_STAND,
    MYSTERY_MOVING,
    MYSTERY_MOVING_TO_SPEECH,
    MYSTERY_MOVING_TO_SHOW_UP,
    MYSTERY_WAITING,
    MYSTERY_WAITING_TO_SPEECH,
    MYSTERY_WAITING_TO_SHOW_UP,
    MYSTERY_SPEECH_UPGRADE,
    MYSTERY_SPEECH_SHOW_UP,
    MYSTERY_UPGRADE,
    MYSTERY_RETURNING,
    MYSTERY_STATE_TOTAL
};

///Mystery state time
const int MYSTERY_STATE_TIME[MYSTERY_STATE_TOTAL] = {0, 0, 0, 0, 0, 1200, 0, 7200, 5200, 5200, 0, 0};

///Mystery class
class Mystery:
    public Entity
{
    public:
        //Constructor:
        Mystery(Point _tile = Point());

        //Destructor:
        ~Mystery();

        ///main function:
        //init
        void init(Graphic* _graphic, Timer* timer, Point _stand, Point _wait, Point _speech, Point _upgrade);
        void setSpeechPoint(Point _speech_upgrade, Point _speech_show_up);

        //loop:
        void loop();

        //render:
        void render();

        ///state function:
        void setState(const MYSTERY_STATE newState);
        void initState();
        void handleState();

        MYSTERY_STATE getState();

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
        Point getSpeech();
        Point getUpgrade();

    private:
        ///Console
        Console* console;

        ///State
        MYSTERY_STATE curState;
        Uint32 startState;
        int curSpeech;

        ///Playing value
        Point target;
        Point speech_upgrade, speech_show_up;
        Point stand, wait, speech, upgrade;
        Direction direction;
        int speed;
        bool stop;

        bool outOfStandPosition;

        ///Animation value
        bool animated;
        int sprite_val;
        int frame, frame_value;
};

#endif // MYSTERY_H_
