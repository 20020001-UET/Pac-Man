///State [Header]
#ifndef STATE_H_
#define STATE_H_

///Include header
#include "System.h"

///State Type
enum STATE_TYPE
{
    UNSET_STATE = -1,
    MENU_STATE,
    PLAYING_STATE,
    HOW_TO_PLAY_STATE,
    SETTING_STATE,
    HIGHSCORE_STATE,
    ABOUT_STATE,
    RESUME_STATE,
    SAVE_SETTING_STATE,
    EXIT_GAME_STATE,
    GAME_OVER_STATE,
    WIN_GAME_STATE,
    CLOSE_STATE,
    RETURN_STATE,
    EXIT_STATE,
    STATE_TYPE_TOTAL
};

///State class
class State
{
    public:
        //Constructor:
        State();
        State(System* _system);

        //Destructor:
        virtual ~State();

        ///main function:
        //init:
        virtual void init(System* _system) {};

        //loop:
        virtual void loop() = 0;

        //render:
        virtual void render() = 0;

        //handle key event:
        virtual void keyPressed(const int key_code) = 0;
        virtual void keyReleased(const int key_code) = 0;

        //close:
        virtual void close() {};

        //pull state function:
        void pull(STATE_TYPE _request);
        STATE_TYPE request();
        void pulled();

    protected:
        ///The request State
        STATE_TYPE requestState;

        ///System
        System* system;
};

#endif // STATE_H_
