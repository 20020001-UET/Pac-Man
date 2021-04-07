///Entity [Header]
#ifndef ENITY_H_
#define ENITY_H_

///SDL libraries
#include <SDL.h>

///Project headers
#include "Point.h"

class Entity
{
    public:
        Entity(int _tileX, int _tileY, int _width, int _height);

        Point getTile();
        FPoint getScreen();

        void move(float x, float y);
        void teleport(int _tileX, int _tileY);
        void setScreenCenter(int x, int y);
        bool checkScreen();

    protected:
        Point tile;
        FPoint screen;

        int width, height;
        SDL_Rect srcRect, destRect;

    private:
        void setup();

};

#endif // ENITY_H_
