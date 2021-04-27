///Timer [Header]
#ifndef TIMER_H_
#define TIMER_H_

///Include header
#include "Console.h"

///Timer class
class Timer
{
    public:
        //Constructor:
        Timer();

        //Destructor:
        ~Timer();

        ///function:
        //init:
        void init();

        //close:
        void close();

        //The timer actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Get the timer's time
        Uint32 getTicks();

        //Check the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        //The console that the timer write to
        Console* console;

        //The time when the timer started
        Uint32 startTicks;
        //The ticks stored when the timer was paused
        Uint32 pausedTicks;

        //The timer status
        bool started;
        bool paused;
};

#endif // TIMER_H_

