///Fruit Ai [Header]
#ifndef FRUIT_AT_H_
#define FRUIT_AT_H_

///Include header
#include "Fruit.h"
#include "Labyrinth.h"
#include "Pacman.h"

///Calculate new Direction
DIRECTION calcDirection(Fruit* fruit, Labyrinth* labyrinth);

void handleFruitMove(Fruit* fruit, Labyrinth* labyrinth);
bool handleFruitHit(Fruit* fruit, Pacman* pacman);

#endif // FRUIT_AT_H_
