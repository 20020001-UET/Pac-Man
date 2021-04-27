///Texture [Source]
#include "Texture.h"

///Texture class
//Constructor:
Texture::Texture()
{
    renderer = NULL;
    console = NULL;
    return;
}

//Destructor:
Texture::~Texture()
{
    renderer = NULL;
    delete console;
    console = NULL;
    return;
}

///function:
//init:
void Texture::init(SDL_Renderer* _renderer)
{
    console = new Console("Texture");

    renderer = _renderer;

    console->writeLine("Initialized texture syb-system.");
}

//load:
SDL_Texture* Texture::load(std::string path)
{
    console->writeLine("Loading file: " + path);
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());

    SDL_Texture* tmpTexture = NULL;

    if (tmpSurface == NULL)
    {
        //Error:
        console->logError("Can't load surface from file: " + path, ERROR_FLAGS::IMG_ERROR);
        return tmpTexture;
    }

    tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    if (tmpTexture == NULL)
    {
        //Error:
        console->logError("Can't create texture from surface: " + path, ERROR_FLAGS::IMG_ERROR);
    }

    SDL_FreeSurface(tmpSurface);
    tmpSurface = NULL;

    return tmpTexture;
}

//draw:
void Texture::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

void Texture::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, NULL, flip);
}

//close:
void Texture::close()
{
    console->writeLine("Closing texture syb-system. . .");
    return;
}
