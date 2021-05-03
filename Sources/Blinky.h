///Blinky [Header]
#ifndef BLINKY_H_
#define BLINKY_H_

///Include header
#include "Ghost.h"

///Blinky class
class Blinky:
    public Ghost
{
    public:
        //Contructor:
        Blinky();

        //Destructor:
        ~Blinky();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* _timer, Point _start_point = Point(), Point _stand = Point(), Point _scatter = Point(), Point _upgrade = Point());

        void leaveGhostHouse();

    private:

};

#endif // BLINKY_H_
