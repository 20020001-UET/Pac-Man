///Speedy [Source]
#include "Speedy.h"

///Include header

///Speedy class
//Contructor:
Speedy::Speedy() : UniqueGhost(UNIQUE_GHOST_SPEEDY)
{
    return;
}

//Destructor:
Speedy::~Speedy()
{
    graphic = NULL;
    timer = NULL;
    return;
}

///function:
//init:
void Speedy::init(Graphic* _graphic, Timer* _timer, Point _show_up, Point _start_point, Point _stand, Point _scatter)
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

    stand_val = GHOST_LEFT;

    lastPoint.clear();

    setMode(UNIQUE_GHOST_NORMAL);

    setTile(stand);
    update();

    return;
}
