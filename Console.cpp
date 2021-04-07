///Console [Source]
#include "Console.h"

//C++ library
#include <iostream>

///Console class
//constructor:
Console::Console(std::string name)
{
    main_name = name;
}

//writeLine
void Console::writeLine(std::string line)
{
    std::cout << '[' << main_name << "]: " << line << '\n';
}

//logError
void Console::logError(std::string error, ERROR_FLAGS flag)
{
    std::cout << '[' << main_name << "]: Error - " << error;
    switch (flag)
    {
        case SDL_ERROR:
            std::cout << " SDL Error: " << SDL_GetError() << '\n';
            break;
        case IMG_ERROR:
            std::cout << " SDL Error: " << IMG_GetError() << '\n';
            break;
    }
}

