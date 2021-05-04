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
    SCORE,
    FRUIT,
    UNIQUE_GHOST,
    SPEECH,
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
    BACKGROUND_GAME_OVER,
    BACKGROUND_WIN_GAME,
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
const int SETTING_BUTTON_HEIGHT[SETTING_BUTTON_TYPE_TOTAL] = {24*3, 24*3, 32*3, 48*3};
const int SETTING_BUTTON_SPRITE_TOTAL = 2;
const int SETTING_BUTTON_TYPE_SPRITE[SETTING_BUTTON_TYPE_TOTAL] = {11, 11, 3, 3};

///Pacman
enum PACMAN_TYPE
{
    PACMAN_DEFAULT = 0,
    PACMAN_MS,
    PACMAN_ANDROID,
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
    OBJECT_DOT_STATUS,
    OBJECT_LEVEL,
    OBJECT_BELL,
    OBJECT_KEY,
    OBJECT_FRUIT,
    OBJECT_PACMAN_LIFE,
    OBJECT_MYSTERY,
    OBJECT_DEADLY,
    OBJECT_SPEEDY,
    OBJECT_INVISY,
    OBJECT_FREEZY,
    OBJECT_GOLDEN,
    OBJECT_GOLDEN_EXHAUTED_DEFAULT,
    OBJECT_GOLDEN_EXHAUTED_YELLOW,
    OBJECT_GOLDEN_DEATH,
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
    GHOST_UPGRADE = 8,
    GHOST_SPRITE_TOTAL = 11
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
    DOT_SPRITE_TOTAL
};

const int DOT_STATUS_WIDTH = 16*3;
const int DOT_STATUS_HEIGHT = 16*3;
enum DOT_STATUS
{
    POWER_DOT_STATUS = 0,
    CONFUSED_STATUS,
    SPEED_DOT_STATUS,
    SLOW_DOWN_STATUS,
    INVISIBLE_DOT_STATUS,
    BLIND_STATUS,
    TIME_FREE_DOT_STATUS,
    FREEZE_STATUS,
    DOT_STATUS_TOTAL
};

enum LEVEL_TYPE
{
    LEVEL_CHERRY = 0,
    LEVEL_STAWBERRY,
    LEVEL_ORANGE,
    LEVEL_APPLE,
    LEVEL_MELON,
    LEVEL_BANANA,
    LEVEL_WATER_MELON,
    LEVEL_MANGO,
    LEVEL_TYPE_TOTAL
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

///Score
const int SCORE_WIDTH = 32*3;
const int SCORE_HEIGHT = 16*3;
enum SCORE_TYPE
{
    SCORE_DEFAULT = -1,
    SCORE_EAT_GHOST = 0,
    SCORE_EAT_FRUIT = 8,
    SCORE_TYPE_TOTAL = 16
};

///Fruit
const int FRUIT_WIDTH = 16*3;
const int FRUIT_HEIGHT = 16*3;
const int FRUIT_ANIMTAION_FRAME = 4;
const int FRUIT_SPRITE_TOTAL = 4;
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

///Unique Ghost
const int UNIQUE_GHOST_WIDTH = 16*3;
const int UNIQUE_GHOST_HEIGHT = 16*3;
const int UNIQUE_ANIMATION_FRAME = 2;
enum UNIQUE_GHOST_TYPE
{
    UNIQUE_GHOST_MYSTERY = 0,
    UNIQUE_GHOST_DEADLY,
    UNIQUE_GHOST_SPEEDY,
    UNIQUE_GHOST_INVISY,
    UNIQUE_GHOST_FREEZY,
    UNIQUE_GHOST_GOLDEN,
    UNIQUE_GHOST_GOLDEN_EXHAUTED,
    UNIQUE_GHOST_GOLDEN_DEATH,
    UNIQUE_GHOST_TOTAL
};

enum UNIQUE_GHOST_GOLDEN_EXHAUTED_TYPE
{
    UNIQUE_GHOST_GOLDEN_EXHAUTED_DEFAULT = 0,
    UNIQUE_GHOST_GOLDEN_EXHAUTED_YELLOW,
    UNIQUE_GHOST_GOLDEN_EXHAUTED_TOTAL
};

const int UNIQUE_GHOST_MYSTERY_ANIMATION_FRAME = 2;
enum UNIQUE_GHOST_MYSTERY_SPRITE
{
    UNIQUE_GHOST_MYSTERY_DEFAULT = 0,
    UNIQUE_GHOST_MYSTERY_WHITE = 2,
    UNIQUE_GHOST_MYSTERY_UPGRADE_DEFAULT = 4,
    UNIQUE_GHOST_MYSTERY_UPGRADE_WHITE = 6,
    UNIQUE_GHOST_MYSTERY_SPRITE_TOTAL = 8
};

const int UNIQUE_GHOST_GOLDEN_DEATH_ANIMATION_FRAME = 8;

enum UNIQUE_GHOST_SPRITE
{
    UNIQUE_GHOST_UP = 0,
    UNIQUE_GHOST_RIGHT = 2,
    UNIQUE_GHOST_DOWN = 4,
    UNIQUE_GHOST_LEFT = 6,
    UNIQUE_GHOST_SPRITE_TOTAL = 8
};

///Speech
enum SPEECH_TYPE
{
    SPEECH_UPGRADE = 0,
    SPEECH_SHOW_UP,
    SPEECH_TYPE_TOTAL
};

enum SPEECH_UPGRADE_TYPE
{
    SPEECH_UPGRADE_BLINKY = 0,
    SPEECH_UPGRADE_PINKY,
    SPEECH_UPGRADE_INKY,
    SPEECH_UPGRADE_CLYDE,
    SPEECH_UPGRADE_TOTAL
};
const int SPEECH_UPGRADE_WIDTH = 44*3;
const int SPEECH_UPGRADE_HEIGHT = 26*3;

const int SPEECH_SHOW_UP_TOTAL = 2;
const int SPEECH_SHOW_UP_WIDTH = 52*3;
const int SPEECH_SHOW_UP_HEIGHT = 26*3;

///HP bar
const int HP_BAR_WIDTH = 112*3;
const int HP_BAR_HEIGHT = 16*3;
const int HP_WIDTH = 104*3;
const int HP_HEIGHT = 8*3;

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
        SDL_Rect getSprite(const SCORE_TYPE score_type, const int sprite_val);
        SDL_Rect getSprite(const FRUIT_TYPE fruit_type, const int sprite_val = 0);
        SDL_Rect getSprite(const SPEECH_TYPE speech_type, const int sprite_val = 0);
        SDL_Rect getHP_BarSprite();
        SDL_Rect getHPSprite(const Uint16 curHP, const Uint16 maxHP);

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
        SDL_Texture* score;
        SDL_Texture* fruit;
        SDL_Texture* unique_ghost;
        SDL_Texture* speech;

        ///Sprites
        SDL_Rect background_sprite[BACKGROUND_TYPE_TOTAL];
        SDL_Rect button_sprite[BUTTON_TYPE_TOTAL][BUTTON_SPRITE_TOTAL];
        SDL_Rect* setting_button_sprite[SETTING_BUTTON_TYPE_TOTAL][SETTING_BUTTON_SPRITE_TOTAL];
        SDL_Rect frightened_ghost[FRIGHTENED_GHOST_SPRITE_TOTAL];
        SDL_Rect eaten_ghost[EATEN_GHOST_SPRITE_TOTAL];
        SDL_Rect pacman_sprite[PACMAN_SPRITE_TOTAL];
        SDL_Rect pacman_ms_sprite[PACMAN_SPRITE_TOTAL];
        SDL_Rect pacman_android_sprite[PACMAN_SPRITE_TOTAL];
        SDL_Rect blinky[GHOST_SPRITE_TOTAL];
        SDL_Rect mystery[UNIQUE_GHOST_MYSTERY_SPRITE_TOTAL];
        SDL_Rect deadly[UNIQUE_GHOST_SPRITE_TOTAL];
        SDL_Rect pinky[GHOST_SPRITE_TOTAL];
        SDL_Rect speedy[UNIQUE_GHOST_SPRITE_TOTAL];
        SDL_Rect inky[GHOST_SPRITE_TOTAL];
        SDL_Rect invisy[UNIQUE_GHOST_SPRITE_TOTAL];
        SDL_Rect clyde[GHOST_SPRITE_TOTAL];
        SDL_Rect freezy[UNIQUE_GHOST_SPRITE_TOTAL];
        SDL_Rect golden[UNIQUE_GHOST_SPRITE_TOTAL];
        SDL_Rect golden_exhauted[UNIQUE_GHOST_GOLDEN_EXHAUTED_TOTAL][UNIQUE_GHOST_SPRITE_TOTAL];
        SDL_Rect golden_death[UNIQUE_GHOST_SPRITE_TOTAL];
        SDL_Rect pacman_death[PACMAN_DEATH_SPRITE_TOTAL];
        SDL_Rect dot[DOT_SPRITE_TOTAL];
        SDL_Rect dot_status[DOT_STATUS_TOTAL];
        SDL_Rect level[FRUIT_TYPE_TOTAL];
        SDL_Rect bell, key, pacman_life;
        SDL_Rect labyrinth_sprite[LABYRINTH_TYPE_TOTAL];
        SDL_Rect number_sprite[NUMBER_TYPE_TOTAL][NUMBER_TOTAL];
        SDL_Rect alphabet_sprite[ALPHABET_TYPE_TOTAL][ALPHABET_TOTAL];
        SDL_Rect score_sprite[SCORE_TYPE_TOTAL];
        SDL_Rect fruit_sprite[FRUIT_TYPE_TOTAL][FRUIT_SPRITE_TOTAL];
        SDL_Rect speech_upgrade[SPEECH_UPGRADE_TOTAL];
        SDL_Rect speech_show_up[SPEECH_SHOW_UP_TOTAL];
        SDL_Rect HP_bar, health_point;

        ///Texture
        Texture* texture;

};

#endif // RESOURCES_H_
