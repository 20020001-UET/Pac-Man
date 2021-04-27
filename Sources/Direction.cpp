///Direction [Source]
#include "Direction.h"

///Include header

///Direction struct
//Constructor:
Direction::Direction(DIRECTION _type)
{
    type = _type;
    return;
}

//Destructor:
Direction::~Direction()
{
    return;
}

///function:
bool Direction::operator==(const Direction& another) const
{
    return (type == another.type);
}

Point Direction::vel() const
{
    return DIRECTION_VALUE[type];
}

bool Direction::against(const Direction& another) const
{
    return ((vel() + another.vel()) == Point());
}

bool checkOpposite(DIRECTION first, DIRECTION second)
{
    return ((DIRECTION_VALUE[first] + DIRECTION_VALUE[second]) == Point());
}

DIRECTION opposite(DIRECTION another)
{
    if (another == UP)
        return DOWN;
    if (another == RIGHT)
        return LEFT;
    if (another == DOWN)
        return UP;
    if (another == LEFT)
        return RIGHT;
    return UNSET_DIRECTION;
}
