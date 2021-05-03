///Audio [Header]
#ifndef AUDIO_H_
#define AUDIO_H_

///Include header
#include <SDL_mixer.h>
#include "Console.h"
#include "Sound.h"

///Music
enum MUSIC_TYPE
{
    GAME_START = 0,
    INTERMISSION,
    MUSIC_TYPE_TOTAL
};

///Effect
enum EFFECT_TYPE
{
    CREDIT = 0,
    MUNCH,
    EXTEND,
    UPGRADE,
    POWER_PELLET,
    SIREN,
    DEATH,
    EAT_GHOST,
    EAT_FRUIT,
    CONFUSED,
    FREEZE,
    SPEED,
    BOSS_SHOW_UP,
    UPGRADE_MYSTERY,
    EFFECT_TYPE_TOTAL
};

///Audio class
class Audio
{
    public:
        //Constructor:
        Audio();

        //Destructor:
        ~Audio();

        ///function:
        //init:
        bool init(const int frequency = 44100, const int channels = 2, const int chunkSize = 2048);

        //load:
        void load();

        //free:
        void free();

        //close:
        void close();

        //play:
        void play(MUSIC_TYPE music_type, bool loop = false);
        void play(EFFECT_TYPE effect_type, bool loop = false, const int channel = -1);

        //set volume:
        void setMusicVolume(const int volume);
        void setChannelVolume(const int volume);

        ///Music:
        //status function:
        bool isPlaying();
        bool isPause();
        void stop();
        void pause();
        void unpause();

        ///Channel:
        //status function:
        bool isPlayingChannel(int channel = -1);
        bool isPauseChannel(int channel = -1);
        void stopChannel(int channel = -1);
        void pauseChannel(int channel = -1);
        void unpauseChannel(int channel = -1);

        int getMusicVolume();
        int getChannelVolume();

    private:
        ///Console
        Console* console;

        ///Sound
        Sound* sound;

        ///Musics
        Mix_Music* game_start;
        Mix_Music* intermission;

        ///Effects
        Mix_Chunk* credit;
        Mix_Chunk* munch;
        Mix_Chunk* upgrade;
        Mix_Chunk* extend;
        Mix_Chunk* power_pellet;
        Mix_Chunk* siren;
        Mix_Chunk* death;
        Mix_Chunk* eat_ghost;
        Mix_Chunk* eat_fruit;
        Mix_Chunk* confused;
        Mix_Chunk* freeze;
        Mix_Chunk* speed;
        Mix_Chunk* boss_show_up;
        Mix_Chunk* upgrade_mystery;

        ///System value
        int musicVolume;
        int channelVolume;

};

#endif // AUDIO_H_
