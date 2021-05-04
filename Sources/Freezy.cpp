///Freezy [Source]
#include "Freezy.h"

///Include header

///Freezy class
//Contructor:
Freezy::Freezy() : UniqueGhost(UNIQUE_GHOST_FREEZY)
{
    lastPoint.clear();
    return;
}

//Destructor:
Freezy::~Freezy()
{
    lastPoint.clear();
    graphic = NULL;
    timer = NULL;
    return;
}

///function:
//init:
void Freezy::init(Graphic* _graphic, Timer* _timer, Point _show_up, Point _start_point, Point _stand, Point _scatter)
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

    stand_val = GHOST_RIGHT;

    lastPoint.clear();

    setMode(UNIQUE_GHOST_NORMAL);

    setTile(stand);
    update();

    return;
}
