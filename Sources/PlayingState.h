///PlayingState [Header]
#ifndef PLAYING_STATE_H_
#define PLAYING_STATE_H_

///Include header
#include <SDL.h>
#include "State.h"
#include "Console.h"
#include "Background.h"
#include "Labyrinth.h"
#include "Pacman.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "GameStatus.h"
#include "Fruit.h"

///States of playing
enum STATE_OF_PLAYING
{
    NEW_GAME = 0,
    NEW_LIFE_GAME,
    PLAYING_GAME,
    //PAUSED_GAME,
    NEXT_LEVEL_GAME,
    END_GAME,
    WIN_GAME,
    STATE_OF_PLAYING_TOTAL
};

///Game control
enum PLAYING_CONTROL
{
    UP_KEY = 0,
    RIGHT_KEY,
    DOWN_KEY,
    LEFT_KEY,
    PLAYING_CONTROL_TOTAL
};

///Game Status Point
const Point SCORE_POINT = Point(160*3, 12*3);
const Point HIGHSCORE_POINT = Point(80*3, 12*3);
const Point LIFE_POINT = Point(0*3, 276*3);
const Point LEVEL_POINT = Point(128*3, 276*3);

///Pacman type
const PACMAN_TYPE PACMAN_TYPE_AT[PACMAN_TYPE_TOTAL] = {PACMAN_DEFAULT, PACMAN_MS, PACMAN_ANDROID};

///PlayingState
class PlayingState:
    public State
{
    public:
        //Constructor:
        PlayingState();

        //Destructor:
        ~PlayingState();

        ///function:
        //init:
        void init(System* _system);

        //loop:
        void loop();

        //render:
        void render();

        //handle key event:
        void keyPressed(const int key_code);
        void keyReleased(const int key_code);

        //close:
        void close();

        ///playing state
        //set state:
        void setState(STATE_OF_PLAYING newState);

        //init state:
        void initState();

        //handle state:
        void handleState();

        ///playing control
        //get control
        void getControl();

    private:
        ///Console
        Console* console;

        ///Background
        Background* background;

        ///State
        STATE_OF_PLAYING curState;

        ///Control value
        int controlKey[PLAYING_CONTROL_TOTAL];

        ///Labyrinth
        Labyrinth* labyrinth;

        ///Object
        Pacman* pacman;
        Blinky* blinky;
        Pinky* pinky;
        Inky* inky;
        Clyde* clyde;
        Fruit* fruit;

        //Dot count
        int cur_dot_count;

        ///GameStatus
        GameStatus* gameStatus;
};

#endif // PLAYING_STATE_H_
