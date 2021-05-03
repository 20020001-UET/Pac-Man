///Ghost Ai [Header]
#ifndef GHOST_AI_H_
#define GHOST_AI_H_

///Include header
#include "Ghost.h"
#include "UniqueGhost.h"
#include "Blinky.h"
#include "Deadly.h"
#include "Labyrinth.h"
#include "Pacman.h"

enum HIT_VALUE
{
    UNHIT,
    PACMAN_HIT_GHOST,
    GHOST_HIT_PACMAN,
    HIT_VALUE_TOTAL
};

///Ghost
void handleGhostTarget(Ghost* ghost, Pacman* pacman, Blinky* blinky);
void handleChaseTarget(Ghost* ghost, Pacman* pacman, Blinky* blinky);

///Calculate new Direction
DIRECTION calcDirection(Ghost* ghost, Labyrinth* labyrinth);

void handleGhostMove(Ghost* ghost, Labyrinth* labyrinth);

HIT_VALUE handleGhostHit(Ghost* ghost, Pacman* pacman);

///Unique Ghost
void handleGhostTarget(UniqueGhost* unique_ghost, Pacman* pacman, Deadly* deadly);
void handleChaseTarget(UniqueGhost* unique_ghost, Pacman* pacman, Deadly* deadly);

///Calculate new Direction
DIRECTION calcDirection(UniqueGhost* unique_ghost, Labyrinth* labyrinth);

void handleGhostMove(UniqueGhost* unique_ghost, Labyrinth* labyrinth);

HIT_VALUE handleGhostHit(UniqueGhost* unique_ghost, Pacman* pacman);

#endif // GHOST_AI_H_
