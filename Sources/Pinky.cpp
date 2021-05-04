///Pinky [Source]
#include "Pinky.h"

///Include header

///Pinky class
//Contructor:
Pinky::Pinky() : Ghost(GHOST_PINKY)
{
    return;
}

//Destructor:
Pinky::~Pinky()
{
    graphic = NULL;
    timer = NULL;
    return;
}

///function:
//init:
void Pinky::init(Graphic* _graphic, Timer* _timer, Point _start_point, Point _stand, Point _scatter, Point _upgrade)
{
    graphic = _graphic;
    timer = _timer;
    sprite_val = frame = 0;
    frame_value = GHOST_FRAME_VALUE;

    direction = UNSET_DIRECTION;
    start_point = _start_point;
    stand = _stand;
    scatter = _scatter;
    upgrade = _upgrade;

    upgraded = false;

    stand_val = GHOST_LEFT;

    setTile(stand);
    update();

    return;
}
