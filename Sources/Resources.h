///Resources [Header]
#ifndef RESOURCES_H_
#define RESOURCES_H_

///Include header
#include <SDL.h>
#include "Console.h"
#include "Texture.h"

///Viewport
const SDL_Rect MAIN_VIEWPORT = {4*3, 4*3, 224*3, 296*3};
const SDL_Rect PLAYING_VIEWPORT = {4*3, 28*3, 224*3, 248*3};
const SDL_Rect GAME_STATUS_VIEWPORT ={4*3, 4*3, 224*3, 296*3};

///Resouces
const int RESOURCES_PIXEL = 8*3;
enum RESOURCES_TYPE
{
    BACKGROUND = 0,
    BUTTON,
    SETTING_BUTTON,
    PACMAN,
    OBJECT,
    LABYRINTH,
    NUMBER,
    ALPHABET,
    RESOURCES_TYPE_TOTAL
};

///Backgound
const int BACKGROUND_WIDTH = 224*3;
const int BACKGROUND_HEIGHT = 296*3;
enum BACKGROUND_TYPE
{
    BACKGROUND_MENU = 0,
    BACKGROUND_PLAYING,
    BACKGROUND_HOW_TO_PLAY,
    BACKGROUND_SETTING,
    BACKGROUND_HIGHSCORE,
    BACKGROUND_ABOUT,
    BACKGROUND_RESUME,
    BACKGROUND_SAVE_SETTING,
    BACKGROUND_EXIT_GAME,
    BACKGROUND_TYPE_TOTAL
};

///Button
const int BUTTON_WIDTH = 112*3;
const int BUTTON_HEIGHT = 24*3;
const int BUTTON_SPRITE_TOTAL = 2;
enum BUTTON_TYPE
{
    BUTTON_START = 0,
    BUTTON_HOW_TO_PLAY,
    BUTTON_SETTING,
    BUTTON_HIGHSCORE,
    BUTTON_ABOUT,
    BUTTON_RESUME,
    BUTTON_EXIT,
    BUTTON_YES,
    BUTTON_NO,
    BUTTON_TYPE_TOTAL
};

///Setting Button
enum SETTING_BUTTON_TYPE
{
    SETTING_BUTTON_VOLUME_MUSIC = 0,
    SETTING_BUTTON_VOLUME_SOUND,
    SETTING_BUTTON_CONTROL,
    SETTING_BUTTON_GRAPHIC,
    SETTING_BUTTON_TYPE_TOTAL
};
const int SETTING_BUTTON_WIDTH = 176*3;
const int SETTING_BUTTON_HEIGHT[SETTING_BUTTON_TYPE_TOTAL] = {24*3, 24*3, 32*3, 56*3};
const int SETTING_BUTTON_SPRITE_TOTAL = 2;
const int SETTING_BUTTON_TYPE_SPRITE[SETTING_BUTTON_TYPE_TOTAL] = {11, 11, 3, 3};

///Pacman
enum PACMAN_TYPE
{
    PACMAN_DEFAULT = 0,
    PACMAN_RED,
    PACMAN_ANDROID,
    PACMAN_MS,
    PACMAN_TYPE_TOTAL
};
const int PACMAN_ANIMTAION_FRAME = 4;
enum PACMAN_SPRITE
{
    PACMAN_UP = 0,
    PACMAN_RIGHT = 4,
    PACMAN_DOWN = 8,
    PACMAN_LEFT = 12,
    PACMAN_SPRITE_TOTAL = 16
};

///Object
const int OBJECT_PIXEL = 16*3;
enum OBJECT_TYPE
{
    OBJECT_PACMAN = 0,
    OBJECT_PACMAN_RED,
    OBJECT_PACMAN_ANDROID,
    OBJECT_PACMAN_MS,
    OBJECT_BLINKY,
    OBJECT_PINKY,
    OBJECT_INKY,
    OBJECT_CLYDE,
    OBJECT_FRIGHTENED_GHOST,
    OBJECT_EATEN_GHOST,
    OBJECT_PACMAN_DEATH,
    OBJECT_DOT,
    OBJECT_FRUIT,
    OBJECT_BELL,
    OBJECT_KEY,
    OBJECT_PACMAN_LIFE,
    OBJECT_TYPE_TOTAL
};

const int FRIGHTENED_GHOST_ANIMATION_FRAME = 2;
enum FRIGHTENED_GHOST_SPRITE
{
    FRIGHTENED_GHOST_DEFAULT = 0,
    FRIGHTENED_GHOST_WHITE = 2,
    FRIGHTENED_GHOST_SPRITE_TOTAL = 4
};

const int EATEN_GHOST_ANIMATION_FRAME = 2;
enum EATEN_GHOST_SPIRTE
{
    EATEN_GHOST_UP = 0,
    EATEN_GHOST_RIGHT,
    EATEN_GHOST_DOWN,
    EATEN_GHOST_LEFT,
    EATEN_GHOST_SPRITE_TOTAL
};

const int GHOST_ANIMATION_FRAME = 2;
enum GHOST_SPRITE
{
    GHOST_UP = 0,
    GHOST_RIGHT = 2,
    GHOST_DOWN = 4,
    GHOST_LEFT = 6,
    GHOST_SPRITE_TOTAL = 8
};

const int PACMAN_DEATH_ANIMATION_FRAME = 11;
const int PACMAN_DEATH_SPRITE_TOTAL = 11;

const int DOT_ANIMATION_FRAME = 6;
enum DOT_SPRITE
{
    DEFAULT_DOT = 0,
    POWER_DOT,
    SPEED_DOT,
    INVISIBLE_DOT,
    TIME_FREE_DOT,
    ANIMATION_DOT,
    DOT_SPRITE_TOTAL = 11
};

enum FRUIT_TYPE
{
    FRUIT_CHERRY = 0,
    FRUIT_STAWBERRY,
    FRUIT_ORANGE,
    FRUIT_APPLE,
    FRUIT_MELON,
    FRUIT_BANANA,
    FRUIT_WATER_MELON,
    FRUIT_MANGO,
    FRUIT_TYPE_TOTAL
};

///Labyrinth
const int LABYRINTH_WIDTH = 224*3;
const int LABYRINTH_HEIGHT = 248*3;
enum LABYRINTH_TYPE
{
    LABYRINTH_DEFAULT = 0,
    LABYRINTH_WHITE,
    LABYRINTH_TYPE_TOTAL
};

///Number
const int NUMBER_WIDTH = 8*3;
const int NUMBER_HEIGHT = 8*3;
const int NUMBER_TOTAL = 10;
enum NUMBER_TYPE
{
    NUMBER_DEFAULT = 0,
    NUMBER_BLUE,
    NUMBER_TYPE_TOTAL
};

///Alphabet
const int ALPHABET_WIDTH = 8*3;
const int ALPHABET_HEIGHT = 8*3;
const int ALPHABET_TOTAL = 30;
enum ALPHABET_TYPE
{
    ALPHABET_DEFAULT = 0,
    ALPHABET_BLUE,
    ALPHABET_TYPE_TOTAL
};

///Resources class
class Resources
{
    public:
        //Constructor:
        Resources();

        //Destructor:
        ~Resources();

        ///function:
        //init:
        void init(Texture* _texture);

        //load:
        void load();

        //create:
        void create();

        //free:
        void free();

        //close:
        void close();

        //getTexture:
        SDL_Texture* getTexture(const RESOURCES_TYPE resources_type);

        //getSprite:
        SDL_Rect getSprite(const BACKGROUND_TYPE background_type);
        SDL_Rect getSprite(const BUTTON_TYPE button_type, const bool clickable);
        SDL_Rect getSprite(const SETTING_BUTTON_TYPE setting_button_type, const bool clickable, const int curState);
        SDL_Rect getSprite(const OBJECT_TYPE object_type, const int sprite_val = 0);
        SDL_Rect getSprite(const LABYRINTH_TYPE labyrinth_type);
        SDL_Rect getSprite(const NUMBER_TYPE number_type, const int num);

    private:
        ///Console
        Console* console;

        ///Textures
        SDL_Texture* background;
        SDL_Texture* button;
        SDL_Texture* setting_button;
        SDL_Texture* pacman;
        SDL_Texture* object;
        SDL_Texture* labyrinth;
        SDL_Texture* number;
        SDL_Texture* alphabet;

        ///Sprites
        SDL_Rect background_sprite[BACKGROUND_TYPE_TOTAL];
        SDL_Rect button_sprite[BUTTON_TYPE_TOTAL][BUTTON_SPRITE_TOTAL];
        SDL_Rect* setting_button_sprite[SETTING_BUTTON_TYPE_TOTAL][SETTING_BUTTON_SPRITE_TOTAL];
        SDL_Rect frightened_ghost[FRIGHTENED_GHOST_SPRITE_TOTAL];
        SDL_Rect eaten_ghost[EATEN_GHOST_SPRITE_TOTAL];
        SDL_Rect pacman_sprite[PACMAN_SPRITE_TOTAL];
        SDL_Rect pacman_red_sprite[PACMAN_SPRITE_TOTAL];
        SDL_Rect pacman_android_sprite[PACMAN_SPRITE_TOTAL];
        SDL_Rect pacman_ms_sprite[PACMAN_SPRITE_TOTAL];
        SDL_Rect blinky[GHOST_SPRITE_TOTAL];
        SDL_Rect pinky[GHOST_SPRITE_TOTAL];
        SDL_Rect inky[GHOST_SPRITE_TOTAL];
        SDL_Rect clyde[GHOST_SPRITE_TOTAL];
        SDL_Rect pacman_death[PACMAN_DEATH_SPRITE_TOTAL];
        SDL_Rect dot[DOT_SPRITE_TOTAL];
        SDL_Rect fruit[FRUIT_TYPE_TOTAL];
        SDL_Rect bell, key, pacman_life;
        SDL_Rect labyrinth_sprite[LABYRINTH_TYPE_TOTAL];
        SDL_Rect number_sprite[NUMBER_TYPE_TOTAL][NUMBER_TOTAL];
        SDL_Rect alphabet_sprite[ALPHABET_TYPE_TOTAL][ALPHABET_TOTAL];

        ///Texture
        Texture* texture;

};

#endif // RESOURCES_H_
