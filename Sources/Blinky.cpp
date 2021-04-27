///Blinky [Source]
#include "Blinky.h"

///Include header

///Blinky class
//Contructor:
Blinky::Blinky() : Ghost(GHOST_BLINKY)
{
    return;
}

//Destructor:
Blinky::~Blinky()
{
    graphic = NULL;
    timer = NULL;
    return;
}

///function:
//init:
void Blinky::init(Graphic* _graphic, Timer* _timer, Point _start_point, Point _stand, Point _scatter)
{
    graphic = _graphic;
    timer = _timer;
    sprite_val = frame = 0;
    frame_value = GHOST_FRAME_VALUE;

    direction = UNSET_DIRECTION;
    start_point = _start_point;
    stand = _stand;
    scatter = _scatter;

    setTile(stand);
    update();

    return;
}

void Blinky::leaveGhostHouse()
{
    if (tile == start_point)
    {
        setTile(start_point);
    }

    return;
}
