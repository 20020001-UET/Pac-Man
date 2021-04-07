///Direction [Header]
#ifndef DIRECTION_H_
#define DIRECTION_H_

enum DIRECTION
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    DEFAULT
};

//Direction
const DIRECTION dirAt[5] = {UP, RIGHT, DOWN, LEFT, DEFAULT};
const int vel_x[4] = {0, 1, 0, -1};
const int vel_y[4] = {-1, 0, 1, 0};

//Function
bool checkOppositeDir(DIRECTION first, DIRECTION second);

#endif // DIRECTION_H_
