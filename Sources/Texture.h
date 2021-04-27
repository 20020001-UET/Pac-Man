///Texture [Header]
#ifndef TEXTURE_H_
#define TEXTURE_H_

///Include header
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Console.h"

///Texture class
class Texture
{
    public:
        //Constructor:
        Texture();

        //Destructor:
        ~Texture();

        ///function:
        //init:
        void init(SDL_Renderer* _renderer);

        //load:
        SDL_Texture* load(std::string path);

        //draw:
        void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
        void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip);

        //close:
        void close();

    private:
        ///Renderer
        SDL_Renderer* renderer;

        ///Console
        Console* console;

};

#endif // TEXTURE_H_

