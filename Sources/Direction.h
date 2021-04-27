///Direction [Header]
#ifndef DIRECTION_H_
#define DIRECTION_H_

///Include header
#include "Point.h"

///Direction type
enum DIRECTION
{
    UNSET_DIRECTION = 0,
    UP,
    RIGHT,
    DOWN,
    LEFT,
    DIRECTION_TOTAL
};

///Direction value
const DIRECTION DIRECTION_AT[DIRECTION_TOTAL] = {UNSET_DIRECTION, UP, RIGHT, DOWN, LEFT};
const Point DIRECTION_VALUE[DIRECTION_TOTAL] = { Point(0, 0), Point(0, -1), Point(1, 0), Point(0, 1), Point(-1, 0) };

///Direction struct
struct Direction
{
    //Constructor:
    Direction(DIRECTION _type = UNSET_DIRECTION);

    //Destructor:
    ~Direction();

    ///function:
    bool operator==(const Direction& another) const;
    Point vel() const;
    bool against(const Direction& another) const;

    ///Direction
    DIRECTION type;

};

bool checkOpposite(DIRECTION first, DIRECTION second);
DIRECTION opposite(DIRECTION another);

#endif // DIRECTION_H_
