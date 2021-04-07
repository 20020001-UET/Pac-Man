#include "AboutState.h"

#include "Engine.h"
#include "Resources.h"

void AboutState::init()
{
    console = new Console("AboutState");

    background = new Background(ABOUT_MENU, false);
}

void AboutState::loop()
{

}

void AboutState::render()
{
    background->render();
}

void AboutState::keyPressed(int key_sym)
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

void AboutState::keyReleased(int key_sym)
{
    console->writeLine("Key released.");
}

void AboutState::close()
{
    console->writeLine("Closing state. . .");

    delete background;
    background = NULL;

    delete console;
    console = NULL;
}

