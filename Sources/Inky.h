///Inky [Header]
#ifndef INKY_H_
#define INKY_H_

///Include header
#include "Ghost.h"

///Inky class
class Inky:
    public Ghost
{
    public:
        //Contructor:
        Inky();

        //Destructor:
        ~Inky();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* _timer, Point _start_point = Point(), Point _stand = Point(), Point _scatter = Point());

    private:

};

#endif // INKY_H_

