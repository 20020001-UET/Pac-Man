///Texture [Header]
#ifndef TEXTURE_H_
#define TEXTURE_H_

///SDL libraries
#include <SDL.h>
#include <SDL_image.h>

///Project headers
#include <string>
#include "Console.h"

///Texture class
class Texture
{
    public:
        static void init(SDL_Renderer* _renderer);
        static SDL_Texture* load(std::string path);
        static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
        static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip);
        static void close();

    private:
        static SDL_Renderer* renderer;
        static Console* console;

};

#endif // TEXTURE_H_
