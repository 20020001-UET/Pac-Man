///Deadly [Header]
#ifndef DEADLY_H_
#define DEADLY_H_

///Include header
#include "UniqueGhost.h"

///Deadly class
class Deadly:
    public UniqueGhost
{
    public:
        //Contructor:
        Deadly();

        //Destructor:
        ~Deadly();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* _timer, Point _show_up, Point _start_point = Point(), Point _stand = Point(), Point _scatter = Point());

        void leaveGhostHouse();

    private:

};

#endif // DEADLY_H_
