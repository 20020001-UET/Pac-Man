///Audio [Source]
#include "Audio.h"

///Include header
#include "Sound.h"
#include <sstream>

///Audio class
//Constructor:
Audio::Audio()
{
    console = new Console("Audio");

    sound = new Sound;

    game_start = NULL;
    intermission = NULL;

    credit = NULL;
    munch = NULL;
    power_pellet = NULL;
    siren = NULL;
    death = NULL;
    eat_ghost = NULL;
    eat_fruit = NULL;

    return;
}

//Destructor:
Audio::~Audio()
{
    delete sound;
    sound = NULL;
    delete console;
    console = NULL;
    return;
}

///function:
//init:
bool Audio::init(const int frequency, const int channels, const int chunkSize)
{
    //Initialize SDL_mixer
    if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunkSize) != 0)
    {
        //Error:
        console->logError("SDL_image could not initialize!", ERROR_FLAGS::MIXER_ERROR);
        return false;
    }
    std::stringstream mixerInfo;
    mixerInfo << "Initialized MIXER: ";
    mixerInfo << frequency << "Hz - " << channels << " channel - Chunk size: " << chunkSize;
    console->writeLine(mixerInfo.str().c_str());

    musicVolume = MIX_MAX_VOLUME;
    channelVolume = MIX_MAX_VOLUME;

    sound->init();

    load();

    console->writeLine("Initialized Audio");
    return true;
}

//load:
void Audio::load()
{
    console->writeLine("Loading musics and sound effects. . .");

    ///Load Music
    game_start = sound->loadMusic("Assets/Sound/game_start.wav");

    intermission = sound->loadMusic("Assets/Sound/intermission.wav");

    ///Load Effect
    credit = sound->loadEffect("Assets/Sound/credit.wav");

    munch = sound->loadEffect("Assets/Sound/munch_1.wav");

    power_pellet = sound->loadEffect("Assets/Sound/power_pellet.wav");

    siren = sound->loadEffect("Assets/Sound/siren_1.wav");

    death = sound->loadEffect("Assets/Sound/death_1.wav");

    eat_ghost = sound->loadEffect("Assets/Sound/eat_ghost.wav");

    eat_fruit = sound->loadEffect("Assets/Sound/eat_fruit.wav");

    return;
}

//play:
void Audio::play(MUSIC_TYPE music_type, bool loop)
{
    switch (music_type)
    {
        case GAME_START:
            sound->play(game_start, loop);
            break;
        case INTERMISSION:
            sound->play(intermission, loop);
            break;
        default:
            break;
    }
    return;
}

void Audio::play(EFFECT_TYPE effect_type, bool loop, const int channel)
{
    switch (effect_type)
    {
        case CREDIT:
            sound->play(credit, loop, channel);
            break;
        case MUNCH:
            sound->play(munch, loop, channel);
            break;
        case POWER_PELLET:
            sound->play(power_pellet, loop, channel);
            break;
        case SIREN:
            sound->play(siren, loop, channel);
            break;
        case DEATH:
            sound->play(death, loop, channel);
            break;
        case EAT_GHOST:
            sound->play(eat_ghost, loop, channel);
            break;
        case EAT_FRUIT:
            sound->play(eat_fruit, loop, channel);
            break;
        default:
            break;
    }
    return;
}

//set volume:
void Audio::setMusicVolume(const int volume)
{
    musicVolume = volume;
    Mix_VolumeMusic(volume);
    return;
}

void Audio::setChannelVolume(const int volume)
{
    channelVolume = volume;
    Mix_Volume(-1, volume);
    return;
}

///Music:
//status function:
bool Audio::isPlaying()
{
    return (Mix_PlayingMusic() != 0);
}

bool Audio::isPause()
{
    return (Mix_PausedMusic() == 1);
}

void Audio::stop()
{
    //Stop the music
    Mix_HaltMusic();
    return;
}

void Audio::pause()
{
    //If the music is playing
    if(!isPause())
    {
        //Pause the music
        Mix_PauseMusic();
    }
    return;
}

void Audio::unpause()
{
    //If the music is paused
    if(isPause())
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    return;
}

///Channel:
bool Audio::isPlayingChannel(int channel)
{
    return (Mix_Playing(channel) == 1);
}

bool Audio::isPauseChannel(int channel)
{
    return (Mix_Paused(channel) == 1);
}

void Audio::stopChannel(int channel)
{
    Mix_HaltChannel(channel);
    return;
}

void Audio::pauseChannel(int channel)
{
    if (!Mix_Paused(channel))
    {
        Mix_Pause(channel);
    }
    return;
}

void Audio::unpauseChannel(int channel)
{
    if (Mix_Paused(channel))
    {
        Mix_Resume(channel);
    }
    return;
}

int Audio::getMusicVolume()
{
    return musicVolume;
}

int Audio::getChannelVolume()
{
    return channelVolume;
}

//free:
void Audio::free()
{
    console->writeLine("Freeing musics and sound effects. . .");

    Mix_FreeMusic(game_start);
    game_start = NULL;
    Mix_FreeMusic(intermission);
    intermission = NULL;


    Mix_FreeChunk(credit);
    credit = NULL;
    Mix_FreeChunk(munch);
    munch = NULL;
    Mix_FreeChunk(power_pellet);
    power_pellet = NULL;
    Mix_FreeChunk(siren);
    siren = NULL;
    Mix_FreeChunk(death);
    death = NULL;
    Mix_FreeChunk(eat_ghost);
    eat_ghost = NULL;
    Mix_FreeChunk(eat_fruit);
    eat_fruit = NULL;

    return;
}

//close:
void Audio::close()
{
    console->writeLine("Closing Audio. . .");

    free();

    sound->close();

    //Mix_Quit();
    //Close Audio
    Mix_CloseAudio();

    return;
}
