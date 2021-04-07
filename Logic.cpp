///Logic [Source]
#include "Logic.h"
#include "Direction.h"
#include <iostream>

///Logic class
Pacman* Logic::pacman;
Ghost* Logic::blinky;
Labyrinth* Logic::labyrinth;

void Logic::init(Pacman* _pacman, Ghost* _blinky, Labyrinth* _labyrinth)
{
    pacman = _pacman;
    blinky = _blinky;
    labyrinth = _labyrinth;
}

bool Logic::PacmanCanMove()
{
    return labyrinth->canMove(pacman->getTile(), pacman->getDir());
}

bool Logic::DotHere()
{
    return labyrinth->isDotHere(pacman->getTile());
}

bool Logic::IntersectionHere()
{
    return labyrinth->intersection(pacman->getTile());
}

void Logic::handleGhostMove(Ghost* ghost)
{
    if (labyrinth->intersection(ghost->getTile()))
    {
        if (ghost->isStop())
        {
            Point tmp;
            int dis, minDis;
            minDis = (int)1e9;
            int pos = 4;
            for (int i = 0; i < 4; i++)
            {
                if (checkOppositeDir(ghost->getDir(), dirAt[i]))
                    continue;

                dis = (int)1e9;

                if (labyrinth->canMove(ghost->getTile(), dirAt[i]))
                {
                    tmp = Point(ghost->getTile());
                    tmp.x += vel_x[i];
                    tmp.y += vel_y[i];
                    dis = Point::distance(tmp, ghost->getTarget());
                }

                if (minDis > dis)
                {
                    pos = i;
                    minDis = dis;
                }
            }

            ghost->setMoving(dirAt[pos]);
            ghost->setStop(false);
        }
    }
    else
        ghost->setStop(true);

    if (labyrinth->canMove(ghost->getTile(), ghost->getDir()))
        ghost->loop();
    else
        ghost->setStop(true);

    return;
}


void Logic::handleGhostHit(Ghost* ghost)
{
    if (Point::checkEqual(pacman->getTile(), ghost->getTile()))
    {
        if (ghost->getBehavior() == FRIGHTENED)
        {
            ghost->setBehavior(EATEN);
        }
        else
            if (ghost->getBehavior() != EATEN)
            {
                pacman->dead();
            }
    }
}

void Logic::free()
{
    pacman = NULL;
    blinky = NULL;
    labyrinth = NULL;
}
