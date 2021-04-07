///Playing [Source]
#include "Playing.h"

#include "Engine.h"
#include <random>
#include <ctime>
#include <iostream>

///Playing class
void Playing::init()
{
    console = new Console("Playing");

    pacman = new Pacman(14, 22,
                        Engine::getPixel()*2, Engine::getPixel()*2);

    blinky = new Ghost(14, 10,
                       Engine::getPixel()*2, Engine::getPixel()*2, BLINKY);

    labyrinth = new Labyrinth();
    labyrinth->load("labyrinth.dat");

    Logic::init(pacman, blinky, labyrinth);

    srand(time(NULL));

    console->writeLine("Initialized state.");
}

void Playing::loop()
{
    if (Logic::PacmanCanMove() && pacman->isAlive())
        pacman->loop();
    else
        pacman->stop();

    if (Logic::DotHere())
    {
        pacman->eatDot();
        labyrinth->removeDot(pacman->getTile());
        if (labyrinth->isPowerUpHere(pacman->getTile()))
        {
            blinky->setBehavior(FRIGHTENED);
        }
    }

    if (Logic::IntersectionHere())
        pacman->stop();

    if (pacman->getDir() != DEFAULT)
    {
        if (blinky->getBehavior() == CHASE)
        blinky->setTarget(pacman->getTile());
        else
            if (blinky->getBehavior() == SCATTER)
                blinky->setTarget(Point(28, -3));
            else
                if (blinky->getBehavior() == FRIGHTENED)
                {
                    int move_rand = rand() % 4;
                    Point newTarget = Point(blinky->getTile());
                    newTarget.x += vel_x[move_rand];
                    newTarget.y += vel_y[move_rand];
                    blinky->setTarget(newTarget);
                }

        Logic::handleGhostMove(blinky);

        Logic::handleGhostHit(blinky);
    }

    if (!pacman->isAlive())
    {
        pacman->keepAlive();
        blinky->teleport(14, 10);
    }

    if (pacman->isDead())
        Engine::stateClose();
}

void Playing::render()
{
    labyrinth->render();
    blinky->render();
    pacman->render();
}

void Playing::keyPressed(int key_sym)
{
    console->writeLine("Key pressed.");

    switch (key_sym)
    {
        case SDLK_UP:
            pacman->setDir(UP);
            break;

        case SDLK_DOWN:
            pacman->setDir(DOWN);
            break;

        case SDLK_LEFT:
            pacman->setDir(LEFT);
            break;

        case SDLK_RIGHT:
            pacman->setDir(RIGHT);
            break;

        case SDLK_ESCAPE:
            Engine::stateClose();
            break;

        default:
            break;
    }
}

void Playing::keyReleased(int key_sym)
{
    console->writeLine("Key released.");
}

void Playing::close()
{
    console->writeLine("Closing state. . .");

    Logic::free();

    delete console;
    console = NULL;

    delete pacman;
    pacman = NULL;

    delete blinky;
    blinky = NULL;

    delete pinky;
    pinky = NULL;

    delete labyrinth;
    labyrinth = NULL;
}


