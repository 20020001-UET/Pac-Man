///State Manager [Source]
#include "StateManager.h"

///Include header
#include "MenuState.h"
#include "PlayingState.h"
#include "HowToPlayState.h"
#include "SettingState.h"
#include "HighScoreState.h"
#include "AboutState.h"
#include "ResumeState.h"
#include "SaveSettingState.h"
#include "ExitGameState.h"
#include "GameOverState.h"
#include "WinGameState.h"

///State Manager class
//Constructor:
StateManager::StateManager()
{
    console = new Console("State Manager");
    return;
}

//Destructor:
StateManager::~StateManager()
{
    delete console;
    console = NULL;

    system = NULL;

    return;
}

///main function:
//init:
void StateManager::init(System* _system)
{
    system = _system;

    console->writeLine("Initialized State Manager");

    add(new MenuState);

    return;
}

//close:
void StateManager::close()
{
    console->writeLine("Closing State Manager. . .");

    while (!isEmpty())
        remove();

    return;
}

///state function:
//add:
void StateManager::add(State* state)
{
    states.push(state);
    states.top()->init(system);
    return;
}

//loop:
void StateManager::loop()
{
    if (!isEmpty())
        states.top()->loop();
    return;
}

//render:
void StateManager::render()
{
    if (!isEmpty())
        states.top()->render();
    return;
}

//handle key event:
void StateManager::keyPressed(const int key_code)
{
    if (!isEmpty())
        states.top()->keyPressed(key_code);
    return;
}

void StateManager::keyReleased(const int key_code)
{
    if (!isEmpty())
        states.top()->keyReleased(key_code);
    return;
}

//remove:
void StateManager::remove()
{
    if (!isEmpty())
    {
        //create a pointer to the last top element
        State* tmpState = states.top();

        states.top()->close();
        states.pop();

        //delete the old state
        delete tmpState;
        tmpState = NULL;
    }
    return;
}

//is the stack empty?
bool StateManager::isEmpty()
{
    return states.empty();
}

//state request:
bool StateManager::pullRequest()
{
    bool running = true;
    if (!isEmpty())
    {
        if (states.top()->request() != UNSET_STATE)
        {
            STATE_TYPE stateType = states.top()->request();
            states.top()->pulled();
            switch (stateType)
            {
                case MENU_STATE:
                    {
                        while (!isEmpty())
                            remove();
                        add(new MenuState);
                        break;
                    }
                case PLAYING_STATE:
                    add(new PlayingState);
                    break;
                case HOW_TO_PLAY_STATE:
                    add(new HowToPlayState);
                    break;
                case SETTING_STATE:
                    add(new SettingState);
                    break;
                case HIGHSCORE_STATE:
                    add(new HighScoreState);
                    break;
                case ABOUT_STATE:
                    add(new AboutState);
                    break;
                case RESUME_STATE:
                    add(new ResumeState);
                    break;
                case SAVE_SETTING_STATE:
                    add(new SaveSettingState);
                    break;
                case EXIT_GAME_STATE:
                    add(new ExitGameState);
                    break;
                case GAME_OVER_STATE:
                    add(new GameOverState);
                    break;
                case WIN_GAME_STATE:
                    add(new WinGameState);
                    break;
                case RETURN_STATE:
                    {
                        remove();
                        remove();
                        break;
                    }
                case CLOSE_STATE:
                    remove();
                    break;
                case EXIT_STATE:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }
    return running;
}
