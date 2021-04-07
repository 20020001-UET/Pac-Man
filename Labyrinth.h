///Labyrinth [Header]
#ifndef LABYRINTH_H_
#define LABYRINTH_H_

#include <SDL.h>
#include "Console.h"
#include "Direction.h"
#include "Point.h"

//Normal 28x31
const int LABYRINTH_W = 28;
const int LABYRINTH_H = 31;

class Labyrinth
{
    public:
        Labyrinth();
        void load(std::string file);
        void render();
        bool canMove(Point point, DIRECTION dir);
        bool intersection(Point point);
        bool isDotHere(Point point);
        bool isPowerUpHere(Point point);
        void removeDot(Point point);

    private:
        int width, height;
        int data[LABYRINTH_H][LABYRINTH_W];
        bool isDot[LABYRINTH_H][LABYRINTH_W];

        SDL_Rect srcRect, destRect;

        Console* console;
};

#endif // LABYRINTH_H_
