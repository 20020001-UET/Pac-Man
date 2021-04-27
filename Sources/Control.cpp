///Control [Source]
#include "Control.h"

///Include header

///Control class
//Constructor:
Control::Control()
{
    console = new Console("Control");
    return;
}

//Destructor:
Control::~Control()
{
    delete console;
    console = NULL;
    return;
}

///function:
//init:
void Control::init()
{
    setControl(CONTROL_ARROW_KEY);
    console->writeLine("Initialized Control");
    return;
}

//get control:
int Control::getControl(CONTROL_TYPE control_type)
{
    return key_code[control_type];
}

//set control:
void Control::setControl(int control_value)
{
    for (int index = 0; index < CONTROL_TYPE_TOTAL; index++)
        key_code[index] = GET_CONTROL_VALUE[control_value][index];
    return;
}

//close:
void Control::close()
{
    console->writeLine("Closing Control. . .");
    return;
}
