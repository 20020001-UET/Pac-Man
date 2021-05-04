///PlayingState [Source]
#include "PlayingState.h"

///Include header
#include "GhostAi.h"
#include "FruitAi.h"
#include "MysteryAi.h"
#include "GoldenAi.h"
#include "Distance.h"
#include <random>
#include <ctime>
#include <iostream>

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
    deadly = new Deadly;

    pinky = new Pinky;
    speedy = new Speedy;

    inky = new Inky;
    invisy = new Invisy;

    clyde = new Clyde;
    freezy = new Freezy;

    fruit = new Fruit;

    mystery = new Mystery;
    golden = new Golden;

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
    delete deadly;
    deadly = NULL;

    delete pinky;
    pinky = NULL;
    delete speedy;
    speedy = NULL;

    delete inky;
    inky = NULL;
    delete invisy;
    invisy = NULL;

    delete clyde;
    clyde = NULL;
    delete freezy;
    freezy = NULL;

    delete fruit;
    fruit = NULL;

    delete mystery;
    mystery = NULL;
    delete golden;
    golden = NULL;

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

    blinky->init(system->graphic, system->timer, labyrinth->getGhostStart(), labyrinth->getBlinkyStand(), Point(27, -1), Point(14, 17));
    deadly->init(system->graphic, system->timer, Point(14, 17), labyrinth->getGhostStart(), labyrinth->getBlinkyStand(), Point(27, -1));

    pinky->init(system->graphic, system->timer, labyrinth->getGhostStart(), labyrinth->getPinkyStand(), Point(0, -1), Point(14, 17));
    speedy->init(system->graphic, system->timer, Point(14, 17), labyrinth->getGhostStart(), labyrinth->getPinkyStand(), Point(0, -1));

    inky->init(system->graphic, system->timer, labyrinth->getGhostStart(), labyrinth->getInkyStand(), Point(27, 32), Point(14, 17));
    invisy->init(system->graphic, system->timer, Point(14, 17), labyrinth->getGhostStart(), labyrinth->getInkyStand(), Point(27, 32));

    clyde->init(system->graphic, system->timer, labyrinth->getGhostStart(), labyrinth->getClydeStand(), Point(0, 32), Point(14, 17));
    freezy->init(system->graphic, system->timer, Point(14, 17), labyrinth->getGhostStart(), labyrinth->getClydeStand(), Point(0, 32));

    fruit->init(system->graphic, system->timer, Point(28, 14), Point(14, 17));

    mystery->init(system->graphic, system->timer, Point(-1, 14), Point (13, 17), Point(11, 17), Point(13, 17));
    mystery->setSpeechPoint(MYSTERY_SPEECH_UPGRADE_POINT, MYSTERY_SPEECH_SHOW_UP_POINT);
    golden->init(system->graphic, system->timer, labyrinth->getGhostStart(), Point(14, 17));

    gameStatus->init(pacman, system->graphic, system->timer, system->highscore, HIGHSCORE_POINT, SCORE_POINT, LIFE_POINT, LEVEL_POINT, POWER_POINT);
    gameStatus->initBoss(golden);

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

    renderGhost(blinky, deadly);
    renderGhost(pinky, speedy);
    renderGhost(inky, invisy);
    renderGhost(clyde, freezy);

    if (!golden->isShowedUp())
        mystery->render();
    else
        golden->render();

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
        if (!pacman->isPacmanPower(CONFUSED_PACMAN))
            pacman->setDirection(UP);
        else
            pacman->setDirection(DOWN);
        console->writeLine("Pacman up");
    }

    if (key_code == controlKey[RIGHT_KEY])
    {
        if (!pacman->isPacmanPower(CONFUSED_PACMAN))
            pacman->setDirection(RIGHT);
        else
            pacman->setDirection(LEFT);
        console->writeLine("Pacman right");
    }

    if (key_code == controlKey[DOWN_KEY])
    {
        if (!pacman->isPacmanPower(CONFUSED_PACMAN))
            pacman->setDirection(DOWN);
        else
            pacman->setDirection(UP);
        console->writeLine("Pacman down");
    }

    if (key_code == controlKey[LEFT_KEY])
    {
        if (!pacman->isPacmanPower(CONFUSED_PACMAN))
            pacman->setDirection(LEFT);
        else
            pacman->setDirection(RIGHT);
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
            mystery->setState(MYSTERY_INIT);

            //cur_dot_count = 0;
            cur_dot_count = 150;

            break;
        }
        case NEW_LIFE_GAME:
        {
            system->audio->play(MUSIC_TYPE::GAME_START);
            labyrinth->setAnimated(true);
            gameStatus->setAnimated(true);

            initGhostInit(blinky, deadly);
            initGhostInit(pinky, speedy);
            initGhostInit(inky, invisy);
            initGhostInit(clyde, freezy);
            pacman->setState(PACMAN_NEW_STATE);

            break;
        }
        case UPGRADE_GHOST_GAME:
        {
            system->audio->pauseChannel(0);
            labyrinth->setAnimated(false);
            gameStatus->setAnimated(false);
            mystery->setState(MYSTERY_INIT);
            golden->setState(GOLDEN_INIT_STATE);

            if (gameStatus->getLevel() == 1)
            {
                mystery->setState(MYSTERY_MOVING);
                system->audio->play(EFFECT_TYPE::SIREN, true, 0);
            }
            if (gameStatus->getLevel() == 2)
            {
                initUpgrade(blinky, deadly);
            }
            if (gameStatus->getLevel() == 3)
            {
                initUpgrade(pinky, speedy);
            }
            if (gameStatus->getLevel() == 4)
            {
                initUpgrade(inky, invisy);
            }
            if (gameStatus->getLevel() == 5)
            {
                initUpgrade(clyde, freezy);
            }
            if (gameStatus->getLevel() == 7)
            {
                mystery->setState(MYSTERY_MOVING_TO_SHOW_UP);
                deadly->setTarget(mystery->getUpgrade());
                speedy->setTarget(mystery->getUpgrade());
                invisy->setTarget(mystery->getUpgrade());
                freezy->setTarget(mystery->getUpgrade());
                system->audio->play(EFFECT_TYPE::SIREN, true, 0);
            }

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

            initGhostInit(blinky, deadly);
            initGhostInit(pinky, speedy);
            initGhostInit(inky, invisy);
            initGhostInit(clyde, freezy);
            pacman->setState(PACMAN_NEW_STATE);

            fruit->setType(gameStatus->getLevel());
            fruit->setState(FRUIT_INIT);

            mystery->setState(MYSTERY_INIT);

            //cur_dot_count = 0;
            cur_dot_count = 150;

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
                if (!blinky->isUpgraded())
                    blinky->setBehavior(GHOST_SCATTER);
                else
                    deadly->setBehavior(UNIQUE_GHOST_SCATTER);

                golden->setTile(golden->getStartPoint());
                if (golden->isShowedUp())
                    golden->setState(GOLDEN_RUNNING_STATE);

                setState(PLAYING_GAME);
            }
            break;
        }
        case UPGRADE_GHOST_GAME:
        {
            if (gameStatus->getLevel() == 1)
            {
                handleMysteryMove(mystery, labyrinth);
                mystery->handleState();
                if (mystery->getState() == MYSTERY_STAND)
                {
                    setState(NEXT_LEVEL_GAME);
                    system->audio->stopChannel(0);
                }
                else
                {
                    if (mystery->getState() == MYSTERY_WAITING)
                    {
                        system->audio->stopChannel(0);
                    }
                    else
                    {
                        if (!system->audio->isPlayingChannel(0))
                            system->audio->play(EFFECT_TYPE::SIREN, true, 0);
                    }
                }
            }
            if (gameStatus->getLevel() == 2)
            {
                handleUpgrade(blinky, deadly);
            }
            if (gameStatus->getLevel() == 3)
            {
                handleUpgrade(pinky, speedy);
            }
            if (gameStatus->getLevel() == 4)
            {
                handleUpgrade(inky, invisy);
            }
            if (gameStatus->getLevel() == 5)
            {
                handleUpgrade(clyde, freezy);
            }
            if (gameStatus->getLevel() == 7)
            {
                handleMysteryMove(mystery, labyrinth);
                mystery->handleState();

                if (deadly->getTile() == deadly->getTarget())
                    deadly->setBehavior(UNIQUE_GHOST_WAIT);

                if (speedy->getTile() == speedy->getTarget())
                    speedy->setBehavior(UNIQUE_GHOST_WAIT);

                if (invisy->getTile() == invisy->getTarget())
                    invisy->setBehavior(UNIQUE_GHOST_WAIT);

                if (freezy->getTile() == freezy->getTarget())
                    freezy->setBehavior(UNIQUE_GHOST_WAIT);

                if (mystery->getState() == MYSTERY_SPEECH_SHOW_UP || mystery->getState() == MYSTERY_WAITING_TO_SHOW_UP)
                {
                    handleGhostMove(deadly, labyrinth);
                    handleGhostMove(speedy, labyrinth);
                    handleGhostMove(invisy, labyrinth);
                    handleGhostMove(freezy, labyrinth);
                }

                if (mystery->getState() == MYSTERY_SPEECH_SHOW_UP && golden->getState() != GOLDEN_SHOW_UP_STATE)
                {
                    system->audio->stopChannel(0);
                    if (!system->audio->isPlayingChannel(-1))
                        system->audio->play(EFFECT_TYPE::BOSS_SHOW_UP, false, -1);
                }

                if (mystery->getState() == MYSTERY_WAITING_TO_SHOW_UP && golden->getState() != GOLDEN_SHOW_UP_STATE && !system->audio->isPlayingChannel(-1))
                {
                    system->audio->play(EFFECT_TYPE::UPGRADE_MYSTERY, false, -1);
                    golden->setState(GOLDEN_SHOW_UP_STATE);
                    gameStatus->setHP();
                }

                if (golden->getState() == GOLDEN_SHOW_UP_STATE)
                {
                    if (!system->audio->isPlayingChannel(-1))
                    {
                        setState(NEXT_LEVEL_GAME);
                    }
                }
            }

            break;
        }
        case PLAYING_GAME:
        {
            if (golden->isShowedUp())
            {
                if (golden->getState() == GOLDEN_DEATH_STATE)
                {
                    //std::cout << golden->isDead() << '\n';
                    golden->handleState();
                    break;
                }
            }

            pacman->handlePower();

            handleGhostMode(blinky, deadly);
            handleGhostMode(pinky, speedy);
            handleGhostMode(inky, invisy);
            handleGhostMode(clyde, freezy);
            if (golden->isShowedUp())
                golden->handleMode();

            if (pacman->getState() == PACMAN_EATING_STATE)
            {
                pacman->loop();

                handleGhostDeadLoop(blinky, deadly, blinky, deadly);
                handleGhostDeadLoop(pinky, speedy, blinky, deadly);
                handleGhostDeadLoop(inky, invisy, blinky, deadly);
                handleGhostDeadLoop(clyde, freezy, blinky, deadly);

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
                    system->audio->play(EFFECT_TYPE::MUNCH, false, -1);
                    system->audio->stopChannel(0);
                }
                else
                {
                    switch (power)
                    {
                        case POWER_DOT:
                        {
                            pacman->setPower(POWER_PACMAN);

                            setGhostBehavior(blinky, deadly, BEHAVIOR_FRIGHTENED);
                            setGhostBehavior(pinky, speedy, BEHAVIOR_FRIGHTENED);
                            setGhostBehavior(inky, invisy, BEHAVIOR_FRIGHTENED);
                            setGhostBehavior(clyde, freezy, BEHAVIOR_FRIGHTENED);

                            gameStatus->setGhostEaten();

                            system->audio->play(EFFECT_TYPE::POWER_PELLET, false, -1);
                            break;
                        }
                        case SPEED_DOT:
                        {
                            pacman->setPower(SPEED_PACMAN);

                            system->audio->play(EFFECT_TYPE::SPEED, false, -1);
                            break;
                        }
                        case INVISIBLE_DOT:
                        {
                            pacman->setPower(INVISIBLE_PACMAN);

                            setGhostBehavior(blinky, deadly, BEHAVIOR_BLIND);
                            setGhostBehavior(pinky, speedy, BEHAVIOR_BLIND);
                            setGhostBehavior(inky, invisy, BEHAVIOR_BLIND);
                            setGhostBehavior(clyde, freezy, BEHAVIOR_BLIND);

                            system->audio->play(EFFECT_TYPE::POWER_PELLET, false, -1);
                            break;
                        }
                        case TIME_FREE_DOT:
                        {
                            pacman->setPower(FREE_TIME_PACMAN);

                            setGhostBehavior(blinky, deadly, BEHAVIOR_FREEZING);
                            setGhostBehavior(pinky, speedy, BEHAVIOR_FREEZING);
                            setGhostBehavior(inky, invisy, BEHAVIOR_FREEZING);
                            setGhostBehavior(clyde, freezy, BEHAVIOR_FREEZING);

                            system->audio->play(EFFECT_TYPE::FREEZE, false, -1);
                            break;
                        }
                    }
                }
                pacman->eatDot();
                labyrinth->removeDot(pacman->getTile());
                //labyrinth->removeDot(pacman->getScreen(), pacman->getCurDirection());
            }

            if (labyrinth->isIntersection(pacman->getTile()))
                pacman->stop(labyrinth->pacmanCanMove(pacman->getTile(), pacman->getLastDirection()));

            handleGhostLoop(blinky, deadly, blinky, deadly);
            handleGhostLoop(pinky, speedy, blinky, deadly);
            handleGhostLoop(inky, invisy, blinky, deadly);
            handleGhostLoop(clyde, freezy, blinky, deadly);

            ///handle Boss here
            if (golden->isShowedUp())
            {
                handleGoldenMode();
                handleGoldenGenerate();
                handleGoldenTarget(golden, pacman, labyrinth);
                handleGoldenMove(golden, labyrinth);
                handleGoldenHit();

                if (golden->getHP() <= 0)
                {
                    system->audio->play(EFFECT_TYPE::BOSS_DEATH, false, 1);
                    golden->setState(GOLDEN_DEATH_STATE);
                    break;
                }
            }

            if (labyrinth->isDotOver() || ((cur_dot_count == 151) && gameStatus->getLevel() != 7))
            {
                setState(WIN_GAME);
                break;
            }

            ///handle ghost hit
            bool isEndGame = false;

            if (!blinky->isUpgraded())
            {
                switch (handleGhostHit(blinky, pacman))
                {
                    case PACMAN_HIT_GHOST:
                        setState(END_GAME);
                        isEndGame = true;
                        break;
                    case GHOST_HIT_PACMAN:
                        system->audio->play(EFFECT_TYPE::EAT_GHOST, false, -1);
                        gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, blinky->getScreen());
                        break;
                    default:
                        break;
                }
            }
            else
            {
                switch (handleGhostHit(deadly, pacman))
                {
                    case PACMAN_HIT_GHOST:
                        setState(END_GAME);
                        isEndGame = true;
                        break;
                    case GHOST_HIT_PACMAN:
                        system->audio->play(EFFECT_TYPE::EAT_GHOST, false, -1);
                        gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, deadly->getScreen());
                        break;
                    default:
                        break;
                }
            }

            if (!pinky->isUpgraded())
            {
                switch (handleGhostHit(pinky, pacman))
                {
                    case PACMAN_HIT_GHOST:
                        setState(END_GAME);
                        isEndGame = true;
                        break;
                    case GHOST_HIT_PACMAN:
                        system->audio->play(EFFECT_TYPE::EAT_GHOST, false, -1);
                        gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, pinky->getScreen());
                        break;
                    default:
                        break;
                }
            }
            else
            {
                switch (handleGhostHit(speedy, pacman))
                {
                    case PACMAN_HIT_GHOST:
                        if (!pacman->isPacmanPower(SLOW_DOWN_PACMAN))
                        {
                            pacman->setPower(SLOW_DOWN_PACMAN);
                            speedy->setBehavior(UNIQUE_GHOST_SCATTER);
                            speedy->setMode(UNIQUE_GHOST_SPEED_UP_MODE);
                            system->audio->play(EFFECT_TYPE::CONFUSED, false, -1);
                        }
                        break;
                    case GHOST_HIT_PACMAN:
                        system->audio->play(EFFECT_TYPE::EAT_GHOST, false, -1);
                        gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, speedy->getScreen());
                        break;
                    default:
                        break;
                }
            }

            if (!inky->isUpgraded())
            {
                switch (handleGhostHit(inky, pacman))
                {
                    case PACMAN_HIT_GHOST:
                        setState(END_GAME);
                        isEndGame = true;
                        break;
                    case GHOST_HIT_PACMAN:
                        system->audio->play(EFFECT_TYPE::EAT_GHOST, false, -1);
                        gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, inky->getScreen());
                        break;
                    default:
                        break;
                }
            }
            else
            {
                switch (handleGhostHit(invisy, pacman))
                {
                    case PACMAN_HIT_GHOST:
                        if (!pacman->isPacmanPower(BLIND_PACMAN))
                        {
                            pacman->setPower(BLIND_PACMAN);
                            deadly->setMode(UNIQUE_GHOST_INVISIBLE_MODE);
                            speedy->setMode(UNIQUE_GHOST_INVISIBLE_MODE);
                            if (clyde->isUpgraded())
                                freezy->setMode(UNIQUE_GHOST_INVISIBLE_MODE);
                            invisy->setBehavior(UNIQUE_GHOST_SCATTER);
                            invisy->setMode(UNIQUE_GHOST_SPEED_UP_MODE);
                            system->audio->play(EFFECT_TYPE::CONFUSED, false, -1);
                        }
                        break;
                    case GHOST_HIT_PACMAN:
                        system->audio->play(EFFECT_TYPE::EAT_GHOST, false, -1);
                        gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, invisy->getScreen());
                        break;
                    default:
                        break;
                }
            }

            if (!clyde->isUpgraded())
            {
                switch (handleGhostHit(clyde, pacman))
                {
                    case PACMAN_HIT_GHOST:
                        setState(END_GAME);
                        isEndGame = true;
                        break;
                    case GHOST_HIT_PACMAN:
                        system->audio->play(EFFECT_TYPE::EAT_GHOST, false, -1);
                        gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, clyde->getScreen());
                        break;
                    default:
                        break;
                }
            }
            else
            {
                switch (handleGhostHit(freezy, pacman))
                {
                    case PACMAN_HIT_GHOST:
                        if (!pacman->isPacmanPower(FREEZE_PACMAN))
                        {
                            pacman->setPower(FREEZE_PACMAN);
                            freezy->setMode(UNIQUE_GHOST_SPEED_UP_MODE);
                            system->audio->play(EFFECT_TYPE::FREEZE, false, -1);
                        }
                        break;
                    case GHOST_HIT_PACMAN:
                        system->audio->play(EFFECT_TYPE::EAT_GHOST, false, -1);
                        gameStatus->pushScore(UPDATE_SCORE_EAT_GHOST, freezy->getScreen());
                        break;
                    default:
                        break;
                }
            }

            if (isEndGame)
                break;

            handleFruitMove(fruit, labyrinth);

            if (handleFruitHit(fruit, pacman))
            {
                system->audio->play(EFFECT_TYPE::EAT_FRUIT, false, -1);
                gameStatus->pushScore(UPDATE_SCORE_EAT_FRUIT, fruit->getScreen());
                fruit->setState(FRUIT_STAND);
            }

            if (pacman->getFruitEaten() == 4)
            {
                pacman->gainLife();
                system->audio->play(EFFECT_TYPE::EXTEND, false, -1);
            }

            if (!system->audio->isPlayingChannel(1))
                if (!system->audio->isPlayingChannel(0))
                    system->audio->play(EFFECT_TYPE::SIREN, true, 0);

            handleGhostOut(50, pinky, speedy);
            handleGhostOut(100, inky, invisy);
            handleGhostOut(150, clyde, freezy);

            if (cur_dot_count >= 200 && !fruit->isOutOfStandPosition())
                fruit->setState(FRUIT_MOVING);

            break;
        }
        case NEXT_LEVEL_GAME:
        {
            if (!system->audio->isPlaying())
            {
                if (!blinky->isUpgraded())
                    blinky->setBehavior(GHOST_SCATTER);
                else
                    deadly->setBehavior(UNIQUE_GHOST_SCATTER);

                if (golden->isShowedUp())
                    golden->setState(GOLDEN_RUNNING_STATE);

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
                if (gameStatus->getLevel() == 8)
                {
                    system->saveHighscore(gameStatus->getScore(), gameStatus->getLevel());
                    pull(WIN_GAME_STATE);
                }
                else
                {
                    if (gameStatus->getLevel() > 5 && gameStatus->getLevel() != 7)
                        setState(NEXT_LEVEL_GAME);
                    else
                        setState(UPGRADE_GHOST_GAME);

                }
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

//handle ghost with unique ghost
void PlayingState::renderGhost(Ghost* ghost, UniqueGhost* unique_ghost)
{
    if (!ghost->isUpgraded())
        ghost->render();
    if (unique_ghost->isShowedUp() || unique_ghost->getBehavior() == UNIQUE_GHOST_SHOW_UP)
        unique_ghost->render();
    return;
}

void PlayingState::initGhostInit(Ghost* ghost, UniqueGhost* unique_ghost)
{
    if (!ghost->isUpgraded())
        ghost->setBehavior(GHOST_INIT);
    else
        unique_ghost->setBehavior(UNIQUE_GHOST_INIT);
    return;
}

void PlayingState::handleGhostLoop(Ghost* ghost, UniqueGhost* unique_ghost, Blinky* blinky, Deadly* deadly)
{
    if (!ghost->isUpgraded())
    {
        handleGhostTarget(ghost, pacman, blinky);
        handleGhostMove(ghost, labyrinth);
    }
    else
    {
        handleGhostTarget(unique_ghost, pacman, deadly);
        handleGhostMove(unique_ghost, labyrinth);
    }
    return;
}

void PlayingState::handleGhostDeadLoop(Ghost* ghost, UniqueGhost* unique_ghost, Blinky* blinky, Deadly* deadly)
{
    if (!ghost->isUpgraded())
    {
        if (ghost->getBehavior() == GHOST_EATEN || ghost->getBehavior() == GHOST_REBORN)
        {
            handleGhostTarget(ghost, pacman, blinky);
            handleGhostMove(ghost, labyrinth);
        }
    }
    else
    {
        if (unique_ghost->getBehavior() == UNIQUE_GHOST_EATEN || unique_ghost->getBehavior() == UNIQUE_GHOST_REBORN)
        {
            handleGhostTarget(unique_ghost, pacman, deadly);
            handleGhostMove(unique_ghost, labyrinth);
        }
    }
    return;
}

void PlayingState::handleGhostMode(Ghost* ghost, UniqueGhost* unique_ghost)
{
    if (!ghost->isUpgraded())
        ghost->handleMode();
    else
    {
        unique_ghost->handleMode();
        if (unique_ghost->getType() == UNIQUE_GHOST_SPEEDY)
        {
            int distance = DISTANCE::Euclidean(unique_ghost->getTile(), pacman->getTile());
            if (distance <= 2*OBJECT_PIXEL)
            {
                if (!pacman->isPacmanPower(SLOW_DOWN_PACMAN))
                    if (!unique_ghost->isGhostMode(UNIQUE_GHOST_SLOW_DOWN_MODE))
                        unique_ghost->setMode(UNIQUE_GHOST_SLOW_DOWN_MODE);
            }
            else
            {
                if (distance <= 12*OBJECT_PIXEL)
                {
                    if (!unique_ghost->isGhostMode(UNIQUE_GHOST_SPEED_UP_MODE))
                        unique_ghost->setMode(UNIQUE_GHOST_SPEED_UP_MODE);
                }
            }
        }
        if (unique_ghost->getType() == UNIQUE_GHOST_INVISY)
        {
            if (!unique_ghost->isGhostMode(UNIQUE_GHOST_INVISIBLE_MODE))
                unique_ghost->setMode(UNIQUE_GHOST_INVISIBLE_MODE);
        }
    }
    return;
}

void PlayingState::handleGhostOut(const int dot_require, Ghost* ghost, UniqueGhost* unique_ghost)
{
    if (!ghost->isUpgraded())
    {
        if (cur_dot_count >= dot_require && !ghost->isOutGhostHouse())
            ghost->setBehavior(GHOST_SCATTER);
    }
    else
    {
        if (cur_dot_count >= dot_require && !unique_ghost->isOutGhostHouse())
        {
            unique_ghost->setBehavior(UNIQUE_GHOST_SCATTER);
        }
    }
    return;
}

void PlayingState::setGhostBehavior(Ghost* ghost, UniqueGhost* unique_ghost, GHOST_BEHAVIOR_TYPE type)
{
    switch (type)
    {
        case BEHAVIOR_BLIND:
        {
            if (!ghost->isUpgraded())
                ghost->setBehavior(GHOST_BLIND);
            else
                unique_ghost->setBehavior(UNIQUE_GHOST_BLIND);
            break;
        }
        case BEHAVIOR_FREEZING:
        {
            if (!ghost->isUpgraded())
                ghost->setBehavior(GHOST_FREEZING);
            else
                unique_ghost->setBehavior(UNIQUE_GHOST_FREEZING);
            break;
        }
        case BEHAVIOR_FRIGHTENED:
        {
            if (!ghost->isUpgraded())
                ghost->setBehavior(GHOST_FRIGHTENED);
            else
                unique_ghost->setBehavior(UNIQUE_GHOST_FRIGHTENED);
            break;
        }
        default:
            break;
    }
    return;
}

void PlayingState::initUpgrade(Ghost* ghost, UniqueGhost* unique_ghost)
{
    mystery->setState(MYSTERY_MOVING_TO_SPEECH);
    ghost->setTarget(ghost->getUpgrade());
    system->audio->play(EFFECT_TYPE::SIREN, true, 0);
    return;
}

void PlayingState::handleUpgrade(Ghost* ghost, UniqueGhost* unique_ghost)
{
    handleMysteryMove(mystery, labyrinth);
    mystery->handleState();

    handleGhostMove(ghost, labyrinth);
    unique_ghost->handleBehavior();

    if (ghost->getBehavior() != GHOST_UPGRADE_UNIQUE && ghost->getTile() == ghost->getTarget())
    {
        mystery->setState(MYSTERY_SPEECH_UPGRADE);
        system->audio->pauseChannel(0);
        system->audio->play(EFFECT_TYPE::UPGRADE, false, -1);
        ghost->setBehavior(GHOST_UPGRADE_UNIQUE);
    }
    if (ghost->isUpgraded() && unique_ghost->getBehavior() != UNIQUE_GHOST_SHOW_UP)
    {
        unique_ghost->setBehavior(UNIQUE_GHOST_SHOW_UP);
    }
    if (unique_ghost->isShowedUp())
    {
        system->audio->stopChannel(-1);
        system->audio->unpauseChannel(0);
        setState(NEXT_LEVEL_GAME);
    }
    return;
}

void PlayingState::handleGoldenMode()
{
    int distance = DISTANCE::Euclidean(golden->getTile(), pacman->getTile());
    if (distance <= 1*OBJECT_PIXEL)
    {
        if (!golden->isGoldenMode(GOLDEN_SPEED_UP_MODE) && !golden->isGoldenMode(GOLDEN_EXHAUSTED_MODE))
            golden->setMode(GOLDEN_SPEED_UP_MODE);
    }

    ///speed up the unique ghost
    if (golden->getTile() == deadly->getTile())
    {
        if (!deadly->isGhostMode(UNIQUE_GHOST_SPEED_UP_MODE))
            deadly->setMode(UNIQUE_GHOST_SPEED_UP_MODE);
    }

    if (golden->getTile() == speedy->getTile())
    {
        if (!speedy->isGhostMode(UNIQUE_GHOST_SPEED_UP_MODE))
            speedy->setMode(UNIQUE_GHOST_SPEED_UP_MODE);
    }

    if (golden->getTile() == invisy->getTile())
    {
        if (!invisy->isGhostMode(UNIQUE_GHOST_SPEED_UP_MODE))
            invisy->setMode(UNIQUE_GHOST_SPEED_UP_MODE);
    }

    if (golden->getTile() == freezy->getTile())
    {
        if (!freezy->isGhostMode(UNIQUE_GHOST_SPEED_UP_MODE))
            freezy->setMode(UNIQUE_GHOST_SPEED_UP_MODE);
    }

    return;
}

void PlayingState::handleGoldenGenerate()
{
    if (golden->checkScreen())
        labyrinth->generateDot(golden->getTile(), golden->dotGenerate());
    return;
}

void PlayingState::handleGoldenHit()
{
    if (golden->checkCollision(pacman))
    {
        if (golden->isGoldenMode(GOLDEN_EXHAUSTED_MODE))
        {
            pacman->setState(PACMAN_EATING_STATE);
            system->audio->play(EFFECT_TYPE::EAT_GHOST, false ,-1);
            golden->takeDamage(GOLDEN_DAMAGE_HIT);
            gameStatus->pushDamage(GOLDEN_DAMAGE_HIT);
            golden->setMode(GOLDEN_NORMAL_MODE);
        }
        else
        {

        }
    }
    return;
}
