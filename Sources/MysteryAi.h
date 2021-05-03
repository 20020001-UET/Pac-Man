///Mystery Ai [Header]
#ifndef MYSTERY_AI_H_
#define MYSTERY_AI_H_

///Include header
#include "Mystery.h"
#include "Labyrinth.h"

///Calculate new Direction
DIRECTION calcDirection(Mystery* mystery, Labyrinth* labyrinth);

void handleMysteryMove(Mystery* mystery, Labyrinth* labyrinth);

#endif // MYSTERY_AI_H_
