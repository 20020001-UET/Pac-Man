///Background [Source]
#include "Background.h"

///Include header

///Background class
//Constructor:
Background::Background(BACKGROUND_TYPE _type)
{
    graphic = NULL;
    type = _type;
    dest = {0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
    return;
}

//Destructor:
Background::~Background()
{
    graphic = NULL;
    return;
}

///function:
//init:
void Background::init(Graphic* _graphic)
{
    graphic = _graphic;
    return;
}

//render:
void Background::render()
{
    graphic->draw(type, dest);
    return;
}
