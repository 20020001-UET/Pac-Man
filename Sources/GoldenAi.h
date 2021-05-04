///Golden Ai [Header]
#ifndef GOLDEN_AI_H_
#define GOLDEN_AI_H_

///Include header
#include "Golden.h"
#include "Labyrinth.h"
#include "Pacman.h"

void handleGoldenTarget(Golden* golden, Pacman* pacman, Labyrinth* labyrinth);

///Calculate new Direction
DIRECTION calcDirection(Golden* golden, Labyrinth* labyrinth);

void handleGoldenMove(Golden* golden, Labyrinth* labyrinth);

#endif // GOLDEN_AI_H_
