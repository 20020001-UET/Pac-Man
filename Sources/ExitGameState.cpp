///ExitGameState [Source]
#include "ExitGameState.h"

///Include header

///ExitGameState class
//Constructor:
ExitGameState::ExitGameState()
{
    console = new Console("ExitGame");

    background = new Background(BACKGROUND_EXIT_GAME);

    for (int index = 0; index < EXIT_GAME_BUTTON_TOTAL; index++)
        button[index] = new Button(EXIT_GAME_BUTTON_TYPE_AT[index], EXIT_GAME_BUTTON_TILE[index]);

    return;
}

//Destructor:
ExitGameState::~ExitGameState()
{
    delete background;
    background = NULL;

    for (int index = 0; index < EXIT_GAME_BUTTON_TOTAL; index++)
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
void ExitGameState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    for (int index = 0; index < EXIT_GAME_BUTTON_TOTAL; index++)
    {
        button[index]->init(system->graphic);
    }

    curButton = 0;
    button[curButton]->setClick(true);

    console->writeLine("Initialized ExitGameState");
    return;
}

//loop:
void ExitGameState::loop()
{
    return;
}

//render:
void ExitGameState::render()
{
    background->render();
    for (int index = 0; index < EXIT_GAME_BUTTON_TOTAL; index++)
    {
        button[index]->render();
    }

    return;
}

//handle key event:
void ExitGameState::keyPressed(const int key_code)
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

void ExitGameState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
            system->timer->unpause();
            pull(CLOSE_STATE);
            break;
        case SDLK_RETURN:
            handleButton();
            break;
    }
    return;
}

//button function:
void ExitGameState::updateButton(int change)
{
    button[curButton]->setClick(false);

    curButton += change;

    if (curButton < EXIT_GAME_BUTTON_YES) curButton = EXIT_GAME_BUTTON_NO;
    if (curButton > EXIT_GAME_BUTTON_NO) curButton = EXIT_GAME_BUTTON_YES;

    button[curButton]->setClick(true);
    return;
}

void ExitGameState::handleButton()
{
    system->timer->unpause();
    switch (curButton)
    {
        case EXIT_GAME_BUTTON_YES:
            pull(MENU_STATE);
            break;
        case EXIT_GAME_BUTTON_NO:
        {
            system->audio->unpauseChannel(0);
            pull(RETURN_STATE);
            break;
        }
        default:
            break;
    }
    return;
}

void ExitGameState::close()
{
    console->writeLine("Closing state. . .");

    return;
}
