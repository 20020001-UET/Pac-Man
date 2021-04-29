///Graphic [Header]
#ifndef GRAPHIC_H_
#define GRAPHIC_H_

///Include header
#include <SDL.h>
#include "Console.h"
#include "Texture.h"
#include "Resources.h"
#include "Point.h"

///Graphic class
class Graphic
{
    public:
        //Constructor:
        Graphic();

        //Destructor:
        ~Graphic();

        ///function:
        //init:
        bool init(SDL_Renderer* _renderer, const int IMG_flags = IMG_INIT_PNG);

        //clearscreen:
        void clearScreen(const Uint8 r = 0x00, const Uint8 g = 0x00, const Uint8 b = 0x00, const Uint8 a = 0xFF);

        //draw:
        void draw(const BACKGROUND_TYPE background_type, const SDL_Rect background_dest);
        void draw(const BUTTON_TYPE button_type, const bool clickable, const SDL_Rect button_dest);
        void draw(const SETTING_BUTTON_TYPE setting_button_type, const bool clickable, const int curState, const SDL_Rect setting_button_dest);
        void draw(const OBJECT_TYPE object_type, const int sprite_val, const SDL_Rect object_dest);
        void draw(const LABYRINTH_TYPE labyrinth_type, const SDL_Rect labyrinth_dest);
        void draw(const FRUIT_TYPE fruit_type, const int sprite_val, const SDL_Rect fruit_dest);

        //render text:
        void renderNumber(const NUMBER_TYPE number_type, const int number, const Point dest_point);
        void renderText(const std::string& text, const Point dest_point);
        void renderScore(const int sprite_val, const Point score_point);

        //set viewport:
        void setViewPort(SDL_Rect viewport);
        void unsetViewPort();

        //set texture alpha blending:
        void setTextureBlending(const RESOURCES_TYPE resources_type, SDL_BlendMode blending = SDL_BLENDMODE_BLEND);
        void setTextureAlpha(const RESOURCES_TYPE resources_type, Uint8 alpha = 0xBD);
        void unsetTextureBlending(const RESOURCES_TYPE resources_type);
        Uint8 getTextureAlpha(const RESOURCES_TYPE resources_type) const;

        //close:
        void close();

    private:
        ///Renderer
        SDL_Renderer* renderer;

        ///Console
        Console* console;

        ///Resources
        Resources* resources;

        ///Texture
        Texture* texture;

        ///System value
        int curAlpha[RESOURCES_TYPE_TOTAL];
};

#endif // GRAPHIC_H_
