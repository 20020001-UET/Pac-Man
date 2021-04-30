///System [Header]
#ifndef SYSTEM_H_
#define SYSTEM_H_

///Include header
#include <SDL.h>
#include "Console.h"
#include "Audio.h"
#include "Graphic.h"
#include "Timer.h"
#include "Control.h"
#include <set>

///System config
const std::string SYSTEM_CONFIG_PATH = "system.config";
const std::string SYSTEM_HIGHSCORE_PATH = "highscore.dat";

///Volume setting
const int VOLUME_SETTING_TOTAL = 11;
const int VOLUME_SETTING_VALUE[VOLUME_SETTING_TOTAL] = {0, 12, 24, 36, 48, 60, 72, 84, 96, 108, 128};

///System struct
struct System
{
    //Contructor:
    System();

    //Destructor:
    ~System();

    ///function:
    //init:
    void init();
    bool initAudio(const int frequency = 44100, const int channels = 2, const int chunkSize = 2048);
    bool initGraphic(SDL_Renderer* _renderer, const int IMG_flags = IMG_INIT_PNG);
    void initTimer();
    void initControl();
    //load:
    void load(std::string path = SYSTEM_CONFIG_PATH);
    void loadHighscore(std::string path = SYSTEM_HIGHSCORE_PATH);
    //update system:
    void update();
    //save:
    void save(std::string path = SYSTEM_CONFIG_PATH);
    void saveHighscore(Uint32 score, int level, std::string path = SYSTEM_HIGHSCORE_PATH);
    //close:
    void close();

    ///Console
    Console* console;

    ///System
    Audio* audio;
    Graphic* graphic;
    Timer* timer;
    Control* control;

    ///System value
    std::multiset<Uint32, std::greater<Uint32>> highscore_set;
    int lastLevel;
    Uint32 lastScore, highscore;
    int musicVolume, channelVolume;
    int mainCharacter;
    int controlType;

};

#endif // SYSTEM_H_
