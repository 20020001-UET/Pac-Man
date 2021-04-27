///Console [Header]
#ifndef CONSOLE_H_
#define CONSOLE_H_

///Include header
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>

///ERRORS_FLAGS enum
enum ERROR_FLAGS
{
    SDL_ERROR = 0,
    IMG_ERROR,
    MIXER_ERROR,
    ERROR_FLAGS_TOTAL
};

///Console class
class Console
{
    public:
        //Constructor:
        Console(const std::string name);
        //Destructor:
        ~Console();

        //writeLine:
        void writeLine(const std::string line);

        //logError:
        void logError(const std::string error, ERROR_FLAGS flag = SDL_ERROR);

    private:
        //main part name:
        std::string main_name;

};

#endif // CONSOLE_H_

