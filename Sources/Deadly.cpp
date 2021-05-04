///Deadly [Source]
#include "Deadly.h"

///Include header

///Deadly class
//Contructor:
Deadly::Deadly() : UniqueGhost(UNIQUE_GHOST_DEADLY)
{
    lastPoint.clear();
    return;
}

//Destructor:
Deadly::~Deadly()
{
    graphic = NULL;
    timer = NULL;
    lastPoint.clear();
    return;
}

///function:
//init:
void Deadly::init(Graphic* _graphic, Timer* _timer, Point _show_up, Point _start_point, Point _stand, Point _scatter)
{
    graphic = _graphic;
    timer = _timer;
    sprite_val = frame = 0;
    frame_value = UNIQUE_GHOST_FRAME_VALUE;

    direction = UNSET_DIRECTION;
    show_up = _show_up;
    start_point = _start_point;
    stand = _stand;
    scatter = _scatter;

    showed_up = false;

    stand_val = GHOST_DOWN;

    lastPoint.clear();

    setMode(UNIQUE_GHOST_NORMAL);

    setTile(stand);
    update();

    return;
}

void Deadly::leaveGhostHouse()
{
    if (tile == start_point)
    {
        setTile(start_point);
    }

    return;
}
