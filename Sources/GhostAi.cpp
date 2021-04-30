///Ghost Ai [Source]
#include "GhostAi.h"

///Include header
#include "Distance.h"

void handleGhostTarget(Ghost* ghost, Pacman* pacman, Blinky* blinky)
{
    if (ghost->getBehavior() == GHOST_STAND)
        return;

    switch (ghost->getBehavior())
    {
        case GHOST_CHASE:
        case GHOST_FREEZING:
        {
            handleChaseTarget(ghost, pacman, blinky);
            break;
        }
        case GHOST_SCATTER:
        {
            ghost->setTarget(ghost->getScatter());
            break;
        }
        case GHOST_BLIND:
        case GHOST_FRIGHTENED:
        {
            int move_rand = rand() % 4 + 1;
            Point newTarget = Point(ghost->getTile()) + DIRECTION_VALUE[move_rand];
            ghost->setTarget(newTarget);
            break;
        }
        case GHOST_BEING_EATEN:
        case GHOST_EATEN:
        case GHOST_UNSET:
        {
            ghost->setTarget(ghost->getStartPoint());
            break;
        }
        default:
            break;
    }
    return;
}

void handleChaseTarget(Ghost* ghost, Pacman* pacman, Blinky* blinky)
{
    switch (ghost->getType())
    {
        case GHOST_BLINKY:
        {
            ghost->setTarget(pacman->getTile());
            break;
        }

        case GHOST_PINKY:
        {
            Point newTarget = pacman->getTile();
            newTarget = newTarget + DIRECTION_VALUE[pacman->getCurDirection()] * 4;
            ghost->setTarget(newTarget);
            break;
        }

        case GHOST_INKY:
        {
            Point newTarget = pacman->getTile();
            newTarget = newTarget + DIRECTION_VALUE[pacman->getCurDirection()] * 2;
            newTarget = newTarget * 2 - blinky->getTile();
            ghost->setTarget(newTarget);
            break;
        }

        case GHOST_CLYDE:
        {
            Point newTarget = pacman->getTile();
            if (DISTANCE::Euclidean(ghost->getTile(), newTarget) <= 8*RESOURCES_PIXEL)
                newTarget = ghost->getScatter();
            ghost->setTarget(newTarget);
            break;
        }

        default:
            break;
    }

    return;
}

///Calculate new Direction
DIRECTION calcDirection(Ghost* ghost, Labyrinth* labyrinth)
{
    Point newTile;
    int dis, minDis;
    minDis = (int)1e9;
    int newDirection = 0;

    for (int i = UP; i <= LEFT; i++)
    {
        if (checkOpposite(ghost->getCurDirection(), DIRECTION_AT[i]))
        {
            continue;
        }

        dis = (int)1e9;

        if (labyrinth->ghostCanMove(ghost->getTile(), DIRECTION_AT[i]))
        {
            newTile = ghost->getTile() + DIRECTION_VALUE[i];

            ///Euclidean distance
            dis = DISTANCE::Euclidean(newTile, ghost->getTarget());

            ///Manhattan distance
            //dis = DISTANCE::Manhattan(newTile, ghost->getTarget());
        }

        if (minDis > dis)
        {
            minDis = dis;
            newDirection = i;
        }
    }

    return DIRECTION_AT[newDirection];
}

void handleGhostMove(Ghost* ghost, Labyrinth* labyrinth)
{
    if (ghost->getBehavior() == GHOST_STAND)
        return;

    if (labyrinth->isIntersection(ghost->getTile()) || ghost->getCurDirection() == UNSET_DIRECTION)
    {
        if (ghost->isStop())
        {
            ghost->setDirection(calcDirection(ghost, labyrinth));
            ghost->setStop(false);
        }
    }
    else
        ghost->setStop(true);

    if (labyrinth->ghostCanMove(ghost->getTile(), ghost->getCurDirection()))
        ghost->loop();
    else
        ghost->setStop(true);
    return;
}

HIT_VALUE handleGhostHit(Ghost* ghost, Pacman* pacman)
{
    if (ghost->getBehavior() == GHOST_STAND)
        return UNHIT;

    if (ghost->checkCollision(pacman))
    {
        if (ghost->getBehavior() == GHOST_FRIGHTENED)
        {
        //if (ghost->getTile() == pacman->getTile())

            pacman->setState(PACMAN_EATING_STATE);
            ghost->setBehavior(GHOST_BEING_EATEN);
            return GHOST_HIT_PACMAN;

        //return UNHIT;
        }

        if (!pacman->isPacmanPower(INVISIBLE_PACMAN) && ghost->getBehavior() != GHOST_EATEN && ghost->getBehavior() != GHOST_BEING_EATEN && ghost->getBehavior() != GHOST_UNSET)
        {
            return PACMAN_HIT_GHOST;
        }
    }

    return UNHIT;
}
