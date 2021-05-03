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
        if (ghost->isGhostMode(GHOST_FRIGHTENED_MODE))
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

///Unique Ghost
void handleGhostTarget(UniqueGhost* unique_ghost, Pacman* pacman, Deadly* deadly)
{
    if (unique_ghost->getBehavior() == UNIQUE_GHOST_STAND)
        return;

    switch (unique_ghost->getBehavior())
    {
        case UNIQUE_GHOST_CHASE:
        case UNIQUE_GHOST_FREEZING:
        {
            handleChaseTarget(unique_ghost, pacman, deadly);
            break;
        }
        case UNIQUE_GHOST_SCATTER:
        {
            unique_ghost->setTarget(unique_ghost->getScatter());
            break;
        }
        case UNIQUE_GHOST_BLIND:
        case UNIQUE_GHOST_FRIGHTENED:
        {
            int move_rand = rand() % 4 + 1;
            Point newTarget = Point(unique_ghost->getTile()) + DIRECTION_VALUE[move_rand];
            unique_ghost->setTarget(newTarget);
            break;
        }
        case UNIQUE_GHOST_BEING_EATEN:
        case UNIQUE_GHOST_EATEN:
        case UNIQUE_GHOST_UNSET:
        {
            unique_ghost->setTarget(unique_ghost->getStartPoint());
            break;
        }
        default:
            break;
    }
    return;
}

void handleChaseTarget(UniqueGhost* unique_ghost, Pacman* pacman, Deadly* deadly)
{
    switch (unique_ghost->getType())
    {
        case UNIQUE_GHOST_DEADLY:
        {
            unique_ghost->setTarget(pacman->getTile());
            break;
        }

        case UNIQUE_GHOST_SPEEDY:
        {
            Point newTarget = pacman->getTile();
            newTarget = newTarget + DIRECTION_VALUE[pacman->getCurDirection()] * 4;
            unique_ghost->setTarget(newTarget);
            break;
        }

        case UNIQUE_GHOST_INVISY:
        {
            Point newTarget = pacman->getTile();
            newTarget = newTarget + DIRECTION_VALUE[pacman->getCurDirection()] * 2;
            newTarget = newTarget * 2 - deadly->getTile();
            unique_ghost->setTarget(newTarget);
            break;
        }

        case UNIQUE_GHOST_FREEZY:
        {
            Point newTarget = pacman->getTile();
            if (DISTANCE::Euclidean(unique_ghost->getTile(), newTarget) <= 8*RESOURCES_PIXEL)
                newTarget = unique_ghost->getScatter();
            unique_ghost->setTarget(newTarget);
            break;
        }

        default:
            break;
    }

    return;
}

///Caculate new Direction
DIRECTION calcDirection(UniqueGhost* unique_ghost, Labyrinth* labyrinth)
{
    Point newTile;
    int dis, minDis;
    minDis = (int)1e9;
    int newDirection = 0;

    for (int i = UP; i <= LEFT; i++)
    {
        if (checkOpposite(unique_ghost->getCurDirection(), DIRECTION_AT[i]))
        {
            continue;
        }

        dis = (int)1e9;

        if (labyrinth->ghostCanMove(unique_ghost->getTile(), DIRECTION_AT[i]))
        {
            newTile = unique_ghost->getTile() + DIRECTION_VALUE[i];

            ///Euclidean distance
            dis = DISTANCE::Euclidean(newTile, unique_ghost->getTarget());

            ///Manhattan distance
            //dis = DISTANCE::Manhattan(newTile, unique_ghost->getTarget());
        }

        if (minDis > dis)
        {
            minDis = dis;
            newDirection = i;
        }
    }

    return DIRECTION_AT[newDirection];
}

void handleGhostMove(UniqueGhost* unique_ghost, Labyrinth* labyrinth)
{
    if (unique_ghost->getBehavior() == UNIQUE_GHOST_STAND)
        return;

    if (labyrinth->isIntersection(unique_ghost->getTile()) || unique_ghost->getCurDirection() == UNSET_DIRECTION)
    {
        if (unique_ghost->isStop())
        {
            unique_ghost->setDirection(calcDirection(unique_ghost, labyrinth));
            unique_ghost->setStop(false);
        }
    }
    else
        unique_ghost->setStop(true);

    if (labyrinth->ghostCanMove(unique_ghost->getTile(), unique_ghost->getCurDirection()))
        unique_ghost->loop();
    else
        unique_ghost->setStop(true);
    return;
}

HIT_VALUE handleGhostHit(UniqueGhost* unique_ghost, Pacman* pacman)
{
    if (unique_ghost->getBehavior() == UNIQUE_GHOST_STAND)
        return UNHIT;

    if (unique_ghost->checkCollision(pacman))
    {
        if (unique_ghost->isGhostMode(UNIQUE_GHOST_FRIGHTENED_MODE))
        {
        //if (unique_ghost->getTile() == pacman->getTile())

            pacman->setState(PACMAN_EATING_STATE);
            unique_ghost->setBehavior(UNIQUE_GHOST_BEING_EATEN);
            return GHOST_HIT_PACMAN;

        //return UNHIT;
        }

        if (!pacman->isPacmanPower(INVISIBLE_PACMAN) && unique_ghost->getBehavior() != UNIQUE_GHOST_EATEN && unique_ghost->getBehavior() != UNIQUE_GHOST_BEING_EATEN && unique_ghost->getBehavior() != UNIQUE_GHOST_UNSET)
        {
            switch (unique_ghost->getType())
            {
                case UNIQUE_GHOST_DEADLY:
                    pacman->dead(); //-1 life
                    break;
                case UNIQUE_GHOST_SPEEDY:
                    break;
                case UNIQUE_GHOST_INVISY:
                    break;
                case UNIQUE_GHOST_FREEZY:
                    break;
                default:
                    break;
            }
            return PACMAN_HIT_GHOST;
        }
    }

    return UNHIT;
}
