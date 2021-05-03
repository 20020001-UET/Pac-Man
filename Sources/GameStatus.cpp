///Game Status [Source]
#include "GameStatus.h"

///Include header
#include <fstream>
#include <sstream>
#include <string>

//Constructor:
GameStatus::GameStatus()
{
    console = new Console("GameStatus");
    pacman = NULL;
    graphic = NULL;

    scoreObject.clear();

    return;
}

//Destructor:
GameStatus::~GameStatus()
{
    delete console;
    console = NULL;
    pacman = NULL;
    graphic = NULL;

    scoreObject.clear();

    return;
}

///main function:
void GameStatus::init(Pacman* _pacman, Graphic* _graphic, Timer* _timer, Uint32 _highscore, Point _highscore_point, Point _score_point, Point _life_point, Point _level_point, Point _power_point)
{
    pacman = _pacman;
    graphic = _graphic;
    timer = _timer;

    highscore_point = _highscore_point;
    score_point = _score_point;
    life_point = _life_point;
    level_point = _level_point;
    power_point = _power_point;

    score = highscore = bonus = pacman_life = score_state = 0;
    level = 0;

    animated = false;
    startAnimated = 0;
    frame = 0;
    frame_value = GAMESTATUS_FRAME_VALUE;

    highscore = _highscore;

    curGhostEaten = 0;

    for (int index = 0; index < PACMAN_POWER_STATE_TOTAL; index++)
        power[index] = false;

    console->writeLine("Initialized done!");

    return;
}

///push score
void GameStatus::updateScore()
{
    if (!scoreObject.empty())
    {
        std::vector<ScoreObject>::iterator it;
        do
        {
            it = scoreObject.begin();

            int timePast = timer->getTicks() - it->start;
            if (timePast >= SCORE_TIME)
            {
                scoreObject.erase(it);
            }
            else
                break;

            if (scoreObject.empty())
                break;
        } while (true);

    }
    return;
}

void GameStatus::pushScore(const UPDATE_SCORE update_score, const Point screen)
{
    if (update_score == UPDATE_SCORE_NORMAL_DOT)
        bonus += SCORE_NORMAL_DOT;
    if (update_score == UPDATE_SCORE_BIG_DOT)
        bonus += SCORE_BIG_DOT;

    int score_sprite = 0;
    if (update_score == UPDATE_SCORE_EAT_GHOST)
    {
        bonus += SCORE_EAT_GHOST_VALUE[curGhostEaten];
        score_sprite = SCORE_EAT_GHOST + curGhostEaten;
        curGhostEaten++;
    }

    if (update_score == UPDATE_SCORE_EAT_FRUIT)
    {
        bonus += SCORE_EAT_FRUIT_VALUE[level];
        score_sprite = SCORE_EAT_FRUIT + level;
    }

    scoreObject.push_back(ScoreObject(screen, timer->getTicks(), score_sprite));

    return;
}

void GameStatus::setGhostEaten(int updateValue)
{
    curGhostEaten = updateValue;
    return;
}

///update loop
void GameStatus::update()
{
    updateScore();

    score = pacman->getDotEaten()*10 + bonus;

    if ((int)(score / 1000) > score_state && !animated)
    {
        animated = true;
        startAnimated = timer->getTicks();
        score_state = score / 1000;
    }

    highscore = std::max(highscore, score);
    pacman_life = pacman->getCurLife();

    for (int index = 0; index < PACMAN_POWER_STATE_TOTAL; index++)
        power[index] = pacman->isPacmanPower(index);

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

    //render score
    ss << score;
    ss >> num;
    while (num.size() < 8)
        num = '0' + num;

    graphic->renderNumber(number_type, num, score_point);

    //render highscore
    ss.clear();
    ss << highscore;
    ss >> num;
    while (num.size() < 8)
        num = '0' + num;

    if (highscore > score)
        graphic->renderNumber(NUMBER_DEFAULT, num, highscore_point);
    else
        graphic->renderNumber(number_type, num, highscore_point);

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
            graphic->draw(OBJECT_LEVEL, index, destination);
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

    //render power status
    destination = {power_point.x, power_point.y, DOT_STATUS_WIDTH, DOT_STATUS_HEIGHT};
    for (int index = 1; index < PACMAN_POWER_STATE_TOTAL; index++)
    {
        if (power[index])
        {
            graphic->setTextureAlpha(OBJECT, 0xFF);
            graphic->draw(OBJECT_DOT_STATUS, index-1, destination);
            destination.x += OBJECT_PIXEL;
        }
    }

    return;
}

void GameStatus::renderScore()
{
    //render score in game
    if (!scoreObject.empty())
    {
        for (size_t index = 0; index < scoreObject.size(); index++)
        {
            graphic->renderScore(scoreObject[index].score_sprite, scoreObject[index].screen - Point(RESOURCES_PIXEL/2, RESOURCES_PIXEL/2));
        }
    }
    return;
}


Uint32 GameStatus::getScore()
{
    return score;
}
///update animation
void GameStatus::setAnimated(bool _animated)
{
    animated = _animated;
    return;
}

///level
int GameStatus::getLevel()
{
    return level;
}

void GameStatus::updateLevel()
{
    level++;
    return;
}
