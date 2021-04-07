#include "Button.h"

#include "Engine.h"
#include "Texture.h"
#include "Resources.h"

Button::Button(int _tileX, int _tileY, int _width, int _height, BUTTON _type)
{
    tile = Point(_tileX, _tileY);
    width = _width;
    height = _height;

    srcRect = {0, 0, width, height};

    setup();

    type = _type;
}

Point Button::getTile()
{
    return tile;
}

Point Button::getScreen()
{
    return screen;
}

void Button::setType(BUTTON _type)
{
    type= _type;
}

void Button::setTile(Point _tile)
{
    tile = Point(_tile);
    setup();
}

void Button::render()
{
    int sprite_val = type;
    srcRect = Resources::getSprite(MENU_VAL::BUTTON_TEXTURE, sprite_val);
    Texture::draw(Resources::getTexture(BUTTON_TEXTURE), srcRect, destRect);
}

void Button::setup()
{
    screen = Point(tile.x*(Engine::getPixel()), tile.y*(Engine::getPixel()));

    destRect = {(int)(screen.x), (int)(screen.y), width, height};
}
