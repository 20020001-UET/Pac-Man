#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <SDL.h>

enum BACKGROUND
{
    MAIN_MENU = 0,
    HOW_TO_PLAY_MENU,
    SETTING_MENU,
    ABOUT_MENU
};

class Background
{
    public:
        Background(BACKGROUND _type, bool _animated);
        void render();

        BACKGROUND getType();

    private:
        BACKGROUND type;

        int width, height;
        int frame;
        bool animated;
        SDL_Rect srcRect, destRect;
};

#endif // BACKGROUND_H_
