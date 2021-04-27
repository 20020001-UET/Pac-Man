///Engine [Source]
#include "Engine.h"

///Include header
#include <sstream>

///Engine class
//Constructor:
Engine::Engine()
{
    ///Window
    window = NULL;
    renderer = NULL;

    ///Status
    running = false;

    ///Information
    width = height = pixel = 0;
    title = "";

    ///Console
    console = new Console("Engine");

    ///System
    system = new System;

    ///State
    state = new StateManager;

    return;
}

//Destructor:
Engine::~Engine()
{
    ///Delete Console
    delete console;
    console = NULL;

    ///Delete System
    delete system;
    system = NULL;

    ///State
    delete state;
    state = NULL;

    return;
}

///function:
//init:
void Engine::init(const std::string _title, const int _width, const int _height, const int _pixel)
{
    //Initialize flag
    running = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        //Error:
        console->logError("SDL could not initialize!", ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }
    console->writeLine("Initialized SDL");

    //Create window
    width = _width;
    height = _height;
    pixel = _pixel;
    title = _title;
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        //Error:
        console->logError("Window could not be created!", ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }
    console->writeLine("Created Window.");

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        //Error:
        console->logError("Renderer could not be created!", ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }
    console->writeLine("Created Renderer");

    ///Initialize System
    system->init();
    //Initialize Audio
    running = system->initAudio(44100, 2, 2048);
    //Initialize Graphic
    running = system->initGraphic(renderer, IMG_INIT_PNG);
    //Initialize Timer
    system->initTimer();
    //Initialize Control
    system->initControl();

    ///Load system config
    system->load();

    //Initialize State
    state->init(system);

    return;
}

//isRunning:
bool Engine::isRunning()
{
    return running;
}

//handleEvent:
void Engine::handleEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                state->keyPressed(event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                state->keyReleased(event.key.keysym.sym);
                break;
        }
    }
    return;
}

//loop:
void Engine::loop()
{
    state->loop();
    return;
}

//render:
void Engine::render()
{
    //Render
    system->graphic->setViewPort(MAIN_VIEWPORT);
    state->render();

    //Update screen
    SDL_RenderPresent(renderer);
    return;
}

//handleState:
void Engine::handleState()
{
    if (running)
        running = state->pullRequest();
    return;
}

//close:
void Engine::close()
{
    console->writeLine("Closing Engine. . .");

    //Closing States
    state->close();

    ///Closing System
    system->close();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}
