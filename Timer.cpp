///Timer [Source]
#include "Timer.h"

///Include header
#include <SDL.h>

///Timer class
//Constructor:
Timer::Timer()
{
    console = new Console("Timer");

    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;

    return;
}

//Destructor:
Timer::~Timer()
{
    delete console;
    console = NULL;
    return;
}

///function:
//init:
void Timer::init()
{
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;

    start();

    console->writeLine("Initialized Timer");
    return;
}

void Timer::close()
{
    console->writeLine("Closing Timer. . .");
    return;
}

//start:
void Timer::start()
{
    //Start the timer
    started = true;

    //Unpaused the timer
    paused = false;

    //Get the current time
    startTicks = SDL_GetTicks();
    pausedTicks = 0;

    return;
}

//stop:
void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpaused the timer
    paused = false;

    //Clear tick variables
    startTicks = 0;
    pausedTicks = 0;

    return;
}

//paused:
void Timer::pause()
{
    //If the timer is running and isn't already paused
    if (started && !paused)
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
    return;
}

//unpause:
void Timer::unpause()
{
    //If the timer is running and paused
    if (started && paused)
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
    return;
}

//getTicks:
Uint32 Timer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if (started)
    {
        //If the timer is paused
        if (paused)
        {
            //Return the number of ticks when the timer was paused
            time = pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

//Check status:
bool Timer::isStarted()
{
    //Timer is running and paused or unpaused
    return started;
}

bool Timer::isPaused()
{
    //Timer is running and paused
    return paused && started;
}
