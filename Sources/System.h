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
    //update system:
    void update();
    //save:
    void save(std::string path = SYSTEM_CONFIG_PATH);
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
    int musicVolume, channelVolume;
    int zoomScale;
    int controlType;

};

#endif // SYSTEM_H_
