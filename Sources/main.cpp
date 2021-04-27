/*
A Pacman game by Ba Luong.
Github: 20020001-UET
*/

///Include header
#include "Engine.h"

///Screen dimension
const int ZOOM_SCALE = 3;
const int SCREEN_PIXEL = 8*ZOOM_SCALE;
const int SCREEN_WIDTH = 232*ZOOM_SCALE;
const int SCREEN_HEIGHT = 304*ZOOM_SCALE;

///Game title
const std::string GAME_TITLE = "Pacman";

///Game FPS settings
const int GAME_FPS = 120;
const int frameDelay = 1000 / GAME_FPS;

///main
int main(int argc, char* argv[])
{
    ///Crate Game engine
    Engine* engine = new Engine;

    ///Inititalize Game engine
    engine->init(GAME_TITLE,
                 SCREEN_WIDTH,
                 SCREEN_HEIGHT,
                 SCREEN_PIXEL);

    //Calculate frame time
    Uint32 frameStart;
    int frameTime;

    ///Game loop
    while (engine->isRunning())
    {
        //Start the frame
        frameStart = SDL_GetTicks();

        ///Handle events from player
        engine->handleEvent();

        ///The main game loop
        engine->loop();

        ///The game render
        engine->render();

        ///Handle state
        engine->handleState();

        //End the frame
        frameTime = SDL_GetTicks() - frameStart;
        //Delay time
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    ///Close Game engine
    engine->close();

    ///Delete Game engine
    delete engine;
    engine = NULL;

    return 0;
}
