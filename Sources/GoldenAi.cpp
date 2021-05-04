///Golden Ai [Source]
#include "GoldenAi.h"

///Include header
#include "Distance.h"

void handleGoldenTarget(Golden* golden, Pacman* pacman, Labyrinth* labyrinth)
{
    Point root(14, 14);
    Point newTarget = root*2 - pacman->getTile();
    golden->setTarget(newTarget);

    int distance = DISTANCE::Euclidean(golden->getTile(), pacman->getTile());
    if (distance <= 1*OBJECT_PIXEL)
    {
        int new_distance = DISTANCE::Euclidean(golden->getTile() + DIRECTION_VALUE[golden->getCurDirection()], pacman->getTile() + DIRECTION_VALUE[pacman->getCurDirection()]);

        if (new_distance < distance)
            golden->setDanger(true);
        else
            golden->setDanger(false);

        if (golden->isDanger())
        {
            if (labyrinth->ghostCanMove(golden->getTile(), opposite(golden->getCurDirection())))
            {
                golden->setDirection(opposite(golden->getCurDirection()));
                golden->setDanger(false);
            }
        }
    }
    else
    {
        golden->setDanger(true);
    }

    return;
}

///Calculate new Direction
DIRECTION calcDirection(Golden* golden, Labyrinth* labyrinth)
{
    Point newTile;
    int dis, minDis;
    minDis = (int)1e9;
    int newDirection = 0;

    for (int i = UP; i <= LEFT; i++)
    {
        if (checkOpposite(golden->getCurDirection(), DIRECTION_AT[i]))
        {
            continue;
        }

        dis = (int)1e9;

        if (labyrinth->ghostCanMove(golden->getTile(), DIRECTION_AT[i]))
        {
            newTile = golden->getTile() + DIRECTION_VALUE[i];

            ///Manhattan distance
            dis = DISTANCE::Manhattan(newTile, golden->getTarget());
        }

        if (minDis > dis)
        {
            minDis = dis;
            newDirection = i;
        }
    }

    return DIRECTION_AT[newDirection];
}

void handleGoldenMove(Golden* golden, Labyrinth* labyrinth)
{
    if (golden->getState() == GOLDEN_SHOW_UP_STATE)
        return;

    if (labyrinth->isIntersection(golden->getTile()) || golden->getCurDirection() == UNSET_DIRECTION)
    {
        if (golden->isStop())
        {
            golden->setDirection(calcDirection(golden, labyrinth));
            golden->setStop(false);
        }
    }
    else
        golden->setStop(true);

    if (labyrinth->ghostCanMove(golden->getTile(), golden->getCurDirection()))
        golden->loop();
    else
        golden->setStop(true);
    return;
}
