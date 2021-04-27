///State Manager [Header]
#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

///Include header
#include "State.h"
#include "Console.h"
#include <Stack>

///State Manager class
class StateManager
{
    public:
        //Constructor:
        StateManager();

        //Destructor:
        ~StateManager();

        ///main function:
        //init:
        void init(System* _system);

        //close:
        void close();

        ///state function:
        //add:
        void add(State* state);

        //loop:
        void loop();

        //render:
        void render();

        //handle key event:
        void keyPressed(const int key_code);
        void keyReleased(const int key_code);

        //remove:
        void remove();

        //is the stack empty?
        bool isEmpty();

        //state request:
        bool pullRequest();

    private:
        ///Stack State
        std::stack<State*> states;

        ///Console
        Console* console;

        ///System
        System* system;
};

#endif // STATE_MANAGER_H_
