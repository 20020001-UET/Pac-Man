///HighScoreState [Source]
#include "HighScoreState.h"

///Include header

///HighScoreState class
//Constructor:
HighScoreState::HighScoreState() : State()
{
    console = new Console("Highscore");

    background = new Background(BACKGROUND_HIGHSCORE);

    return;
}

//Destructor:
HighScoreState::~HighScoreState()
{
    delete background;
    background = NULL;

    delete console;
    console = NULL;

    return;
}

///function:
//init:
void HighScoreState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    console->writeLine("Initialized HighScoreState");
    return;
}

//loop:
void HighScoreState::loop()
{
    return;
}

//render:
void HighScoreState::render()
{
    background->render();

    return;
}

//handle key event:
void HighScoreState::keyPressed(const int key_code)
{
    system->audio->play(EFFECT_TYPE::CREDIT);
    return;
}

void HighScoreState::keyReleased(const int key_code)
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
void HighScoreState::close()
{
    console->writeLine("Closing state. . .");
    return;
}


