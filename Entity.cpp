///Entity [Source]
#include "Entity.h"

#include "Engine.h"
#include <cmath>

///Entity class
Entity::Entity(int _tileX, int _tileY, int _width, int _height)
{
    tile = Point(_tileX, _tileY);

    screen = FPoint(tile.x*(Engine::getPixel()), tile.y*(Engine::getPixel()));

    width = _width;
    height = _height;

    srcRect = {0, 0, width, height};

    setup();
}

Point Entity::getTile()
{
    return tile;
}

FPoint Entity::getScreen()
{
    return screen;
}

bool Entity::checkScreen()
{
    return (((int)(screen.x) % Engine::getPixel() == 0) && ((int)(screen.y) % Engine::getPixel() == 0));
}

void Entity::move(float x, float y)
{
    screen.x += x;
    screen.y += y;

    if (checkScreen())
    {
        tile.x = (int) round(screen.x / Engine::getPixel());
        tile.y = (int) round(screen.y / Engine::getPixel());
    }

    destRect = {(int)(screen.x) - 12, (int)(screen.y) - 12, width, height};
}

void Entity::teleport(int _tileX, int _tileY)
{
    tile = Point(_tileX, _tileY);

    setup();
}

void Entity::setScreenCenter(int x, int y)
{
    screen.x = x*Engine::getPixel() - 10;
    screen.y = y*Engine::getPixel();

    destRect = {(int)(screen.x) - 15, (int)(screen.y) - 12, width, height};
}

void Entity::setup()
{
    screen = FPoint(tile.x*(Engine::getPixel()), tile.y*(Engine::getPixel()));

    destRect = {(int)(screen.x) - 12, (int)(screen.y) - 12, width, height};
}
