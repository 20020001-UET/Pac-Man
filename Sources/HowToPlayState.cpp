///HowToPlayState [Source]
#include "HowToPlayState.h"

///Include header

///HowToPlayState class
//Constructor:
HowToPlayState::HowToPlayState() : State()
{
    console = new Console("HowToPlay");

    background = new Background(BACKGROUND_HOW_TO_PLAY);

    return;
}

//Destructor:
HowToPlayState::~HowToPlayState()
{
    delete background;
    background = NULL;

    delete console;
    console = NULL;

    return;
}

///function:
//init:
void HowToPlayState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    console->writeLine("Initialized HowToPlayState");
    return;
}

//loop:
void HowToPlayState::loop()
{
    return;
}

//render:
void HowToPlayState::render()
{
    background->render();

    return;
}

//handle key event:
void HowToPlayState::keyPressed(const int key_code)
{
    system->audio->play(EFFECT_TYPE::CREDIT);
    return;
}

void HowToPlayState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
            pull(CLOSE_STATE);
            break;
    }
    return;
}

//close:
void HowToPlayState::close()
{
    console->writeLine("Closing state. . .");
    return;
}


