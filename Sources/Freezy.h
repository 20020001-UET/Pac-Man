///Freezy [Header]
#ifndef FREEZY_H_
#define FREEZY_H_

///Include header
#include "UniqueGhost.h"

///Freezy class
class Freezy:
    public UniqueGhost
{
    public:
        //Contructor:
        Freezy();

        //Destructor:
        ~Freezy();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* _timer, Point _show_up, Point _start_point = Point(), Point _stand = Point(), Point _scatter = Point());

    private:

};

#endif // FREEZY_H_
