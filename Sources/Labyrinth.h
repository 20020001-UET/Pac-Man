///Labyrinth [Header]
#ifndef LABYRINTH_H_
#define LABYRINTH_H_

///Include header
#include "Graphic.h"
#include "Console.h"
#include "Point.h"
#include "Direction.h"
#include <string>

///Labyrinth type
const LABYRINTH_TYPE LABYRINTH_TYPE_AT[LABYRINTH_TYPE_TOTAL] = { LABYRINTH_DEFAULT, LABYRINTH_WHITE };

///Labyrinth constan value
const std::string LABYRINTH_PATH = "labyrinth.dat";
const int LABYRINTH_FRAME_VALUE = 5;
const int LABYRINTH_DATA_WIDTH = 28;
const int LABYRINTH_DATA_HEIGHT = 31;
enum LABYRINTH_DATA_TYPE
{
    WALL_DATA = 0,
    PATH_DATA,
    DOT_DATA,
    POWER_DOT_DATA,
    GHOST_HOUSE_DATA,
    PACMAN_STAND_DATA,
    GHOST_START_DATA,
    PINKY_STAND_DATA,
    INKY_STAND_DATA,
    CLYDE_STAND_DATA,
    LABYRINTH_DATA_TOTAL
};

///Labyrinth class
class Labyrinth
{
    public:
        //Constructor:
        Labyrinth();

        //Destructor:
        ~Labyrinth();

        ///function:
        //init:
        void init(Graphic* _graphic);

        //load:
        void renew();
        void load(const std::string path = LABYRINTH_PATH);

        //set animation:
        void setAnimated(const bool _animated);

        //render:
        void render();
        void dot_render();

        ///Check function
        bool isIntersection(Point tile) const;
        bool isDotOver() const;

        ///Pacman function
        Point getPacmanStand() const;
        bool pacmanCanMove(Point tile, DIRECTION dir) const;
        bool isDotHere(Point tile) const;
        int isPowerDotHere(Point tile) const;
        void removeDot(Point tile);

        ///Ghost function:
        Point getGhostStart() const;
        Point getBlinkyStand() const;
        Point getPinkyStand() const;
        Point getInkyStand() const;
        Point getClydeStand() const;
        bool ghostCanMove(Point tile, DIRECTION dir) const;

        ///Fruit function:
        bool fruitCanMove(Point tile, DIRECTION dir) const;

    private:
        ///Console
        Console* console;

        ///Graphic
        Graphic* graphic;

        ///Labyrinth type
        LABYRINTH_TYPE type;

        ///Labyrinth data
        Point pacman_stand;
        Point ghost_start;
        Point blinky_stand, pinky_stand, inky_stand, clyde_stand;
        int data[LABYRINTH_DATA_WIDTH][LABYRINTH_DATA_HEIGHT], powerDot[LABYRINTH_DATA_WIDTH][LABYRINTH_DATA_HEIGHT];
        bool isDot[LABYRINTH_DATA_WIDTH][LABYRINTH_DATA_HEIGHT];
        int dotRemain;

        //destination:
        SDL_Rect dest, dot_dest;

        ///Animation value
        bool animated;
        int frame, frame_value;

        ///Check point
        bool checkIn(Point tile) const;
        int getData(Point tile) const;
};

#endif // LABYRINTH_H_
