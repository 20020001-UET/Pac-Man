///Game Status [Source]
#include "GameStatus.h"

#include "sstream"
#include "string"

//Constructor:
GameStatus::GameStatus()
{
    pacman = NULL;
    graphic = NULL;

    return;
}

//Destructor:
GameStatus::~GameStatus()
{
    pacman = NULL;
    graphic = NULL;

    return;
}

///main function:
void GameStatus::init(Pacman* _pacman, Graphic* _graphic, Timer* _timer, Point _highscore_point, Point _score_point, Point _life_point, Point _level_point)
{
    pacman = _pacman;
    graphic = _graphic;
    timer = _timer;

    highscore_point = _highscore_point;
    score_point = _score_point;
    life_point = _life_point;
    level_point = _level_point;

    score = highscore = bonus = pacman_life = score_state = 0;
    level = 0;

    animated = false;
    startAnimated = 0;
    frame = 0;
    frame_value = GAMESTATUS_FRAME_VALUE;

    return;
}

///update loop
void GameStatus::update()
{
    score = pacman->getDotEaten()*10 + bonus;

    if (score / 1000 > score_state && !animated)
    {
        animated = true;
        startAnimated = timer->getTicks();
        score_state = score / 1000;
    }

    highscore = std::max(highscore, score);
    pacman_life = pacman->getCurLife();

    return;
}

void GameStatus::render()
{
    NUMBER_TYPE number_type = NUMBER_DEFAULT;
    if (animated)
    {
        number_type = NUMBER_TYPE_AT[frame / frame_value];
        ++frame;
        if (frame / frame_value >= NUMBER_TYPE_TOTAL)
            frame = 0;
    }


    std::stringstream ss;
    std::string num;
    Point dest;

    //render score
    ss << score;
    ss >> num;
    while (num.size() < 8)
        num = '0' + num;

    dest = score_point;
    for (size_t index = 0; index < num.size(); index++)
    {
        int number = (int)(num[index] - '0');
        graphic->renderNumber(number_type, number, dest);
        dest.x += RESOURCES_PIXEL;
    }

    //render highscore
    ss << highscore;
    ss >> num;
    while (num.size() < 8)
        num = '0' + num;

    dest = highscore_point;
    for (size_t index = 0; index < num.size(); index++)
    {
        int number = (int)(num[index] - '0');
        if (highscore > score)
            graphic->renderNumber(NUMBER_DEFAULT, number, dest);
        else
            graphic->renderNumber(number_type, number, dest);
        dest.x += RESOURCES_PIXEL;
    }

    //render life
    SDL_Rect destination = {life_point.x, life_point.y, OBJECT_PIXEL, OBJECT_PIXEL};
    for (int index = 0; index < pacman_life; index++)
    {
        graphic->draw(OBJECT_PACMAN_LIFE, 0, destination);
        destination.x += OBJECT_PIXEL;
    }

    //render level
    destination = {level_point.x, level_point.y, OBJECT_PIXEL, OBJECT_PIXEL};
    for (int index = level - 6 + 1; index <= level; index++)
    {
        if (index >= 0)
        {
            graphic->draw(OBJECT_FRUIT, index, destination);
        }
        destination.x += OBJECT_PIXEL;
    }

    //handle animation
    if (startAnimated != 0)
    {
        Uint32 curAnimated = timer->getTicks();
        if (curAnimated - startAnimated >= SCORE_ANIMATED_TIME)
        {
            animated = false;
            startAnimated = 0;
        }
    }

    return;
}

///update animation
void GameStatus::setAnimated(bool _animated)
{
    animated = _animated;
    return;
}

///update level
void GameStatus::updateLevel()
{
    level++;
    return;
}