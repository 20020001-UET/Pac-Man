///PlayingState [Source]
#include "PlayingState.h"

///Include header
#include "GhostAi.h"
#include "FruitAi.h"
#include <random>
#include <ctime>

///PlayingState class
//Constructor:
PlayingState::PlayingState() : State()
{
    console = new Console("Playing");

    background = new Background(BACKGROUND_PLAYING);

    labyrinth = new Labyrinth;

    //pacman. . .
    pacman = NULL;

    blinky = new Blinky;

    pinky = new Pinky;

    inky = new Inky;

    clyde = new Clyde;

    fruit = new Fruit;

    gameStatus = new GameStatus;

    return;
}

//Destructor:
PlayingState::~PlayingState()
{
    delete background;
    background = NULL;

    delete labyrinth;
    labyrinth = NULL;

    delete pacman;
    pacman = NULL;

    delete blinky;
    blinky = NULL;

    delete pinky;
    pinky = NULL;

    delete inky;
    inky = NULL;

    delete clyde;
    clyde = NULL;

    delete fruit;
    fruit = NULL;

    delete gameStatus;
    gameStatus = NULL;

    delete console;
    console = NULL;

    return;
}

///function:
//init:
void PlayingState::init(System* _system)
{
    system = _system;
    system->loadHighscore();

    background->init(system->graphic);

    labyrinth->init(system->graphic);
    labyrinth->load();

    pacman = new Pacman(PACMAN_TYPE_AT[system->mainCharacter]);
    pacman->init(system->graphic, system->timer, labyrinth->getPacmanStand());

    blinky->init(system->graphic, system->timer, labyrinth->getGhostStart(), labyrinth->getBlinkyStand(), Point(27, -1));
    pinky->init(system->graphic, system->timer, labyrinth->getGhostStart(), labyrinth->getPinkyStand(), Point(0, -1));
    inky->init(system->graphic, system->timer, labyrinth->getGhostStart(), labyrinth->getInkyStand(), Point(27, 32));
    clyde->init(system->graphic, system->timer, labyrinth->getGhostStart(), labyrinth->getClydeStand(), Point(0, 32));

    fruit->init(system->graphic, system->timer, Point(28, 14), Point(14, 17));

    gameStatus->init(pacman, system->graphic, system->timer, system->highscore, HIGHSCORE_POINT, SCORE_POINT, LIFE_POINT, LEVEL_POINT);

    getControl();

    srand(time(NULL));

    setState(NEW_GAME);

    console->writeLine("Initialized PlayingState");
    return;
}

//loop:
void PlayingState::loop()
{
    gameStatus->update();

    handleState();

    return;
}

//render:
void PlayingState::render()
{
    background->render();

    gameStatus->render();

    system->graphic->setViewPort(PLAYING_VIEWPORT);
    labyrinth->render();

    fruit->render();

    pacman->render();
    blinky->render();
    pinky->render();
    inky->render();
    clyde->render();

    gameStatus->renderScore();

    return;
}

//handle key event:
void PlayingState::keyPressed(const int key_code)
{
    if (curState != PLAYING_GAME && curState != END_GAME)
    {
        system->audio->play(EFFECT_TYPE::CREDIT);
        return;
    }

    if (key_code == controlKey[UP_KEY])
    {
        pacman->setDirection(UP);
        console->writeLine("Pacman up");
    }

    if (key_code == controlKey[RIGHT_KEY])
    {
        pacman->setDirection(RIGHT);
        console->writeLine("Pacman right");
    }

    if (key_code == controlKey[DOWN_KEY])
    {
        pacman->setDirection(DOWN);
        console->writeLine("Pacman down");
    }

    if (key_code == controlKey[LEFT_KEY])
    {
        pacman->setDirection(LEFT);
        console->writeLine("Pacman left");
    }

    return;
}

void PlayingState::keyReleased(const int key_code)
{
    switch (key_code)
    {
        case SDLK_ESCAPE:
        {
            system->timer->pause();
            system->audio->pause();
            pull(RESUME_STATE);
            break;
        }
    }
    return;
}

//close:
void PlayingState::close()
{
    console->writeLine("Closing state. . .");
    return;
}

///playing state
//set state:
void PlayingState::setState(STATE_OF_PLAYING newState)
{
    curState = newState;
    initState();
    return;
}

//initState:
void PlayingState::initState()
{
    switch (curState)
    {
        case NEW_GAME:
        {
            system->audio->play(MUSIC_TYPE::GAME_START);
            //Init object. . .
            labyrinth->setAnimated(true);
            gameStatus->setAnimated(true);

            blinky->setBehavior(GHOST_INIT);
            pinky->setBehavior(GHOST_INIT);
            inky->setBehavior(GHOST_INIT);
            clyde->setBehavior(GHOST_INIT);
            pacman->setState(PACMAN_INIT_STATE);

            fruit->setType(gameStatus->getLevel());
            fruit->setState(FRUIT_INIT);

            cur_dot_count = 0;

            break;
        }
        case NEW_LIFE_GAME:
        {
            system->audio->play(MUSIC_TYPE::GAME_START);
            labyrinth->setAnimated(true);
            gameStatus->setAnimated(true);

            blinky->setBehavior(GHOST_INIT);
            pinky->setBehavior(GHOST_INIT);
            inky->setBehavior(GHOST_INIT);
            clyde->setBehavior(GHOST_INIT);
            pacman->setState(PACMAN_NEW_STATE);

            break;
        }
        case PLAYING_GAME:
        {
            labyrinth->setAnimated(false);
            gameStatus->setAnimated(false);

            system->audio->play(EFFECT_TYPE::SIREN, true, 0);

            break;
        }
        case NEXT_LEVEL_GAME:
        {
            system->audio->play(MUSIC_TYPE::GAME_START);
            labyrinth->load();
            labyrinth->setAnimated(true);
            gameStatus->setAnimated(true);

            blinky->setBehavior(GHOST_INIT);
            pinky->setBehavior(GHOST_INIT);
            inky->setBehavior(GHOST_INIT);
            clyde->setBehavior(GHOST_INIT);
            pacman->setState(PACMAN_NEW_STATE);

            fruit->setType(gameStatus->getLevel());
            fruit->setState(FRUIT_INIT);

            cur_dot_count = 0;

            break;
        }
        case END_GAME:
        {
            system->audio->stopChannel();
            system->audio->play(EFFECT_TYPE::DEATH, false);
            pacman->setState(PACMAN_DEATH_STATE);
            break;
        }
        case WIN_GAME:
        {
            system->audio->play(MUSIC_TYPE::INTERMISSION);
            labyrinth->setAnimated(true);
            gameStatus->setAnimated(true);
        }
        default:
            break;
    }
    return;
}

//handleState:
void PlayingState::handleState()
{
    switch (curState)
    {
        case NEW_GAME:
        {
            if (!system->audio->isPlaying())
            {
                blinky->setBehavior(GHOST_SCATTER);
                setState(PLAYING_GAME);
            }
            break;
        }
        case NEW_LIFE_GAME:
        {
            if (!system->audio->isPlaying())
            {
                blinky->setBehavior(GHOST_SCATTER);
                setState(PLAYING_GAME);
            }
            break;
        }
        case PLAYING_GAME:
        {
            if (pacman->getState() == PACMAN_EATING_STATE)
            {
                pacman->loop();

                if (blinky->getBehavior() == GHOST_EATEN || blinky->getBehavior() == GHOST_REBORN)
                {
                    handleGhostTarget(blinky, pacman, blinky);
                    handleGhostMove(blinky, labyrinth);
                }

                if (pinky->getBehavior() == GHOST_EATEN || pinky->getBehavior() == GHOST_REBORN)
                {
                    handleGhostTarget(pinky, pacman, blinky);
                    handleGhostMove(pinky, labyrinth);
                }

                if (inky->getBehavior() == GHOST_EATEN || inky->getBehavior() == GHOST_REBORN)
                {
                    handleGhostTarget(inky, pacman, blinky);
                    handleGhostMove(inky, labyrinth);
                }

                if (clyde->getBehavior() == GHOST_EATEN || clyde->getBehavior() == GHOST_REBORN)
                {
                    handleGhostTarget(clyde, pacman, blinky);
                    handleGhostMove(clyde, labyrinth);
                }

                break;
            }

            if (labyrinth->pacmanCanMove(pacman->getTile(), pacman->getCurDirection()))
                pacman->loop();
            else
                pacman->stop();

            if (labyrinth->isDotHere(pacman->getTile()))
            //if (labyrinth->isDotHere(pacman->getScreen(), pacman->getCurDirection()))
            {
                cur_dot_count++;
                int power = labyrinth->isPowerDotHere(pacman->getTile());
                //int power = labyrinth->isPowerDotHere(pacman->getScreen(), pacman->getCurDirection());
                if (power == -1)
                {
                    system->audio->play(EFFECT_TYPE::MUNCH, false, 1);
                    system->audio->stopChannel(0);
                }
                else
                {
                    switch (power)
                    {
                        case POWER_DOT:
                        {
                            pacman->setPower(POWER_PACMAN);
                            blinky->setBehavior(GHOST_FRIGHTENED);
                            pinky->setBehavior(GHOST_FRIGHTENED);
                            inky->setBehavior(GHOST_FRIGHTENED);
                            clyde->setBehavior(GHOST_FRIGHTENED);
                            gameStatus->setGhostEaten();
                            break;
                        }
                        case SPEED_DOT:
                        {
                            pacman->setPower(SPEED_PACMAN);
                            break;
                        }
                        case INVISIBLE_DOT:
                        {
                            pacman->setPower(INVISIBLE_PACMAN);
                            blinky->setBehavior(GHOST_BLIND);
                            pinky->setBehavior(GHOST_BLIND);
                            inky->setBehavior(GHOST_BLIND);
                            clyde->setBehavior(GHOST_BLIND);
                            break;
                        }
                        case TIME_FREE_DOT:
                        {
                            pacman->setPower(FREE_TIME_PACMAN);
                            blinky->setBehavior(GHOST_FREEING);
                            pinky->setBehavior(GHOST_FREEING);
                            inky->setBehavior(GHOST_FREEING);
                            clyde->setBehavior(GHOST_FREEING);
                            break;
                        }
                    }
                    system->audio->play(EFFECT_TYPE::POWER_PELLET, false, -1);
                }
                pacman->eatDot();
                labyrinth->removeDot(pacman->getTile());
                //labyrinth->removeDot(pacman->getScreen(), pacman->getCurDirection());
            }

            if (labyrinth->isIntersection(pacman->getTile()))
                pacman->stop(labyrinth->pacmanCanMove(pacman->getTile(), pacman->getLastDirection()));

            handleGhostTarget(blinky, pacman, blinky);
            handleGhostTarget(pinky, pacman, blinky);
            handleGhostTarget(inky, pacman, blinky);
            handleGhostTarget(clyde, pacman, blinky);

            handleGhostMove(blinky, labyrinth);
            handleGhostMove(pinky, labyrinth);
            handleGhostMove(inky, labyrinth);
            handleGhostMove(clyde, labyrinth);

            bool isEndGame = false;

            switch (handleGhostHit(blinky, pacman))
            {
                case PACMAN_HIT_GHOST:
                    setState(END_GAME);
                    isEndGame = true;
                    break;
                case GHOST_HIT_PACMAN:
                    system->audio->play(EFFECT_TYPE::EAT_GHOST, false, 1);
                    gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, blinky->getScreen());
                    break;
                default:
                    break;
            }

            switch (handleGhostHit(pinky, pacman))
            {
                case PACMAN_HIT_GHOST:
                    setState(END_GAME);
                    isEndGame = true;
                    break;
                case GHOST_HIT_PACMAN:
                    system->audio->play(EFFECT_TYPE::EAT_GHOST, false, 1);
                    gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, pinky->getScreen());
                    break;
                default:
                    break;
            }

            switch (handleGhostHit(inky, pacman))
            {
                case PACMAN_HIT_GHOST:
                    setState(END_GAME);
                    isEndGame = true;
                    break;
                case GHOST_HIT_PACMAN:
                    system->audio->play(EFFECT_TYPE::EAT_GHOST, false, 1);
                    gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, inky->getScreen());
                    break;
                default:
                    break;
            }

            switch (handleGhostHit(clyde, pacman))
            {
                case PACMAN_HIT_GHOST:
                    setState(END_GAME);
                    isEndGame = true;
                    break;
                case GHOST_HIT_PACMAN:
                    system->audio->play(EFFECT_TYPE::EAT_GHOST, false, 1);
                    gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, clyde->getScreen());
                    break;
                default:
                    break;
            }

            if (isEndGame)
                break;

            handleFruitMove(fruit, labyrinth);

            if (handleFruitHit(fruit, pacman))
            {
                system->audio->play(EFFECT_TYPE::EAT_FRUIT, false, 1);
                gameStatus->pushScore(UPDATE_SCORE_EAT_FRUIT, fruit->getScreen());
                fruit->setState(FRUIT_STAND);
            }

            if (!system->audio->isPlayingChannel(1))
                if (!system->audio->isPlayingChannel(0))
                    system->audio->play(EFFECT_TYPE::SIREN, true, 0);

            if (cur_dot_count >= 50 && !pinky->isOutGhostHouse())
                pinky->setBehavior(GHOST_SCATTER);

            if (cur_dot_count >= 100 && !inky->isOutGhostHouse())
                inky->setBehavior(GHOST_SCATTER);

            if (cur_dot_count >= 150 && !clyde->isOutGhostHouse())
                clyde->setBehavior(GHOST_SCATTER);

            if (cur_dot_count >= 200 && !fruit->isOutOfStandPosition())
                fruit->setState(FRUIT_MOVING);

            if (labyrinth->isDotOver())
            {
                setState(WIN_GAME);
                break;
            }

            break;
        }
        case NEXT_LEVEL_GAME:
        {
            if (!system->audio->isPlaying())
            {
                blinky->setBehavior(GHOST_SCATTER);
                setState(PLAYING_GAME);
            }

            break;
        }
        case END_GAME:
        {
            if (!system->audio->isPlayingChannel())
            {
                if (!pacman->isDead())
                {
                    setState(NEW_LIFE_GAME);
                }
                else
                {
                    system->saveHighscore(gameStatus->getScore(), gameStatus->getLevel());
                    pull(GAME_OVER_STATE);
                }
            }

            break;
        }
        case WIN_GAME:
        {
            if (!system->audio->isPlaying())
            {
                gameStatus->updateLevel();
                setState(NEXT_LEVEL_GAME);
            }

            break;
        }
        default:
            break;
    }
    return;
}

///playing control
//get control:
void PlayingState::getControl()
{
    controlKey[UP_KEY] = system->control->getControl(CONTROL_UP);
    controlKey[RIGHT_KEY] = system->control->getControl(CONTROL_RIGHT);
    controlKey[DOWN_KEY] = system->control->getControl(CONTROL_DOWN);
    controlKey[LEFT_KEY] = system->control->getControl(CONTROL_LEFT);
    return;
}
