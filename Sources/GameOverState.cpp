///GameOverState [Source]
#include "GameOverState.h"

///Include header
#include <sstream>

///GameOverState class
//Constructor:
GameOverState::GameOverState() : State()
{
    console = new Console("GameOver");

    background = new Background(BACKGROUND_GAME_OVER);

    return;
}

//Destructor:
GameOverState::~GameOverState()
{
    delete background;
    background = NULL;

    delete console;
    console = NULL;

    return;
}

///function:
//init:
void GameOverState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    console->writeLine("Initialized GameOverState");
    return;
}

//loop:
void GameOverState::loop()
{
    return;
}

//render:
void GameOverState::render()
{
    background->render();

    std::stringstream ss;
    std::string num;

    //render score
    ss << system->lastScore;
    ss >> num;
    while (num.size() < 8)
        num = '0' + num;

    system->graphic->renderNumber(NUMBER_DEFAULT, num, SCORE_GAME_OVER_POINT);

    //render level
    int curLevel = system->lastLevel + 1;
    SDL_Rect destination = {LEVEL_GAME_OVER_POINT.x - curLevel*OBJECT_PIXEL/2,
                            LEVEL_GAME_OVER_POINT.y, OBJECT_PIXEL, OBJECT_PIXEL};
    for (int index = 0; index < curLevel; index++)
    {
        system->graphic->draw(OBJECT_LEVEL, index, destination);
        destination.x += OBJECT_PIXEL;
    }

    return;
}

//handle key event:
void GameOverState::keyPressed(const int key_code)
{
    system->audio->play(EFFECT_TYPE::CREDIT);
    return;
}

void GameOverState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
            pull(MENU_STATE);
            break;
    }
    return;
}

//close:
void GameOverState::close()
{
    console->writeLine("Closing state. . .");
    return;
}
