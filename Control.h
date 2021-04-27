///Control [Header]
#ifndef CONTROL_H_
#define CONTROL_H_

///Include header
#include <SDL.h>
#include "Console.h"

///Control type
enum CONTROL_TYPE
{
    CONTROL_UP = 0,
    CONTROL_RIGHT,
    CONTROL_DOWN,
    CONTROL_LEFT,
    CONTROL_TYPE_TOTAL
};

///Control value
enum CONTROL_VALUE
{
    CONTROL_ARROW_KEY = 0,
    CONTROL_WASD_KEY,
    CONTROL_IJKL_KEY,
    CONTROL_VALUE_TOTAL
};
const int GET_CONTROL_VALUE[CONTROL_VALUE_TOTAL][CONTROL_TYPE_TOTAL] = { {SDLK_UP, SDLK_RIGHT, SDLK_DOWN, SDLK_LEFT},
                                                                     {SDLK_w, SDLK_d, SDLK_s, SDLK_a},
                                                                     {SDLK_i, SDLK_l, SDLK_k, SDLK_j} };

///Control class
class Control
{
    public:
        //Contructor:
        Control();

        //Destructor:
        ~Control();

        ///function:
        //init:
        void init();

        //get control:
        int getControl(CONTROL_TYPE control_type);

        //set control:
        void setControl(int control_value);

        //close:
        void close();

    private:
        ///Console
        Console* console;

        ///System value
        int key_code[CONTROL_TYPE_TOTAL];

};

#endif // CONTROL_H_
