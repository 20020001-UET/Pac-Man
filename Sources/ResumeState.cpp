///ResumeState [Source]
#include "ResumeState.h"

///Include header

///ResumeState class
//Constructor:
ResumeState::ResumeState()
{
    console = new Console("Resume");

    background = new Background(BACKGROUND_RESUME);

    for (int index = 0; index < RESUME_BUTTON_TOTAL; index++)
        button[index] = new Button(RESUME_BUTTON_TYPE_AT[index], RESUME_BUTTON_TILE[index]);

    return;
}

//Destructor:
ResumeState::~ResumeState()
{
    delete background;
    background = NULL;

    for (int index = 0; index < RESUME_BUTTON_TOTAL; index++)
    {
        delete button[index];
        button[index] = NULL;
    }

    delete console;
    console = NULL;

    return;
}

///function:
//init:
void ResumeState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    for (int index = 0; index < RESUME_BUTTON_TOTAL; index++)
    {
        button[index]->init(system->graphic);
    }

    curButton = 0;
    button[curButton]->setClick(true);

    system->audio->pauseChannel(0);

    console->writeLine("Initialized ResumeState");
    return;
}

//loop:
void ResumeState::loop()
{
    return;
}

//render:
void ResumeState::render()
{
    background->render();
    for (int index = 0; index < RESUME_BUTTON_TOTAL; index++)
    {
        button[index]->render();
    }

    return;
}

//handle key event:
void ResumeState::keyPressed(const int key_code)
{
    system->audio->play(EFFECT_TYPE::CREDIT);

    switch (key_code)
    {
        case SDLK_UP:
            updateButton(-1);
            break;
        case SDLK_DOWN:
            updateButton(+1);
            break;
        default:
            break;
    }
    return;
}

void ResumeState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
            system->timer->unpause();
            system->audio->unpause();
            pull(CLOSE_STATE);
            break;
        case SDLK_RETURN:
            handleButton();
            break;
    }
    return;
}

//button function:
void ResumeState::updateButton(int change)
{
    button[curButton]->setClick(false);

    curButton += change;

    if (curButton < RESUME_BUTTON_REUSME) curButton = RESUME_BUTTON_EXIT;
    if (curButton > RESUME_BUTTON_EXIT) curButton = RESUME_BUTTON_REUSME;

    button[curButton]->setClick(true);
    return;
}

void ResumeState::handleButton()
{
    system->timer->unpause();
    switch (curButton)
    {
        case RESUME_BUTTON_REUSME:
        {
            system->audio->unpause();
            system->audio->unpauseChannel(0);
            pull(CLOSE_STATE);
            break;
        }
        case RESUME_BUTTON_EXIT:
            system->audio->stop();
            pull(EXIT_GAME_STATE);
            break;
        default:
            break;
    }
    return;
}

void ResumeState::close()
{
    console->writeLine("Closing state. . .");

    return;
}
