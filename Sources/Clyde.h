///Clyde [Header]
#ifndef CLYDE_H_
#define CLYDE_H_

///Include header
#include "Ghost.h"

///Clyde class
class Clyde:
    public Ghost
{
    public:
        //Contructor:
        Clyde();

        //Destructor:
        ~Clyde();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* _timer, Point _start_point = Point(), Point _stand = Point(), Point _scatter = Point(), Point _upgrade = Point());

    private:

};

#endif // CLYDE_H_
