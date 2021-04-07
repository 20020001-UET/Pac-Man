///Direction [Source]
#include "Direction.h"

bool checkOppositeDir(DIRECTION first, DIRECTION second)
{
    return ( ((vel_x[first] + vel_x[second]) == 0) && ((vel_y[first] + vel_y[second]) == 0) );
}
