///Sound [Source]
#include "Sound.h"

///Include header

//Constructor:
Sound::Sound()
{
    console = NULL;
    return;
}

//Destructor:
Sound::~Sound()
{
    delete console;
    console = NULL;
    return;
}

///function:
//init:
void Sound::init()
{
    console = new Console("Sound");

    console->writeLine("Initialized mixer sub-system.");
    return;
}

//load:
Mix_Chunk* Sound::loadEffect(std::string path)
{
    console->writeLine("Loading file: " + path);
    Mix_Chunk* tmpChunk = NULL;
    tmpChunk = Mix_LoadWAV(path.c_str());

    if (tmpChunk == NULL)
    {
        //Error:
        console->logError("Can't load sound effect from file: " + path, ERROR_FLAGS::MIXER_ERROR);
        return tmpChunk;
    }

    return tmpChunk;
}

Mix_Music* Sound::loadMusic(std::string path)
{
    console->writeLine("Loading file: " + path);
    Mix_Music* tmpMusic = NULL;
    tmpMusic = Mix_LoadMUS(path.c_str());

    if (tmpMusic == NULL)
    {
        //Error:
        console->logError("Can't load music from file: " + path, ERROR_FLAGS::MIXER_ERROR);
        return tmpMusic;
    }

    return tmpMusic;
}

//play:
void Sound::play(Mix_Chunk* chunk, bool loop, int channel)
{
    int loops = (loop) ? -1 : 0;
    Mix_PlayChannel(channel, chunk, loops);
    return;
}

void Sound::play(Mix_Music* music, bool loop)
{
    int loops = (loop) ? -1 : 1;
    Mix_PlayMusic(music, loops);
    return;
}

//close:
void Sound::close()
{
    console->writeLine("Closing mixer sub-system. . .");
    return;
}
