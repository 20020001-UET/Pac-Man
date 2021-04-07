#include "GifRender.h"

#include "Engine.h"
#include "Texture.h"
#include <iostream>

GifRender::GifRender(std::string path, int x, int y, int _width, int _height, int _frame_count, int _frame_value)
{
    texture = Texture::load(path);
    width = _width;
    height = _height;
    frame_count = _frame_count;
    _frame_value = _frame_value;

    srcRect.resize(frame_count);
    int cnt = 0;
    for (int row = 0; row < 1; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            srcRect[cnt++] = {width*col, height*row,
                             width, height};
            if (cnt == frame_count)
                break;
        }
        if (cnt == frame_count)
            break;
    }

    tile = Point(x, y);
    setup();
}

void GifRender::render()
{
    Texture::draw(texture, srcRect[frame / frame_value], destRect);

    frame++;

    if (frame / frame_value >= frame_count)
        frame = 0;
}

void GifRender::free()
{
    SDL_DestroyTexture(texture);
    texture = NULL;

    srcRect.clear();
}

void GifRender::setup()
{
    screen = Point(tile.x*(Engine::getPixel()), tile.y*(Engine::getPixel()));

    destRect = {(int)(screen.x), (int)(screen.y), width, height};
}
