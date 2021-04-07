///Logic [Header]
#ifndef LOGIC_H_
#define LOGIC_H_

///Project headers
#include "Pacman.h"
#include "Ghost.h"
#include "Labyrinth.h"

///Logic class
class Logic
{
    public:
        static void init(Pacman* _pacman, Ghost* _blinky, Labyrinth* _labyrinth);
        static bool PacmanCanMove();
        static bool DotHere();
        static bool IntersectionHere();
        static void handleGhostMove(Ghost* ghost);
        static void handleGhostHit(Ghost* ghost);
        static void free();

    private:
        static Pacman* pacman;
        static Ghost* blinky;
        static Labyrinth* labyrinth;

};

#endif // LOGIC_H_
