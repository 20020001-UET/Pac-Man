///AboutState [Source]
#include "AboutState.h"

///Include header

///AboutState class
//Constructor:
AboutState::AboutState() : State()
{
    console = new Console("About");

    background = new Background(BACKGROUND_ABOUT);

    return;
}

//Destructor:
AboutState::~AboutState()
{
    delete background;
    background = NULL;

    delete console;
    console = NULL;

    return;
}

///function:
//init:
void AboutState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    console->writeLine("Initialized AboutState");
    return;
}

//loop:
void AboutState::loop()
{
    return;
}

//render:
void AboutState::render()
{
    background->render();

    return;
}

//handle key event:
void AboutState::keyPressed(const int key_code)
{
    system->audio->play(EFFECT_TYPE::CREDIT);
    return;
}

void AboutState::keyReleased(const int key_code)
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
void AboutState::close()
{
    console->writeLine("Closing state. . .");
    return;
}


