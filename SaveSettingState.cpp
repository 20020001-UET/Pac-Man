///SaveSettingState [Source]
#include "SaveSettingState.h"

///Include header

///SaveSettingState class
//Constructor:
SaveSettingState::SaveSettingState()
{
    console = new Console("SaveSetting");

    background = new Background(BACKGROUND_SAVE_SETTING);

    for (int index = 0; index < SAVE_SETTING_BUTTON_TOTAL; index++)
        button[index] = new Button(SAVE_SETTING_BUTTON_TYPE_AT[index], SAVE_SETTING_BUTTON_TILE[index]);

    return;
}

//Destructor:
SaveSettingState::~SaveSettingState()
{
    delete background;
    background = NULL;

    for (int index = 0; index < SAVE_SETTING_BUTTON_TOTAL; index++)
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
void SaveSettingState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    for (int index = 0; index < SAVE_SETTING_BUTTON_TOTAL; index++)
    {
        button[index]->init(system->graphic);
    }

    curButton = 0;
    button[curButton]->setClick(true);

    console->writeLine("Initialized SaveSettingState");
    return;
}

//loop:
void SaveSettingState::loop()
{
    return;
}

//render:
void SaveSettingState::render()
{
    background->render();
    for (int index = 0; index < SAVE_SETTING_BUTTON_TOTAL; index++)
    {
        button[index]->render();
    }

    return;
}

//handle key event:
void SaveSettingState::keyPressed(const int key_code)
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

void SaveSettingState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
            pull(CLOSE_STATE);
            break;
        case SDLK_RETURN:
            handleButton();
            break;
    }
    return;
}

//button function:
void SaveSettingState::updateButton(int change)
{
    button[curButton]->setClick(false);

    curButton += change;

    if (curButton < SAVE_SETTING_BUTTON_YES) curButton = SAVE_SETTING_BUTTON_NO;
    if (curButton > SAVE_SETTING_BUTTON_NO) curButton = SAVE_SETTING_BUTTON_YES;

    button[curButton]->setClick(true);
    return;
}

void SaveSettingState::handleButton()
{
    switch (curButton)
    {
        case SAVE_SETTING_BUTTON_YES:
            system->save();
            break;
        case SAVE_SETTING_BUTTON_NO:
            system->load();
            break;
        default:
            break;
    }
    pull(RETURN_STATE);
    return;
}

void SaveSettingState::close()
{
    console->writeLine("Closing state. . .");

    return;
}
