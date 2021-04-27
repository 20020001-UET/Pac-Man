///State [Source]
#include "State.h"

///Include header

///State class
//Constructor:
State::State()
{
    requestState = UNSET_STATE;
    return;
}

State::State(System* _system)
{
    system = _system;
    return;
}

//Destructor:
State::~State()
{
    system = NULL;
    return;
}

//pull state function:
void State::pull(STATE_TYPE _request)
{
    requestState = _request;
    return;
}

STATE_TYPE State::request()
{
    return requestState;
}

void State::pulled()
{
    requestState = UNSET_STATE;
    return;
}
