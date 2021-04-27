///SettingButton [Header]
#ifndef SETTING_BUTTON_H_
#define SETTING_BUTTON_H_

///Include header
#include "Graphic.h"
#include "Point.h"

///SettingButton class
class SettingButton
{
    public:
        //Constructor:
        SettingButton(SETTING_BUTTON_TYPE _type, Point _tile);

        //Destructor:
        ~SettingButton();

        ///function:
        //init:
        void init(Graphic* _graphic);

        //render();
        void render();

        //set clickable:
        void setClick(bool _cliclable);

        //update state:
        void setState(int _curState);
        void updateState(int change);

        //get state:
        int getState();

    private:
        ///Graphic
        Graphic* graphic;

        ///SettingButton type
        SETTING_BUTTON_TYPE type;

        //clickable:
        bool clickable;

        //button state:
        int curState;

        //Position:
        Point tile, screen;

        //destination:
        SDL_Rect dest;
};

#endif // SETTING_BUTTON_H_
