///Engine [Header]
#ifndef ENGINE_H_
#define ENGINE_H_

///Include header
#include <SDL.h>
#include "Console.h"
#include "System.h"
#include "StateManager.h"

///Engine class
class Engine
{
    public:
        //Constructor:
        Engine();

        //Destructor:
        ~Engine();

        ///function:
        //init:
        void init(const std::string _title, const int _width, const int _height, const int _pixel);

        //isRunning:
        bool isRunning();

        //handleEvent:
        void handleEvent();

        //loop:
        void loop();

        //render:
        void render();

        //handleState:
        void handleState();

        //close:
        void close();

    private:
        ///main window
        SDL_Window* window;
        SDL_Renderer* renderer;

        //status:
        bool running;

        //infomation:
        int width, height, pixel;
        std::string title;

        ///Console
        Console* console;

        ///System
        System* system;

        ///State
        StateManager* state;

};

#endif // ENGINE_H_
