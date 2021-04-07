#include "StateManager.h"

void StateManager::addState(State* state)
{
    states.push(state);
    states.top()->init();
}

void StateManager::loop()
{
    if (checkState())
        states.top()->loop();
}

void StateManager::render()
{
    if (checkState())
        states.top()->render();
}

void StateManager::keyPressed(int key_code)
{
    if (checkState())
        states.top()->keyPressed(key_code);
}

void StateManager::keyReleased(int key_code)
{
    if (checkState())
        states.top()->keyReleased(key_code);
}

void StateManager::closeState()
{
    if (checkState())
    {
        states.top()->close();
        states.pop();
    }
}

bool StateManager::checkState()
{
    return (!states.empty());
}
