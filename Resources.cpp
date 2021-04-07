///Resource [Source]
#include "Resources.h"

#include "Texture.h"

///Resources class
//Static
Console Resources::console = Console("Resources");

///Textures
//Menu
SDL_Texture* Resources::menu;
SDL_Texture* Resources::how_to_play;
SDL_Texture* Resources::about;
SDL_Texture* Resources::button;

//Playing
SDL_Texture* Resources::object;
SDL_Texture* Resources::labyrinth;
SDL_Texture* Resources::dot_texture;

///Sprites
//Menu
SDL_Rect Resources::menu_sprite[MENU_SPRITE_COUNT];
SDL_Rect Resources::how_to_play_sprite;
SDL_Rect Resources::about_sprite;
SDL_Rect Resources::button_sprite[BUTTON_SPRITE_COUNT];

//Playing
SDL_Rect Resources::pacman[PACMAN_SPRITE_COUNT];
SDL_Rect Resources::frightened_ghost[GHOST_ANIMATION_FRAME*2];
SDL_Rect Resources::eaten_ghost[GHOST_SPRITE_COUNT];
SDL_Rect Resources::blinky[GHOST_SPRITE_COUNT];
SDL_Rect Resources::pinky[GHOST_SPRITE_COUNT];
SDL_Rect Resources::inky[GHOST_SPRITE_COUNT];
SDL_Rect Resources::clyde[GHOST_SPRITE_COUNT];
SDL_Rect Resources::labyrinth_sprite;
SDL_Rect Resources::smallDot, Resources::bigDot;

void Resources::load()
{
    console.writeLine("Loading textures. . .");

    ///Menu

    //Menu texture
    menu = Texture::load("Assets/menu.png");

    //Menu sprites
    for (int index = 0; index < MENU_SPRITE_COUNT; index++)
    {
        menu_sprite[index] = {MENU_WIDTH*index, 0,
                         MENU_WIDTH, MENU_HEIGHT};
    }

    //How to play texture
    how_to_play = Texture::load("Assets/howtoplay.png");

    //How to play spirtes
    how_to_play_sprite = {0, 0,
                         MENU_WIDTH, MENU_HEIGHT};

    //About texture
    about = Texture::load("Assets/about.png");

    //About sprites
    about_sprite = {0, 0,
                         MENU_WIDTH, MENU_HEIGHT};

    //Button texture
    button = Texture::load("Assets/button.png");

    //Button sprites
    for (int index = 0; index < BUTTON_SPRITE_COUNT; index++)
    {
        button_sprite[index] = {0, BUTTON_HEIGHT*index,
                         BUTTON_WIDTH, BUTTON_HEIGHT};
    }

    ///Playing

    //Object texture
    object = Texture::load("Assets/object.png");

    //Pacman sprites
    for (int index = 0; index < PACMAN_SPRITE_COUNT; index++)
    {
        pacman[index] = {SPRITE_PIXEL*index, PACMAN_SPRITE*SPRITE_PIXEL,
                         SPRITE_PIXEL, SPRITE_PIXEL};
    }

    console.writeLine("Created pacman sprites.");

    //Blinky sprites
    for (int index = 0; index < GHOST_SPRITE_COUNT; index++)
    {
        blinky[index] = {SPRITE_PIXEL*index, BLINKY_SPIRTE*SPRITE_PIXEL,
                         SPRITE_PIXEL, SPRITE_PIXEL};
    }

    //Ghost frightened sprites
    for (int index = 0; index < 2; index++)
    {
        frightened_ghost[index] = {SPRITE_PIXEL*(index + GHOST_SPRITE_COUNT), BLINKY_SPIRTE*SPRITE_PIXEL,
                                   SPRITE_PIXEL, SPRITE_PIXEL};
    }
    for (int index = 2; index < 4; index++)
    {
        frightened_ghost[index] = {SPRITE_PIXEL*(index-2 + GHOST_SPRITE_COUNT), PINKY_SPRITE*SPRITE_PIXEL,
                                   SPRITE_PIXEL, SPRITE_PIXEL};
    }

    //Ghost eaten sprites
    for (int index = 0; index < 2; index++)
    {
        eaten_ghost[index] = {SPRITE_PIXEL*(index + GHOST_SPRITE_COUNT), INKY_SPRITE*SPRITE_PIXEL,
                                   SPRITE_PIXEL, SPRITE_PIXEL};
    }
    for (int index = 2; index < 4; index++)
    {
        eaten_ghost[index] = {SPRITE_PIXEL*(index-2 + GHOST_SPRITE_COUNT), CLYDE_SPRITE*SPRITE_PIXEL,
                                   SPRITE_PIXEL, SPRITE_PIXEL};
    }

    //Pinky sprites
    for (int index = 0; index < GHOST_SPRITE_COUNT; index++)
    {
        pinky[index] = {SPRITE_PIXEL*index, PINKY_SPRITE*SPRITE_PIXEL,
                         SPRITE_PIXEL, SPRITE_PIXEL};
    }

    //Inky sprites
    for (int index = 0; index < GHOST_SPRITE_COUNT; index++)
    {
        inky[index] = {SPRITE_PIXEL*index, INKY_SPRITE*SPRITE_PIXEL,
                         SPRITE_PIXEL, SPRITE_PIXEL};
    }

    //Clyde sprites
    for (int index = 0; index < GHOST_SPRITE_COUNT; index++)
    {
        clyde[index] = {SPRITE_PIXEL*index, CLYDE_SPRITE*SPRITE_PIXEL,
                         SPRITE_PIXEL, SPRITE_PIXEL};
    }

    //Labyrinth texture
    labyrinth = Texture::load("Assets/labyrinth.png");

    //Labyrinth sprite
    labyrinth_sprite = {0, 0, 25*28, 25*31};

    console.writeLine("Created labyrinth sprites.");

    //Dot texture
    dot_texture = Texture::load("Assets/dot.png");

    //Dot sprites
    smallDot = {0, 0, 25, 25};
    bigDot = {25, 0, 25, 25};

    console.writeLine("Created dot spirtes.");
}

void Resources::free()
{
    console.writeLine("Destroying textures. . .");

    //Menu
    SDL_DestroyTexture(menu);
    menu = NULL;

    SDL_DestroyTexture(button);
    button = NULL;

    //Playing
    SDL_DestroyTexture(object);
    object = NULL;

    SDL_DestroyTexture(labyrinth);
    labyrinth = NULL;

    SDL_DestroyTexture(dot_texture);
    dot_texture = NULL;
}

SDL_Texture* Resources::getTexture(MENU_VAL value)
{
    SDL_Texture* tmpTexture = NULL;
    switch (value)
    {
        case MENU_VAL::MENU_TEXTURE:
            tmpTexture = menu;
            break;

        case MENU_VAL::HOW_TO_PLAY_TEXTURE:
            tmpTexture = how_to_play;
            break;

        case MENU_VAL::ABOUT_TEXTURE:
            tmpTexture = about;
            break;

        case MENU_VAL::BUTTON_TEXTURE:
            tmpTexture = button;
            break;

        default:
            break;
    }
    return tmpTexture;
}

SDL_Texture* Resources::getTexture(OBJECT_VAL value)
{
    SDL_Texture* tmpTexture = NULL;
    switch (value)
    {
        case OBJECT_VAL::PACMAN_SPRITE:
        case OBJECT_VAL::FRIGHTENED_GHOST:
        case OBJECT_VAL::EATEN_GHOST:
        case OBJECT_VAL::BLINKY_SPIRTE:
        case OBJECT_VAL::PINKY_SPRITE:
        case OBJECT_VAL::INKY_SPRITE:
        case OBJECT_VAL::CLYDE_SPRITE:
            tmpTexture = object;
            break;

        case OBJECT_VAL::DOT:
            tmpTexture = dot_texture;
            break;

        default:
            break;
    }
    return tmpTexture;
}

SDL_Texture* Resources::getTextureLabyrinth()
{
    return labyrinth;
}

SDL_Rect Resources::getSprite(MENU_VAL value, int sprite_val)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    switch (value)
    {
        case MENU_VAL::MENU_TEXTURE:
            tmpRect = menu_sprite[sprite_val];
            break;

        case MENU_VAL::HOW_TO_PLAY_TEXTURE:
            tmpRect = how_to_play_sprite;
            break;

        case MENU_VAL::ABOUT_TEXTURE:
            tmpRect = about_sprite;
            break;

        case MENU_VAL::BUTTON_TEXTURE:
            tmpRect = button_sprite[sprite_val];
            break;

        default:
            break;
    }
    return tmpRect;
}

SDL_Rect Resources::getSprite(OBJECT_VAL value, int sprite_val)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    switch (value)
    {
        case OBJECT_VAL::PACMAN_SPRITE:
            tmpRect = pacman[sprite_val];
            break;

        case OBJECT_VAL::FRIGHTENED_GHOST:
            tmpRect = frightened_ghost[sprite_val];
            break;

        case OBJECT_VAL::EATEN_GHOST:
            tmpRect = eaten_ghost[sprite_val];
            break;

        case OBJECT_VAL::BLINKY_SPIRTE:
            tmpRect = blinky[sprite_val];
            break;

        case OBJECT_VAL::PINKY_SPRITE:
            tmpRect = pinky[sprite_val];
            break;

        case OBJECT_VAL::INKY_SPRITE:
            tmpRect = inky[sprite_val];
            break;

        case OBJECT_VAL::CLYDE_SPRITE:
            tmpRect = clyde[sprite_val];
            break;

        case OBJECT_VAL::DOT:
            if (sprite_val == SMALL_DOT)
                tmpRect = smallDot;
            else
                tmpRect = bigDot;
            break;

        default:
            break;
    }
    return tmpRect;
}

SDL_Rect Resources::getSpriteLabyrinth()
{
    return labyrinth_sprite;
}
