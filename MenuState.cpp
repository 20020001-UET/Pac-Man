///MenuState [Source]
#include "MenuState.h"

///Include header

///MenuState class
//Constructor:
MenuState::MenuState() : State()
{
    console = new Console("Menu");

    background = new Background(BACKGROUND_MENU);

    for (int index = 0; index < MENU_BUTTON_TOTAL; index++)
        button[index] = new Button(MENU_BUTTON_TYPE_AT[index], MENU_BUTTON_TILE[index]);

    return;
}

//Destructor:
MenuState::~MenuState()
{
    delete background;
    background = NULL;

    for (int index = 0; index < MENU_BUTTON_TOTAL; index++)
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
void MenuState::init(System* _system)
{
    system = _system;
    background->init(system->graphic);

    for (int index = 0; index < MENU_BUTTON_TOTAL; index++)
    {
        button[index]->init(system->graphic);
    }

    curButton = 0;
    button[curButton]->setClick(true);

    console->writeLine("Initialized MenuState");
    return;
}

//loop:
void MenuState::loop()
{
    return;
}

//render:
void MenuState::render()
{
    background->render();
    for (int index = 0; index < MENU_BUTTON_TOTAL; index++)
    {
        button[index]->render();
    }

    return;
}

//handle key event:
void MenuState::keyPressed(const int key_code)
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

void MenuState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_RETURN:
            handleButton();
            break;
    }
    return;
}

//button function:
void MenuState::updateButton(int change)
{
    button[curButton]->setClick(false);

    curButton += change;

    if (curButton < MENU_BUTTON_START) curButton = MENU_BUTTON_EXIT;
    if (curButton > MENU_BUTTON_EXIT) curButton = MENU_BUTTON_START;

    button[curButton]->setClick(true);
    return;
}

void MenuState::handleButton()
{
    switch (curButton)
    {
        case MENU_BUTTON_START:
            pull(PLAYING_STATE);
            break;
        case MENU_BUTTON_HOW_TO_PLAY:
            pull(HOW_TO_PLAY_STATE);
            break;
        case MENU_BUTTON_SETTING:
            pull(SETTING_STATE);
            break;
        case MENU_BUTTON_HIGHSCORE:
            pull(HIGHSCORE_STATE);
            break;
        case MENU_BUTTON_ABOUT:
            pull(ABOUT_STATE);
            break;
        case MENU_BUTTON_EXIT:
            pull(EXIT_STATE);
            break;
        default:
            break;
    }
    return;
}

void MenuState::close()
{
    console->writeLine("Closing state. . .");

    return;
}
