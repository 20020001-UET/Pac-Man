#ifndef BUTTON_H_
#define BUTTON_H_

#include <SDL.h>
#include "Point.h"

enum BUTTON
{
    START = 0,
    HOW_TO_PLAY,
    SETTING,
    ABOUT,
    EXIT,
    RESUME,
    BUTTON_COUNT
};

const BUTTON button_at[BUTTON_COUNT] = {START, HOW_TO_PLAY, SETTING, ABOUT, EXIT, RESUME};

class Button
{
    public:
        Button(int _tileX, int _tileY, int _width, int _height, BUTTON _type);
        Point getTile();
        Point getScreen();

        void setType(BUTTON _type);
        void setTile(Point _tile);
        void render();

    private:
        Point tile;
        Point screen;

        BUTTON type;

        int width, height;
        SDL_Rect srcRect, destRect;

        void setup();

};

#endif // BUTTON_H_
