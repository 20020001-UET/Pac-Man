///SettingState [Source]
#include "SettingState.h"

///Include header

///SettingState class
//Constructor:
SettingState::SettingState() : State()
{
    console = new Console("Setting");

    background = new Background(BACKGROUND_SETTING);

    for (int index = 0; index < SETTING_BUTTON_TYPE_TOTAL; index++)
        setting_button[index] = new SettingButton(SETTING_BUTTON_TYPE_AT[index], SETTING_BUTTON_TILE[index]);

    return;
}

//Destructor:
SettingState::~SettingState()
{
    delete background;
    background = NULL;

    for (int index = 0; index < SETTING_BUTTON_TYPE_TOTAL; index++)
    {
        delete setting_button[index];
        setting_button[index] = NULL;
    }

    delete console;
    console = NULL;

    return;
}

///function:
//init:
void SettingState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    for (int index = 0; index < SETTING_BUTTON_TYPE_TOTAL; index++)
    {
        setting_button[index]->init(system->graphic);
    }

    setting_button[SETTING_BUTTON_VOLUME_MUSIC]->setState(system->musicVolume);
    setting_button[SETTING_BUTTON_VOLUME_SOUND]->setState(system->channelVolume);
    setting_button[SETTING_BUTTON_CONTROL]->setState(system->controlType);
    setting_button[SETTING_BUTTON_GRAPHIC]->setState(system->zoomScale);

    curButton = 0;
    setting_button[curButton]->setClick(true);

    changed = false;

    console->writeLine("Initialized SettingState");
    return;
}

//loop:
void SettingState::loop()
{
    return;
}

//render:
void SettingState::render()
{
    background->render();

    for (int index = 0; index < SETTING_BUTTON_TYPE_TOTAL; index++)
    {
        setting_button[index]->render();
    }

    return;
}

//handle key event:
void SettingState::keyPressed(const int key_code)
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
        case SDLK_LEFT:
            updateState(-1);
            break;
        case SDLK_RIGHT:
            updateState(+1);
            break;
        default:
            break;
    }
    return;
}

void SettingState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
            {
                if (changed)
                    pull(SAVE_SETTING_STATE);
                else
                    pull(CLOSE_STATE);
                break;
            }
    }
    return;
}

///button function:
//update:
void SettingState::updateButton(int change)
{
    setting_button[curButton]->setClick(false);

    curButton += change;

    if (curButton < SETTING_BUTTON_VOLUME_MUSIC) curButton = SETTING_BUTTON_GRAPHIC;
    if (curButton > SETTING_BUTTON_GRAPHIC) curButton = SETTING_BUTTON_VOLUME_MUSIC;

    setting_button[curButton]->setClick(true);
    return;
}

void SettingState::updateState(int change)
{
    changed = true;

    setting_button[curButton]->updateState(change);
    int newState = setting_button[curButton]->getState();
    switch (curButton)
    {
        case SETTING_BUTTON_VOLUME_MUSIC:
            system->musicVolume = newState;
            break;
        case SETTING_BUTTON_VOLUME_SOUND:
            system->channelVolume = newState;
            break;
        case SETTING_BUTTON_CONTROL:
            system->controlType = newState;
            break;
        case SETTING_BUTTON_GRAPHIC:
            system->zoomScale = newState;
            break;
        default:
            break;
    }

    system->update();

    return;
}

//close:
void SettingState::close()
{
    console->writeLine("Closing state. . .");
    return;
}
