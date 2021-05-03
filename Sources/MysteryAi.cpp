///Mystery Ai [Source]
#include "MysteryAi.h"

///Include header
#include "Distance.h"

///Calculate new Direction
DIRECTION calcDirection(Mystery* mystery, Labyrinth* labyrinth)
{
    Point newTile;
    int dis, minDis;
    minDis = (int)1e9;
    int newDirection = 0;

    for (int i = UP; i <= LEFT; i++)
    {
        if (checkOpposite(mystery->getCurDirection(), DIRECTION_AT[i]))
        {
            continue;
        }

        dis = (int)1e9;

        if (labyrinth->ghostCanMove(mystery->getTile(), DIRECTION_AT[i]))
        {
            newTile = mystery->getTile() + DIRECTION_VALUE[i];

            ///Manhattan distance
            dis = DISTANCE::Manhattan(newTile, mystery->getTarget());
        }

        if (minDis > dis)
        {
            minDis = dis;
            newDirection = i;
        }
    }

    return DIRECTION_AT[newDirection];
}

void handleMysteryMove(Mystery* mystery, Labyrinth* labyrinth)
{
    if (mystery->getState() == MYSTERY_STAND || mystery->getState() == MYSTERY_SPEECH_UPGRADE || mystery->getState() == MYSTERY_WAITING_TO_SPEECH)
        return;

    if (labyrinth->isIntersection(mystery->getTile()) || mystery->getCurDirection() == UNSET_DIRECTION)
    {
        if (mystery->isStop())
        {
            mystery->setDirection(calcDirection(mystery, labyrinth));
            mystery->setStop(false);
        }
    }
    else
        mystery->setStop(true);

    if (labyrinth->fruitCanMove(mystery->getTile(), mystery->getCurDirection()))
        mystery->loop();
    else
        mystery->setStop(true);
    return;
}
