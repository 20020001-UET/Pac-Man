///Engine [Source]
#include "Engine.h"
#include "MenuState.h"

///Engine class
SDL_Window* Engine::window = NULL;
SDL_Renderer* Engine::renderer = NULL;

bool Engine::running = false;
int Engine::width, Engine::height, Engine::pixel;

Console Engine::console = Console("Engine");

StateManager Engine::state;

//Playing Engine::playing;

void Engine::init(std::string _title, int _width, int _height, int _pixel)
{
    running = true;
    window = NULL;
    renderer = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        //Error:
        console.logError("SDL could not be initialized!", ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }

    console.writeLine("Initialized SDL");

    width = _width;
    height = _height;
    pixel = _pixel;

    window = SDL_CreateWindow(_title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        //Error:
        console.logError("Window could not be created!", ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }

    console.writeLine("Created Window.");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        //Error:
        console.logError("Renderer could not be created!", ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }

    console.writeLine("Created renderer");

    int IMG_flags = IMG_INIT_PNG;
    if (IMG_Init(IMG_flags) != IMG_flags)
    {
        //Error:
        console.logError("SDL_image could not be initialized!", ERROR_FLAGS::IMG_ERROR);
        running = false;
        return;
    }

    console.writeLine("Initialized IMG: PNG");

    Texture::init(renderer);

    Resources::load();

    state.addState(new MenuState);
}

bool Engine::isRunning()
{
    return running;
}

void Engine::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                stateExit();
                break;

            case SDL_KEYDOWN:
                state.keyPressed(event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                state.keyReleased(event.key.keysym.sym);
                break;
        }
    }
}

void Engine::loop()
{
    state.loop();
}

void Engine::render()
{
    //Clear screen
    //Black background
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    //Render
    state.render();

    //Update screen
    SDL_RenderPresent(renderer);
}

void Engine::close()
{
    while (state.checkState())
        state.closeState();

    Resources::free();

    Texture::close();

    console.writeLine("Closing engine. . .");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

//function:
int Engine::getPixel()
{
    return pixel;
}

int Engine::getWidth()
{
    return width;
}

int Engine::getHeight()
{
    return height;
}

void Engine::stateAdd(State* newState)
{
    state.addState(newState);
}

void Engine::stateClose()
{
    state.closeState();
}

void Engine::stateExit()
{
    console.writeLine("Closing window. . .");
    running = false;
}
