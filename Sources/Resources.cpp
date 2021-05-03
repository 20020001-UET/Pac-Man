///Resources [Source]
#include "Resources.h"

///Include header
#include "Texture.h"

///Resources class
//Constructor:
Resources::Resources()
{
    console = new Console("Resources");

    texture = NULL;

    background = NULL;
    button = NULL;
    setting_button = NULL;
    pacman = NULL;
    object = NULL;
    labyrinth = NULL;
    number = NULL;
    alphabet = NULL;
    score = NULL;
    fruit = NULL;
    unique_ghost = NULL;
    speech = NULL;

    for (int index = 0; index < SETTING_BUTTON_TYPE_TOTAL; index++)
        for (int sprite = 0; sprite < SETTING_BUTTON_SPRITE_TOTAL; sprite++)
            setting_button_sprite[index][sprite] = new SDL_Rect[SETTING_BUTTON_TYPE_SPRITE[index]];

    return;
}

//Destructor:
Resources::~Resources()
{
    texture = NULL;

    for (int index = 0; index < SETTING_BUTTON_TYPE_TOTAL; index++)
        for (int sprite = 0; sprite < SETTING_BUTTON_SPRITE_TOTAL; sprite++)
        {
            delete setting_button_sprite[index][sprite];
            setting_button_sprite[index][sprite] = NULL;
        }

    delete console;
    console = NULL;
    return;
}

///function:
//init:
void Resources::init(Texture* _texture)
{
    texture = _texture;

    load();

    create();

    console->writeLine("Initialized Resources");
    return;
}

//load:
void Resources::load()
{
    console->writeLine("Loading textures. . .");

    background = texture->load("Assets/Texture/background.png");

    button = texture->load("Assets/Texture/button.png");

    setting_button = texture->load("Assets/Texture/settingButton.png");

    pacman = texture->load("Assets/Texture/pacman.png");

    object = texture->load("Assets/Texture/object.png");

    labyrinth = texture->load("Assets/Texture/labyrinth.png");

    number = texture->load("Assets/Texture/number.png");

    //alphabet = texture->load("Assets/Texture/alphabet.png");

    score = texture->load("Assets/Texture/score.png");

    fruit = texture->load("Assets/Texture/fruits.png");

    unique_ghost = texture->load("Assets/Texture/uniqueGhost.png");

    speech = texture->load("Assets/Texture/speech.png");

    return;
}

//create:
void Resources::create()
{
    console->writeLine("Creating sprites. . ");

    for (int index = 0; index < BACKGROUND_TYPE_TOTAL; index++)
    {
        background_sprite[index] = {index*BACKGROUND_WIDTH, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
    }
    console->writeLine("Created background sprites");

    for (int index = 0; index < BUTTON_TYPE_TOTAL; index++)
    {
        for (int sprite = 0; sprite < BUTTON_SPRITE_TOTAL; sprite++)
        {
            button_sprite[index][sprite] = {index*BUTTON_WIDTH, sprite*BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT};
        }
    }
    console->writeLine("Created button sprites");

    int height_sprite = 0;
    for (int index = 0; index < SETTING_BUTTON_TYPE_TOTAL; index++)
    {
        for (int row = 0; row < SETTING_BUTTON_TYPE_SPRITE[index]; row++)
        {
            for (int sprite = 0; sprite < SETTING_BUTTON_SPRITE_TOTAL; sprite++)
            {
                setting_button_sprite[index][sprite][row] = {sprite*SETTING_BUTTON_WIDTH,
                                                             height_sprite,
                                                             SETTING_BUTTON_WIDTH,
                                                             SETTING_BUTTON_HEIGHT[index]};
            }
            height_sprite += SETTING_BUTTON_HEIGHT[index];
        }
    }
    console->writeLine("Created setting button sprites");

    ///Pacman sprite
    int cnt = 0;
    height_sprite = 0;
    for (int index = 0; index < PACMAN_SPRITE_TOTAL; index++)
    {
        if (index % 4 == 3)
            pacman_sprite[index] = pacman_sprite[index-2];
        else
            if (index % 4 == 0 && index > 0)
                pacman_sprite[index] = pacman_sprite[0];
            else
            {
                pacman_sprite[index] = {cnt*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
                cnt++;
            }
    }
    console->writeLine("Created pacman sprites");

    cnt = 0;
    height_sprite++;
    for (int index = 0; index < PACMAN_SPRITE_TOTAL; index++)
    {
        if (index % 4 == 3)
            pacman_android_sprite[index] = pacman_android_sprite[index-2];
        else
        {
            pacman_android_sprite[index] = {cnt*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
            cnt++;
        }
    }
    console->writeLine("Created android pacman sprites");

    cnt = 0;
    height_sprite++;
    for (int index = 0; index < PACMAN_SPRITE_TOTAL; index++)
    {
        if (index % 4 == 3)
            pacman_ms_sprite[index] = pacman_ms_sprite[index-2];
        else
        {
            pacman_ms_sprite[index] = {cnt*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
            cnt++;
        }
    }
    console->writeLine("Created ms pacman sprites");

    ///Object sprites
    //Line 0
    height_sprite = 0;
    for (int index = 0; index < GHOST_SPRITE_TOTAL; index++)
    {
        blinky[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created blinky sprites");

    //Line 1
    height_sprite++;
    for (int index = 0; index < GHOST_SPRITE_TOTAL; index++)
    {
        pinky[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created pinky sprites");

    //Line 2
    height_sprite++;
    for (int index = 0; index < GHOST_SPRITE_TOTAL; index++)
    {
        inky[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created inky sprites");

    //Line 3
    height_sprite++;
    for (int index = 0; index < GHOST_SPRITE_TOTAL; index++)
    {
        clyde[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created clyde sprites");

    //Line 4
    height_sprite++;
    cnt = 0;
    for (int index = 0; index < FRIGHTENED_GHOST_SPRITE_TOTAL; index++)
    {
        frightened_ghost[index] = {cnt*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
        cnt++;
    }
    console->writeLine("Created frightened ghost sprites");

    for (int index = 0; index < EATEN_GHOST_SPRITE_TOTAL; index++)
    {
        eaten_ghost[index] = {cnt*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
        cnt++;
    }
    console->writeLine("Created eaten ghost sprites");

    //Line 5
    height_sprite++;
    cnt = 0;
    for (int index = 0; index < DOT_SPRITE_TOTAL; index++)
    {
        dot[index] = {cnt*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
        cnt++;
    }
    console->writeLine("Created dot sprites");

    //Line 6
    height_sprite++;
    for (int index = 0; index < PACMAN_DEATH_SPRITE_TOTAL; index++)
    {
        pacman_death[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created pacman death sprites");

    //Line 7
    height_sprite++;
    for (int index = 0; index < LEVEL_TYPE_TOTAL+3; index++)
    {
        if (index < LEVEL_TYPE_TOTAL)
            level[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
        else
        {
            if (index == 8)
                bell = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
            if (index == 9)
                key = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
            if (index == 10)
                pacman_life = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
        }
    }
    console->writeLine("Created level sprites");

    //Line 8
    height_sprite++;
    cnt = 0;
    for (int index = 0; index < DOT_STATUS_TOTAL; index++)
    {
        dot_status[index] = {cnt*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
        cnt++;
    }
    console->writeLine("Created dot status sprites");

    ///Labyrinth sprites
    for (int index = 0; index < LABYRINTH_TYPE_TOTAL; index++)
    {
        labyrinth_sprite[index] = {index*LABYRINTH_WIDTH, 0, LABYRINTH_WIDTH, LABYRINTH_HEIGHT};
    }
    console->writeLine("Created labyrinth sprites");

    ///Number sprites
    for (int index = 0; index < NUMBER_TYPE_TOTAL; index++)
    {
        for (int cnt = 0; cnt < 10; cnt++)
        {
            number_sprite[index][cnt] = {cnt*NUMBER_WIDTH, index*NUMBER_HEIGHT, NUMBER_WIDTH, NUMBER_HEIGHT};
        }
    }
    console->writeLine("Created number sprites");

    ///Alphabet sprites

    ///Score sprite
    cnt = 0;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            score_sprite[cnt] = {col*SCORE_WIDTH, row*SCORE_HEIGHT, SCORE_WIDTH, SCORE_HEIGHT};
            cnt++;
        }
    }
    console->writeLine("Created score sprites");

    ///Fruit sprite
    for (int index = 0; index < FRUIT_TYPE_TOTAL; index++)
    {
        for (int sprite = 0; sprite < FRUIT_SPRITE_TOTAL-1; sprite++)
        {
            fruit_sprite[index][sprite] = {sprite*FRUIT_WIDTH, index*FRUIT_HEIGHT, FRUIT_WIDTH, FRUIT_HEIGHT};
        }
        fruit_sprite[index][FRUIT_SPRITE_TOTAL-1] = fruit_sprite[index][1];
    }
    console->writeLine("Created fruits sprites");

    ///Unique ghost sprite
    //Line 0
    height_sprite = 0;
    for (int index = 0; index < UNIQUE_GHOST_MYSTERY_SPRITE_TOTAL; index++)
    {
        mystery[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created mystery sprites");

    //Line 1
    height_sprite++;
    for (int index = 0; index < UNIQUE_GHOST_SPRITE_TOTAL; index++)
    {
        deadly[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created deadly sprites");

    //Line 2
    height_sprite++;
    for (int index = 0; index < UNIQUE_GHOST_SPRITE_TOTAL; index++)
    {
        speedy[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created speedy sprites");

    //Line 3
    height_sprite++;
    for (int index = 0; index < UNIQUE_GHOST_SPRITE_TOTAL; index++)
    {
        invisy[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created invisy sprites");

    //Line 4
    height_sprite++;
    for (int index = 0; index < UNIQUE_GHOST_SPRITE_TOTAL; index++)
    {
        freezy[index] = {index*OBJECT_PIXEL, height_sprite*OBJECT_PIXEL, OBJECT_PIXEL, OBJECT_PIXEL};
    }
    console->writeLine("Created freezy sprites");

    ///Speech sprites
    //Line 0
    height_sprite = 0;
    for (int index = 0; index < SPEECH_UPGRADE_TOTAL; index++)
    {
        speech_upgrade[index] = {index*SPEECH_UPGRADE_WIDTH, height_sprite*SPEECH_UPGRADE_HEIGHT, SPEECH_UPGRADE_WIDTH, SPEECH_UPGRADE_HEIGHT};
    }
    console->writeLine("Created upgrade speech sprites");

    //Line 1
    height_sprite++;
    for (int index = 0; index < SPEECH_SHOW_UP_TOTAL; index++)
    {
        speech_show_up[index] = {index*SPEECH_SHOW_UP_WIDTH, height_sprite*SPEECH_SHOW_UP_HEIGHT, SPEECH_SHOW_UP_WIDTH, SPEECH_SHOW_UP_HEIGHT};
    }
    console->writeLine("Created show up speech sprites");
    return;
}

//getTexture:
SDL_Texture* Resources::getTexture(const RESOURCES_TYPE resources_type)
{
    SDL_Texture* tmpTexture = NULL;
    switch (resources_type)
    {
        case BACKGROUND:
            tmpTexture = background;
            break;
        case BUTTON:
            tmpTexture = button;
            break;
        case SETTING_BUTTON:
            tmpTexture = setting_button;
            break;
        case PACMAN:
            tmpTexture = pacman;
            break;
        case OBJECT:
            tmpTexture = object;
            break;
        case LABYRINTH:
            tmpTexture = labyrinth;
            break;
        case NUMBER:
            tmpTexture = number;
            break;
        case ALPHABET:
            break;
        case SCORE:
            tmpTexture = score;
            break;
        case FRUIT:
            tmpTexture = fruit;
            break;
        case UNIQUE_GHOST:
            tmpTexture = unique_ghost;
            break;
        case SPEECH:
            tmpTexture = speech;
            break;
        default:
            break;
    }
    return tmpTexture;
}

//getSprite:
SDL_Rect Resources::getSprite(const BACKGROUND_TYPE background_type)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = background_sprite[background_type];
    return tmpRect;
}

SDL_Rect Resources::getSprite(const BUTTON_TYPE button_type, const bool clickable)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = (!clickable) ? button_sprite[button_type][0] : button_sprite[button_type][1];
    return tmpRect;
}

SDL_Rect Resources::getSprite(const SETTING_BUTTON_TYPE setting_button_type, const bool clickable, const int curState)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = (!clickable) ? setting_button_sprite[setting_button_type][0][curState] : setting_button_sprite[setting_button_type][1][curState];
    return tmpRect;
}

SDL_Rect Resources::getSprite(const OBJECT_TYPE object_type, const int sprite_val)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    switch (object_type)
    {
        case OBJECT_PACMAN:
            tmpRect = pacman_sprite[sprite_val];
            break;
        case OBJECT_PACMAN_MS:
            tmpRect = pacman_ms_sprite[sprite_val];
            break;
        case OBJECT_PACMAN_ANDROID:
            tmpRect = pacman_android_sprite[sprite_val];
            break;
        case OBJECT_BLINKY:
            tmpRect = blinky[sprite_val];
            break;
        case OBJECT_PINKY:
            tmpRect = pinky[sprite_val];
            break;
        case OBJECT_INKY:
            tmpRect = inky[sprite_val];
            break;
        case OBJECT_CLYDE:
            tmpRect = clyde[sprite_val];
            break;
        case OBJECT_FRIGHTENED_GHOST:
            tmpRect = frightened_ghost[sprite_val];
            break;
        case OBJECT_EATEN_GHOST:
            tmpRect = eaten_ghost[sprite_val];
            break;
        case OBJECT_PACMAN_DEATH:
            tmpRect = pacman_death[sprite_val];
            break;
        case OBJECT_DOT:
            tmpRect = dot[sprite_val];
            break;
        case OBJECT_DOT_STATUS:
            tmpRect = dot_status[sprite_val];
            break;
        case OBJECT_LEVEL:
            tmpRect = level[sprite_val];
            break;
        case OBJECT_BELL:
            tmpRect = bell;
            break;
        case OBJECT_KEY:
            tmpRect = key;
            break;
        case OBJECT_PACMAN_LIFE:
            tmpRect = pacman_life;
            break;
        case OBJECT_MYSTERY:
            tmpRect = mystery[sprite_val];
            break;
        case OBJECT_DEADLY:
            tmpRect = deadly[sprite_val];
            break;
        case OBJECT_SPEEDY:
            tmpRect = speedy[sprite_val];
            break;
        case OBJECT_INVISY:
            tmpRect = invisy[sprite_val];
            break;
        case OBJECT_FREEZY:
            tmpRect = freezy[sprite_val];
            break;
        case OBJECT_GOLDEN:
            tmpRect = golden[sprite_val];
            break;
        default:
            break;
    }
    return tmpRect;
}

SDL_Rect Resources::getSprite(const LABYRINTH_TYPE labyrinth_type)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = labyrinth_sprite[labyrinth_type];
    return tmpRect;
}

SDL_Rect Resources::getSprite(const NUMBER_TYPE number_type, const int num)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = number_sprite[number_type][num];
    return tmpRect;
}

SDL_Rect Resources::getSprite(const SCORE_TYPE score_type, const int sprite_val)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = score_sprite[sprite_val];
    return tmpRect;
}

SDL_Rect Resources::getSprite(const FRUIT_TYPE fruit_type, const int sprite_val)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = fruit_sprite[fruit_type][sprite_val];
    return tmpRect;
}

SDL_Rect Resources::getSprite(const SPEECH_TYPE speech_type, const int sprite_val)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    switch (speech_type)
    {
        case SPEECH_UPGRADE:
            tmpRect = speech_upgrade[sprite_val];
            break;
        case SPEECH_SHOW_UP:
            tmpRect = speech_show_up[sprite_val];
            break;
        default:
            break;
    }
    return tmpRect;
}

//free:
void Resources::free()
{
    console->writeLine("Freeing textures. . .");

    SDL_DestroyTexture(background);
    background = NULL;

    SDL_DestroyTexture(button);
    button = NULL;

    SDL_DestroyTexture(setting_button);
    setting_button = NULL;

    SDL_DestroyTexture(pacman);
    pacman = NULL;

    SDL_DestroyTexture(object);
    object = NULL;

    SDL_DestroyTexture(labyrinth);
    labyrinth = NULL;

    SDL_DestroyTexture(number);
    number = NULL;

    //SDL_DestroyTexture(alphabet);
    //alphabet = NULL;

    SDL_DestroyTexture(score);
    score = NULL;

    SDL_DestroyTexture(fruit);
    fruit = NULL;

    SDL_DestroyTexture(unique_ghost);
    unique_ghost = NULL;

    SDL_DestroyTexture(speech);
    speech = NULL;

    return;
}

//close:
void Resources::close()
{
    console->writeLine("Closing Resources. . .");

    free();
    return;
}
