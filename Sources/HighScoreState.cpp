///HighScoreState [Source]
#include "HighScoreState.h"

///Include header
#include <sstream>

///HighScoreState class
//Constructor:
HighScoreState::HighScoreState() : State()
{
    console = new Console("Highscore");

    background = new Background(BACKGROUND_HIGHSCORE);

    score.clear();

    return;
}

//Destructor:
HighScoreState::~HighScoreState()
{
    delete background;
    background = NULL;

    delete console;
    console = NULL;

    score.clear();

    return;
}

///function:
//init:
void HighScoreState::init(System* _system)
{
    system = _system;

    background->init(system->graphic);

    score.resize(10, 0);

    if (system->highscore_set.empty())
        system->loadHighscore();

    int cnt = 0;
    std::multiset<Uint32, std::greater<Uint32>>::iterator it;
    for (it = system->highscore_set.begin(); it != system->highscore_set.end(); ++it)
    {
        if (cnt == 10)
            break;
        score[cnt++] = (*it);
    }

    console->writeLine("Initialized HighScoreState");
    return;
}

//loop:
void HighScoreState::loop()
{
    return;
}

//render:
void HighScoreState::render()
{
    background->render();

    //render highscore table
    std::stringstream ss;
    std::string num;
    for (size_t index = 0; index < score.size(); index++)
    {
        ss.clear();
        ss << score[index];
        ss >> num;
        while (num.size() < 8)
            num = '0' + num;

        system->graphic->renderNumber(NUMBER_DEFAULT, num, HIGHSCORE_TABLE_POINT[index]);
    }

    return;
}

//handle key event:
void HighScoreState::keyPressed(const int key_code)
{
    system->audio->play(EFFECT_TYPE::CREDIT);
    return;
}

void HighScoreState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
            pull(CLOSE_STATE);
            break;
    }
    return;
}

//close:
void HighScoreState::close()
{
    console->writeLine("Closing state. . .");
    return;
}


