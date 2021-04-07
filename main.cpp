/*
A Pacman game by Ba Luong.
Github: 20020001-UET
*/

///Project headers
#include "Engine.h"

///Screen dimension
const int SCREEN_PIXEL = 25;
const int SCREEN_WIDTH = SCREEN_PIXEL*28;
const int SCREEN_HEIGHT = SCREEN_PIXEL*(31 + 3);

///Game title
const std::string GAME_TITLE = "Pacman";

///Game FPS settings
const int FPS = 60;
const int frameDelay = 1000/FPS;

///main() function
int main(int argc, char* argv[])
{
    ///Initialize Game engine:
    Engine::init(GAME_TITLE,
                 SCREEN_WIDTH,
                 SCREEN_HEIGHT,
                 SCREEN_PIXEL);

    //Calculate frame time
    Uint32 frameStart;
    int frameTime;

    ///Game loop
    while (Engine::isRunning())
    {
        //Start the frame
        frameStart = SDL_GetTicks();

        ///Handle events from player
        Engine::handleEvents();

        ///The main game loop
        Engine::loop();

        ///The game render
        Engine::render();

        //End the frame
        frameTime = SDL_GetTicks() - frameStart;
        //Delay time
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    ///Close engine
    Engine::close();

    return 0;
}
