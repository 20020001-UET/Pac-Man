#include "HowToPlayState.h"

#include "Engine.h"
#include "Resources.h"

void HowToPlayState::init()
{
    console = new Console("HowToPlayState");

    background = new Background(HOW_TO_PLAY_MENU, false);
}

void HowToPlayState::loop()
{

}

void HowToPlayState::render()
{
    background->render();
}

void HowToPlayState::keyPressed(int key_sym)
{
    console->writeLine("Key pressed.");

    switch (key_sym)
    {
        case SDLK_ESCAPE:
            Engine::stateClose();
            break;

        default:
            break;
    }
}

void HowToPlayState::keyReleased(int key_sym)
{
    console->writeLine("Key released.");
}

void HowToPlayState::close()
{
    console->writeLine("Closing state. . .");

    delete background;
    background = NULL;

    delete console;
    console = NULL;
}

