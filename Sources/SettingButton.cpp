///SettingButton [Source]
#include "SettingButton.h"

///Include header

///SettingButton class
//Constructor:
SettingButton::SettingButton(SETTING_BUTTON_TYPE _type, Point _tile)
{
    graphic = NULL;
    type = _type;
    tile = _tile;
    screen = tile * RESOURCES_PIXEL;
    dest = {screen.x, screen.y, SETTING_BUTTON_WIDTH, SETTING_BUTTON_HEIGHT[type]};
    clickable = false;
    curState = 0;
    return;
}

//Destructor:
SettingButton::~SettingButton()
{
    graphic = NULL;
    return;
}

///function:
//init:
void SettingButton::init(Graphic* _graphic)
{
    graphic = _graphic;
    return;
}

//render:
void SettingButton::render()
{
    graphic->draw(type, clickable, curState, dest);
    return;
}

//set clickable:
void SettingButton::setClick(bool _clickable)
{
    clickable = _clickable;
}

//update state:
void SettingButton::setState(int _curState)
{
    curState = _curState;
    return;
}

void SettingButton::updateState(int change)
{
    if ((0 <= (curState + change)) && ((curState + change) <= (SETTING_BUTTON_TYPE_SPRITE[type] - 1)))
        curState += change;
    return;
}

//get state:
int SettingButton::getState()
{
    return curState;
}
