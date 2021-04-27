///Sound [Header]
#ifndef SOUND_H_
#define SOUND_H_

///Include header
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "Console.h"

///Sound class
class Sound
{
    public:
        //Constructor:
        Sound();

        //Destructor:
        ~Sound();

        ///function:
        //init:
        void init();

        //load:
        Mix_Chunk* loadEffect(std::string path);
        Mix_Music* loadMusic(std::string path);

        //play
        void play(Mix_Chunk* chunk, bool loop, int channel);
        void play(Mix_Music* music, bool loop);

        //close:
        void close();

    private:
        ///Console
        Console* console;

};

#endif // SOUND_H_
