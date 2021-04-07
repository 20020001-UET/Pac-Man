#include "MenuState.h"

#include "Engine.h"
#include "Resources.h"
#include "HowToPlayState.h"
#include "AboutState.h"
#include "Playing.h"

void MenuState::init()
{
    console = new Console("MenuState");

    background = new Background(MAIN_MENU, true);
    cur_button = 0;
    button = new Button(6, 15, BUTTON_WIDTH, BUTTON_HEIGHT, button_at[cur_button]);
}

void MenuState::loop()
{
    button->setType(button_at[cur_button]);
    button->setTile(button_point[cur_button]);
}

void MenuState::render()
{
    background->render();
    button->render();
}

void MenuState::keyPressed(int key_sym)
{
    console->writeLine("Key pressed.");

    switch (key_sym)
    {
        case SDLK_UP:
            cur_button--;
            break;

        case SDLK_DOWN:
            cur_button++;
            break;

        case SDLK_RETURN:
            handleButton();
            return;
            break;

        default:
            break;
    }

    if (cur_button > 4)
        cur_button = 0;
    if (cur_button < 0)
        cur_button = 4;
}

void MenuState::keyReleased(int key_sym)
{
    console->writeLine("Key released.");
}

void MenuState::close()
{
    console->writeLine("Closing state. . .");

    delete background;
    background = NULL;

    delete console;
    console = NULL;
}

void MenuState::handleButton()
{
    switch (button_at[cur_button])
    {
        case START:
            Engine::stateAdd(new Playing);
            break;

        case HOW_TO_PLAY:
            Engine::stateAdd(new HowToPlayState);
            break;

        case SETTING:
            break;

        case ABOUT:
            Engine::stateAdd(new AboutState);
            break;

        case EXIT:
            Engine::stateExit();
            break;

        default:
            break;
    }
    return;
}
