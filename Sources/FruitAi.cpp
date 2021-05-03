///Fruit Ai [Source]
#include "FruitAi.h"

///Include header
#include "Distance.h"

///Calculate new Direction
DIRECTION calcDirection(Fruit* fruit, Labyrinth* labyrinth)
{
    Point newTile;
    int dis, minDis;
    minDis = (int)1e9;
    int newDirection = 0;

    for (int i = UP; i <= LEFT; i++)
    {
        if (checkOpposite(fruit->getCurDirection(), DIRECTION_AT[i]))
        {
            continue;
        }

        dis = (int)1e9;

        if (labyrinth->ghostCanMove(fruit->getTile(), DIRECTION_AT[i]))
        {
            newTile = fruit->getTile() + DIRECTION_VALUE[i];

            ///Manhattan distance
            dis = DISTANCE::Manhattan(newTile, fruit->getTarget());
        }

        if (minDis > dis)
        {
            minDis = dis;
            newDirection = i;
        }
    }

    return DIRECTION_AT[newDirection];
}

void handleFruitMove(Fruit* fruit, Labyrinth* labyrinth)
{
    if (fruit->getState() == FRUIT_STAND)
        return;

    if (labyrinth->isIntersection(fruit->getTile()) || fruit->getCurDirection() == UNSET_DIRECTION)
    {
        if (fruit->isStop())
        {
            fruit->setDirection(calcDirection(fruit, labyrinth));
            fruit->setStop(false);
        }
    }
    else
        fruit->setStop(true);

    if (labyrinth->fruitCanMove(fruit->getTile(), fruit->getCurDirection()))
        fruit->loop();
    else
        fruit->setStop(true);
    return;
}

bool handleFruitHit(Fruit* fruit, Pacman* pacman)
{
    if (fruit->getState() == FRUIT_STAND)
        return false;

    if (fruit->checkCollision(pacman))
    {
        pacman->eatFruit();
        pacman->setState(PACMAN_EATING_STATE);
        return true;
    }

    return false;
}
