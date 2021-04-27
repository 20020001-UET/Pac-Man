///Button [Source]
#include "Button.h"

///Include header

///Button class
//Constructor:
Button::Button(BUTTON_TYPE _type, Point _tile)
{
    graphic = NULL;
    type = _type;
    tile = _tile;
    screen = tile * RESOURCES_PIXEL;
    dest = {screen.x, screen.y, BUTTON_WIDTH, BUTTON_HEIGHT};
    clickable = false;
    return;
}

//Destructor:
Button::~Button()
{
    graphic = NULL;
    return;
}

///function:
//init:
void Button::init(Graphic* _graphic)
{
    graphic = _graphic;
    return;
}

//render:
void Button::render()
{
    graphic->draw(type, clickable, dest);
    return;
}

//set clickable:
void Button::setClick(bool _clickable)
{
    clickable = _clickable;
}
