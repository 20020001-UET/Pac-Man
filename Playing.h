///Playing [Header]
#ifndef PLAYING_H_
#define PLAYING_H_

#include "State.h"

#include "Console.h"
#include "Pacman.h"
#include "Labyrinth.h"
#include "Logic.h"
#include "Ghost.h"

///Playing class
class Playing :
    public State
{
    public:
        void init();
        void loop();
        void render();
        void keyPressed(int key_sym);
        void keyReleased(int key_sym);
        void close();

    private:
        Console* console;

        //Object
        Pacman* pacman;

        Ghost* blinky;
        Ghost* pinky;

        //Labyrinth
        Labyrinth* labyrinth;

};

#endif // PLAYING_H_
