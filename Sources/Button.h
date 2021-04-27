///Button [Header]
#ifndef BUTTON_H_
#define BUTTON_H_

///Include header
#include "Graphic.h"
#include "Point.h"

///Button class
class Button
{
    public:
        //Constructor:
        Button(BUTTON_TYPE _type, Point _tile);

        //Destructor:
        ~Button();

        ///function:
        //init:
        void init(Graphic* _graphic);

        //render();
        void render();

        //set clickable:
        void setClick(bool _cliclable);

    private:
        ///Graphic
        Graphic* graphic;

        ///Button type
        BUTTON_TYPE type;

        //clickable:
        bool clickable;

        //Position:
        Point tile, screen;

        //destination:
        SDL_Rect dest;
};

#endif // BUTTON_H_
