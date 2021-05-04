///WinGameState [Source]
#include "WinGameState.h"

///Include header
#include <sstream>

///WinGameState class
//Constructor:
WinGameState::WinGameState() : State()
{
    console = new Console("WinGame");

    background = new Background(BACKGROUND_WIN_GAME);

    return;
}

//Destructor:
WinGameState::~WinGameState()
{
    delete background;
    background = NULL;

    delete console;
    console = NULL;

    return;
}

///function:
//init:
void WinGameState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    console->writeLine("Initialized WinGameState");
    return;
}

//loop:
void WinGameState::loop()
{
    return;
}

//render:
void WinGameState::render()
{
    background->render();

    std::stringstream ss;
    std::string num;

    //render score
    ss << system->lastScore;
    ss >> num;
    while (num.size() < 8)
        num = '0' + num;

    system->graphic->renderNumber(NUMBER_DEFAULT, num, SCORE_WIN_GAME_POINT);

    /*
    //render level
    int curLevel = system->lastLevel + 1;
    SDL_Rect destination = {LEVEL_GAME_OVER_POINT.x - curLevel*OBJECT_PIXEL/2,
                            LEVEL_GAME_OVER_POINT.y, OBJECT_PIXEL, OBJECT_PIXEL};
    for (int index = 0; index < curLevel; index++)
    {
        system->graphic->draw(OBJECT_LEVEL, index, destination);
        destination.x += OBJECT_PIXEL;
    }
    */

    return;
}

//handle key event:
void WinGameState::keyPressed(const int key_code)
{
    system->audio->play(EFFECT_TYPE::CREDIT);
    return;
}

void WinGameState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
        case SDLK_RETURN:
            pull(MENU_STATE);
            break;
    }
    return;
}

//close:
void WinGameState::close()
{
    console->writeLine("Closing state. . .");
    return;
}
