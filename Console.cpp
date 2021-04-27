///Console [Source]
#include "Console.h"

///Include header
#include <iostream>

///Console class
//constructor:
Console::Console(const std::string name)
{
    main_name = name;
    return;
}

//destructor:
Console::~Console()
{

}

//writeLine:
void Console::writeLine(const std::string line)
{
    std::cout << '[' << main_name << "]: " << line << '\n';
    return;
}

//logError:
void Console::logError(const std::string error, ERROR_FLAGS flag)
{
    std::cout << '[' << main_name << "]: Error - " << error;
    switch (flag)
    {
        case SDL_ERROR:
            std::cout << " - SDL Error: " << SDL_GetError() << '\n';
            break;
        case IMG_ERROR:
            std::cout << " - SDL_image Error: " << IMG_GetError() << '\n';
            break;
        case MIXER_ERROR:
            std::cout << " - SDL_mixer Error: "<< Mix_GetError() << '\n';
            break;
        default:
            break;
    }
    return;
}


