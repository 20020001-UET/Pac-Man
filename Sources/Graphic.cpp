///Graphic [Source]
#include "Graphic.h"

///Include header

///Graphic class
//Constructor:
Graphic::Graphic()
{
    renderer = NULL;

    console = new Console("Graphic");

    texture = new Texture();

    resources = new Resources();
    return;
}

//Destructor:
Graphic::~Graphic()
{
    renderer = NULL;

    delete console;
    console = NULL;
    delete resources;
    resources = NULL;
    delete texture;
    texture = NULL;
    return;
}

///function:
//init:
bool Graphic::init(SDL_Renderer* _renderer, const int IMG_flags)
{
    renderer = _renderer;

    //Initialize SDL_image
    if (IMG_Init(IMG_flags) != IMG_flags)
    {
        //Error:
        console->logError("SDL_image could not initialize!", ERROR_FLAGS::IMG_ERROR);
        return false;
    }
    console->writeLine("Initialized IMG: PNG");

    texture->init(renderer);
    resources->init(texture);

    for (int index = 0; index < RESOURCES_TYPE_TOTAL; index++)
        curAlpha[index] = 0xFF;

    //Clear screen
    //Black background
    clearScreen();

    console->writeLine("Initialized Graphic");
    return true;
}

//clear screen:
void Graphic::clearScreen(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
    unsetViewPort();
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
    return;
}

//draw:
void Graphic::draw(const BACKGROUND_TYPE background_type, const SDL_Rect background_dest)
{
    texture->draw(resources->getTexture(RESOURCES_TYPE::BACKGROUND),
                  resources->getSprite(background_type),
                  background_dest);
    return;
}

void Graphic::draw(const BUTTON_TYPE button_type, const bool clickable, const SDL_Rect button_dest)
{
    texture->draw(resources->getTexture(RESOURCES_TYPE::BUTTON),
                  resources->getSprite(button_type, clickable),
                  button_dest);
    return;
}

void Graphic::draw(const SETTING_BUTTON_TYPE setting_button_type, const bool clickable, const int curState, const SDL_Rect setting_button_dest)
{
    texture->draw(resources->getTexture(RESOURCES_TYPE::SETTING_BUTTON),
                  resources->getSprite(setting_button_type, clickable, curState),
                  setting_button_dest);
    return;
}

void Graphic::draw(const OBJECT_TYPE object_type, const int sprite_val, const SDL_Rect object_dest)
{
    RESOURCES_TYPE resources_type = OBJECT;
    if (object_type == OBJECT_PACMAN || object_type == OBJECT_PACMAN_MS || object_type == OBJECT_PACMAN_ANDROID)
        resources_type = PACMAN;

    SDL_Texture* tmpTexture = resources->getTexture(resources_type);

    texture->draw(tmpTexture,
                  resources->getSprite(object_type, sprite_val),
                  object_dest);
    return;
}

void Graphic::draw(const LABYRINTH_TYPE labyrinth_type, const SDL_Rect labyrinth_dest)
{
    texture->draw(resources->getTexture(RESOURCES_TYPE::LABYRINTH),
                  resources->getSprite(labyrinth_type),
                  labyrinth_dest);
    return;
}

void Graphic::draw(const FRUIT_TYPE fruit_type, const int sprite_val, const SDL_Rect fruit_dest)
{
    texture->draw(resources->getTexture(RESOURCES_TYPE::FRUIT),
                  resources->getSprite(fruit_type, sprite_val),
                  fruit_dest);
    return;
}

void Graphic::renderNumber(const NUMBER_TYPE number_type, const int number, const Point dest_point)
{
    SDL_Rect dest = {dest_point.x, dest_point.y, NUMBER_WIDTH, NUMBER_HEIGHT};
    texture->draw(resources->getTexture(RESOURCES_TYPE::NUMBER),
                  resources->getSprite(number_type, number),
                  dest);
    return;
}

void Graphic::renderNumber(const NUMBER_TYPE number_type, const std::string number, const Point dest_point)
{
    Point dest;

    dest = dest_point;
    for (size_t index = 0; index < number.size(); index++)
    {
        int num = (int)(number[index] - '0');
        renderNumber(number_type, num, dest);
        dest.x += RESOURCES_PIXEL;
    }

    return;
}

void Graphic::renderScore(const int sprite_val, const Point score_dest)
{
    SDL_Rect dest = {score_dest.x, score_dest.y, SCORE_WIDTH, SCORE_HEIGHT};
    texture->draw(resources->getTexture(RESOURCES_TYPE::SCORE),
                  resources->getSprite(SCORE_DEFAULT, sprite_val),
                  dest);
    return;
}

//set viewport:
void Graphic::setViewPort(SDL_Rect viewport)
{
    if (SDL_RenderSetViewport(renderer, &viewport) != 0)
    {
        //Error:
        console->logError("Can't set viewport ", ERROR_FLAGS::SDL_ERROR);
    }
    return;
}

void Graphic::unsetViewPort()
{
    if (SDL_RenderSetViewport(renderer, NULL) != 0)
    {
        //Error:
        console->logError("Can't unset viewport ", ERROR_FLAGS::SDL_ERROR);
    }
    return;
}

//set texture alpha blending:
void Graphic::setTextureBlending(const RESOURCES_TYPE resources_type, SDL_BlendMode blending)
{
    SDL_Texture* tmpTexture = resources->getTexture(resources_type);
    SDL_SetTextureBlendMode(tmpTexture, blending);
    return;
}

void Graphic::setTextureAlpha(const RESOURCES_TYPE resources_type, Uint8 alpha)
{
    SDL_Texture* tmpTexture = resources->getTexture(resources_type);
    curAlpha[resources_type] = alpha;
    SDL_SetTextureAlphaMod(tmpTexture, curAlpha[resources_type]);
    return;
}

void Graphic::unsetTextureBlending(const RESOURCES_TYPE resources_type)
{
    SDL_Texture* tmpTexture = resources->getTexture(resources_type);
    curAlpha[resources_type] = 0xFF;
    SDL_SetTextureAlphaMod(tmpTexture, curAlpha[resources_type]);
    return;
}

Uint8 Graphic::getTextureAlpha(const RESOURCES_TYPE resources_type) const
{
    return curAlpha[resources_type];
}

//close:
void Graphic::close()
{
    console->writeLine("Closing Graphic. . .");

    resources->close();

    texture->close();

    //Quit SDL_image
    IMG_Quit();

    return;
}
