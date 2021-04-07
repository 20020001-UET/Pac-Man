#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

#include <stack>
#include "State.h"

class StateManager
{
    public:
        void addState(State* state);
        void loop();
        void render();
        void keyPressed(int key_code);
        void keyReleased(int key_code);
        void closeState();
        bool checkState();

    private:
        std::stack<State*> states;
};

#endif // STATE_MANAGER_H_
