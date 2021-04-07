///Engine [Header]
#ifndef ENGINE_H_
#define ENGINE_H_

///SDL libraries
#include <SDL.h>
#include <SDL_image.h>

///Project headers
#include "Console.h"
#include "Texture.h"
#include "Resources.h"
#include "StateManager.h"

///Engine class
class Engine
{
    public:
        static void init(std::string _title, int _width, int _height, int _pixel);
        static bool isRunning();
        static void handleEvents();
        static void loop();
        static void render();
        static void close();

        static int getWidth();
        static int getHeight();
        static int getPixel();

        static void stateAdd(State* newState);
        static void stateClose();
        static void stateExit();

    private:
        static SDL_Window* window;
        static SDL_Renderer* renderer;
        static bool running;
        static int width, height, pixel;

        static Console console;

        static StateManager state;
};

#endif // ENGINE_H_
