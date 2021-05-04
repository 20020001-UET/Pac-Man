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
#include "Deadly.h"
#include "Speedy.h"
#include "Invisy.h"
#include "Freezy.h"
#include "Mystery.h"
#include "Golden.h"

///States of playing
enum STATE_OF_PLAYING
{
    NEW_GAME = 0,
    NEW_LIFE_GAME,
    PLAYING_GAME,
    UPGRADE_GHOST_GAME,
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
const Point LEVEL_POINT = Point(112*3, 276*3);
const Point POWER_POINT = Point(0*3, 0*3);

///Mystery Speech Point
const Point MYSTERY_SPEECH_UPGRADE_POINT = Point(90*3, 106*3);
const Point MYSTERY_SPEECH_SHOW_UP_POINT = Point(86*3, 106*3);

///Pacman type
const PACMAN_TYPE PACMAN_TYPE_AT[PACMAN_TYPE_TOTAL] = {PACMAN_DEFAULT, PACMAN_MS, PACMAN_ANDROID};

///Behavior type
enum GHOST_BEHAVIOR_TYPE
{
    BEHAVIOR_FRIGHTENED = 0,
    BEHAVIOR_BLIND,
    BEHAVIOR_FREEZING,
    GHOST_BEHAVIOR_TYPE_TOTAL
};

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

        //handle ghost with unique ghost
        void renderGhost(Ghost* ghost, UniqueGhost* unique_ghost);
        void initGhostInit(Ghost* ghost, UniqueGhost* unique_ghost);
        void handleGhostLoop(Ghost* ghost, UniqueGhost* unique_ghost, Blinky* blinky, Deadly* deadly);
        void handleGhostDeadLoop(Ghost* ghost, UniqueGhost* unique_ghost, Blinky* blinky, Deadly* deadly);
        void handleGhostMode(Ghost* ghost, UniqueGhost* unique_ghost);
        void handleGhostOut(const int dot_require, Ghost* ghost, UniqueGhost* unique_ghost);
        void setGhostBehavior(Ghost* ghost, UniqueGhost* unique_ghost, GHOST_BEHAVIOR_TYPE type);
        void initUpgrade(Ghost* ghost, UniqueGhost* unique_ghost);
        void handleUpgrade(Ghost* ghost, UniqueGhost* unique_ghost);

        void handleGoldenMode();
        void handleGoldenGenerate();
        void handleGoldenHit();

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
        Deadly* deadly;

        Pinky* pinky;
        Speedy* speedy;

        Inky* inky;
        Invisy* invisy;

        Clyde* clyde;
        Freezy* freezy;

        Fruit* fruit;

        Mystery* mystery;

        Golden* golden;

        //Dot count
        int cur_dot_count;

        ///GameStatus
        GameStatus* gameStatus;
};

#endif // PLAYING_STATE_H_
