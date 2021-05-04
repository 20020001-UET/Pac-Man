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
    upgrade = NULL;
    extend = NULL;
    power_pellet = NULL;
    siren = NULL;
    death = NULL;
    eat_ghost = NULL;
    eat_fruit = NULL;
    confused = NULL;
    freeze = NULL;
    speed = NULL;
    boss_show_up = NULL;
    upgrade_mystery = NULL;
    boss_death = NULL;

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

    upgrade = sound->loadEffect("Assets/Sound/ghost_upgrade.wav");

    extend = sound->loadEffect("Assets/Sound/extend.wav");

    power_pellet = sound->loadEffect("Assets/Sound/power_pellet.wav");

    siren = sound->loadEffect("Assets/Sound/siren_1.wav");

    death = sound->loadEffect("Assets/Sound/death_1.wav");

    eat_ghost = sound->loadEffect("Assets/Sound/eat_ghost.wav");

    eat_fruit = sound->loadEffect("Assets/Sound/eat_fruit.wav");

    confused = sound->loadEffect("Assets/Sound/confused.wav");

    freeze = sound->loadEffect("Assets/Sound/freeze.wav");

    speed = sound->loadEffect("Assets/Sound/speed.wav");

    boss_show_up = sound->loadEffect("Assets/Sound/boss_show_up.wav");

    upgrade_mystery = sound->loadEffect("Assets/Sound/upgrade_mystery.wav");

    boss_death = sound->loadEffect("Assets/Sound/boss_death.wav");

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
        case EXTEND:
            sound->play(extend, loop, channel);
            break;
        case UPGRADE:
            sound->play(upgrade, loop, channel);
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
        case CONFUSED:
            sound->play(confused, loop, channel);
            break;
        case FREEZE:
            sound->play(freeze, loop, channel);
            break;
        case SPEED:
            sound->play(speed, loop, channel);
            break;
        case BOSS_SHOW_UP:
            sound->play(boss_show_up, loop, channel);
            break;
        case UPGRADE_MYSTERY:
            sound->play(upgrade_mystery, loop, channel);
            break;
        case BOSS_DEATH:
            sound->play(boss_death, loop, channel);
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
    Mix_FreeChunk(upgrade);
    upgrade = NULL;
    Mix_FreeChunk(extend);
    extend = NULL;
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
    Mix_FreeChunk(confused);
    confused = NULL;
    Mix_FreeChunk(freeze);
    freeze = NULL;
    Mix_FreeChunk(speed);
    speed = NULL;
    Mix_FreeChunk(boss_show_up);
    boss_show_up = NULL;
    Mix_FreeChunk(upgrade_mystery);
    upgrade_mystery = NULL;
    Mix_FreeChunk(boss_death);
    boss_death = NULL;

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
