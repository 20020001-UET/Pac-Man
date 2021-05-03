///Speedy [Header]
#ifndef SPEEDY_H_
#define SPEEDY_H_

///Include header
#include "UniqueGhost.h"

///Speedy class
class Speedy:
    public UniqueGhost
{
    public:
        //Contructor:
        Speedy();

        //Destructor:
        ~Speedy();

        ///function:
        //init:
        void init(Graphic* _graphic, Timer* _timer, Point _show_up, Point _start_point = Point(), Point _stand = Point(), Point _scatter = Point());

    private:

};

#endif // SPEEDY_H_
