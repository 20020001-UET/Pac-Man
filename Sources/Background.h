///Background [Header]
#ifndef BACKGROUND_H_
#define BACKGROUND_H_

///Include header
#include "Graphic.h"

///Background class
class Background
{
    public:
        //Constructor:
        Background(BACKGROUND_TYPE _type);

        //Destructor:
        ~Background();

        ///function:
        //init:
        void init(Graphic* _graphic);

        //render:
        void render();

    private:
        ///Graphic
        Graphic* graphic;

        ///Background type
        BACKGROUND_TYPE type;

        //destination:
        SDL_Rect dest;
};

#endif // BACKGROUND_H_
