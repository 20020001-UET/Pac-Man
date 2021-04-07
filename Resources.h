///Resources [Header]
#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <SDL.h>

#include "Console.h"

//Spiret Pixel
const int SPRITE_PIXEL = 50;

///Menu
///Menu frame
const int MENU_SPRITE_COUNT = 3;
const int MENU_WIDTH = 700;
const int MENU_HEIGHT = 850;

///Button
const int BUTTON_SPRITE_COUNT = 5;
const int BUTTON_WIDTH = SPRITE_PIXEL / 2 * 16;
const int BUTTON_HEIGHT = SPRITE_PIXEL / 2 * 3;
enum BUTTON_VAL
{
    BUTTON_START = 0,
    BUTTON_HOW_TO_PLAY,
    BUTTON_SETTING,
    BUTTON_ABOUT,
    BUTTON_EXIT
};

enum MENU_VAL
{
    MENU_TEXTURE = 0,
    HOW_TO_PLAY_TEXTURE,
    SETTING_TEXTURE,
    ABOUT_TEXTURE,
    BUTTON_TEXTURE
};

///Playing
///Pacman
const int PACMAN_SPRITE_COUNT = 12;
const int PACMAN_ANIMATION_FRAME = 3;
enum PACMAN_SPRITE_VAL
{
    PACMAN_UP = 0,
    PACMAN_DOWN = 3,
    PACMAN_LEFT = 6,
    PACMAN_RIGHT = 9
};

///Ghost
const int GHOST_SPRITE_COUNT = 10;
const int GHOST_ANIMATION_FRAME = 2;
enum GHOST_SPRITE_VAL
{
    GHOST_DEFAUT = 0,
    GHOST_UP = 2,
    GHOST_DOWN = 4,
    GHOST_LEFT = 6,
    GHOST_RIGHT = 8
};

///Dot
const int DOT_SPRITE_PIXEL = 25;
enum DOT_SPRITE_VAL
{
    SMALL_DOT = 0,
    BIG_DOT
};

///Object
enum OBJECT_VAL
{
    FRIGHTENED_GHOST = -2,
    EATEN_GHOST,
    PACMAN_SPRITE,
    BLINKY_SPIRTE,
    PINKY_SPRITE,
    INKY_SPRITE,
    CLYDE_SPRITE,
    DOT = 7
};

///Resource class
class Resources
{
    public:
        static void load();
        static void free();
        static SDL_Texture* getTexture(MENU_VAL value);
        static SDL_Texture* getTexture(OBJECT_VAL value);
        static SDL_Texture* getTextureLabyrinth();
        static SDL_Rect getSprite(MENU_VAL value, int spirte_val);
        static SDL_Rect getSprite(OBJECT_VAL value, int sprite_val);
        static SDL_Rect getSpriteLabyrinth();

    private:
        static Console console;
        ///Textures
        //Menu
        static SDL_Texture* menu;
        static SDL_Texture* how_to_play;
        static SDL_Texture* setting;
        static SDL_Texture* about;
        static SDL_Texture* button;

        //Playing
        static SDL_Texture* object;
        static SDL_Texture* labyrinth;
        static SDL_Texture* dot_texture;

        ///Sprites
        //Menu
        static SDL_Rect menu_sprite[MENU_SPRITE_COUNT];
        static SDL_Rect how_to_play_sprite;
        static SDL_Rect setting_sprite;
        static SDL_Rect about_sprite;
        static SDL_Rect button_sprite[BUTTON_SPRITE_COUNT];

        //Playing
        static SDL_Rect pacman[PACMAN_SPRITE_COUNT];
        static SDL_Rect frightened_ghost[GHOST_ANIMATION_FRAME*2];
        static SDL_Rect eaten_ghost[GHOST_SPRITE_COUNT];
        static SDL_Rect blinky[GHOST_SPRITE_COUNT];
        static SDL_Rect pinky[GHOST_SPRITE_COUNT];
        static SDL_Rect inky[GHOST_SPRITE_COUNT];
        static SDL_Rect clyde[GHOST_SPRITE_COUNT];
        static SDL_Rect labyrinth_sprite;
        static SDL_Rect smallDot, bigDot;

};

#endif // RESOURCES_H_
