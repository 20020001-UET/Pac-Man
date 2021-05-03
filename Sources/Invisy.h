///Invisy [Header]
#ifndef INVISY_H_
#define INVISY_H_

///Include header
#include "UniqueGhost.h"

///Invisy class
class Invisy:
    public UniqueGhost
{
    public:
        //Contructor:
        Invisy();

        //Destructor:
        ~Invisy();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* _timer, Point _show_up, Point _start_point = Point(), Point _stand = Point(), Point _scatter = Point());

    private:

};

#endif // INVISY_H_
