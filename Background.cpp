#include "Background.h"

#include "Engine.h"
#include "Texture.h"
#include "Resources.h"

Background::Background(BACKGROUND _type, bool _animated)
{
    width = MENU_WIDTH;
    height = MENU_HEIGHT;

    srcRect = destRect = {0, 0, width, height};

    type = _type;
    frame = 0;
    animated = _animated;
}

void Background::render()
{
    MENU_VAL menu_val;

    switch (type)
    {
        case MAIN_MENU: menu_val = MENU_VAL::MENU_TEXTURE; break;
        case HOW_TO_PLAY_MENU: menu_val = MENU_VAL::HOW_TO_PLAY_TEXTURE; break;
        case SETTING_MENU: menu_val = MENU_VAL::SETTING_TEXTURE; break;
        case ABOUT_MENU: menu_val = MENU_VAL::ABOUT_TEXTURE; break;
        default: break;
    }

    if (animated)
    {
        int sprite_val = frame / 5;

        srcRect = Resources::getSprite(menu_val, sprite_val);
        Texture::draw(Resources::getTexture(menu_val), srcRect, destRect);

        frame++;

        if (frame / 5 >= 3)
            frame = 0;

        return;
    }

    srcRect = Resources::getSprite(menu_val, 0);
    Texture::draw(Resources::getTexture(menu_val), srcRect, destRect);

    return;
}
