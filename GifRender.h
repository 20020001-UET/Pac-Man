#ifndef GIF_RENDER_H_
#define GIF_RENDER_H_

#include <SDL.h>
#include <string>
#include <vector>
#include "Point.h"

class GifRender
{
    public:
        GifRender(std::string path, int x, int y, int _width, int _height, int _frame_count, int _frame_value);
        void render();
        void free();

    private:

        Point tile, screen;
        int width, height;
        int frame, frame_count, frame_value;
        SDL_Texture* texture;
        std::vector<SDL_Rect> srcRect;
        SDL_Rect destRect;

        void setup();
};

#endif // GIF_RENDER_H_
