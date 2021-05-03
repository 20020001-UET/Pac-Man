///Pinky [Header]
#ifndef PINKY_H_
#define PINKY_H_

///Include header
#include "Ghost.h"

///Pinky class
class Pinky:
    public Ghost
{
    public:
        //Contructor:
        Pinky();

        //Destructor:
        ~Pinky();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* _timer, Point _start_point = Point(), Point _stand = Point(), Point _scatter = Point(), Point _upgrade = Point());

    private:

};

#endif // PINKY_H_

