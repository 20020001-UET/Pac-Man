///Ghost [Header]
#ifndef GHOST_H_
#define GHOST_H_

#include "Entity.h"
#include "Direction.h"
#include "Point.h"
#include "Resources.h"

const int GHOST_FRAME_VALUE = 5;
const float GHOST_SPEED = 1.25f;

enum GHOST_TYPE
{
    BLINKY = 0,
    PINKY = 1,
    INKY = 2,
    CLYDE = 3
};

enum BEHAVIOR
{
    CHASE = 0,
    SCATTER = 1,
    FRIGHTENED = 2,
    EATEN = 3
};

class Ghost :
    public Entity
{
    public:
        Ghost(int x, int y, int w, int h, GHOST_TYPE _type);
        void loop();
        void render();

        void setBehavior(BEHAVIOR bahavior);
        BEHAVIOR getBehavior();
        void setTarget(Point _target);
        Point getTarget();
        void setMoving(DIRECTION dir);
        DIRECTION getDir();
        void setStop(bool _stop);
        bool isStop();

    private:
        GHOST_TYPE type;
        DIRECTION cur_dir;
        BEHAVIOR cur_behavior;
        Point target;
        bool stop;
        int state_time;
        int frame, sprite_frame;
        int waitTime;

};

#endif // GHOST_H_
