///Console [Header]
#ifndef CONSOLE_H_
#define CONSOLE_H_

//include SDL libraries
#include <SDL.h>
#include <SDL_image.h>

//C++ library
#include <string>

enum ERROR_FLAGS
{
    SDL_ERROR = 0,
    IMG_ERROR
};

///Console class
class Console
{
    public:
        Console(std::string name);
        void writeLine(std::string line);
        void logError(std::string error, ERROR_FLAGS flag = SDL_ERROR);

    private:
        std::string main_name;

};

#endif // CONSOLE_H_

