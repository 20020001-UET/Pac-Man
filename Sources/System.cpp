///System [Source]
#include "System.h"

///Include header
#include <fstream>

///System struct
//Constructor:
System::System()
{
    console = new Console("System");

    audio = NULL;
    graphic = NULL;
    timer = NULL;
    control = NULL;

    return;
}

//Destructor:
System::~System()
{
    delete console;
    console = NULL;

    audio = NULL;
    graphic = NULL;
    timer = NULL;
    control = NULL;

    return;
}

///function:
//init:
void System::init()
{
    audio = new Audio;
    graphic = new Graphic;
    timer = new Timer;
    control = new Control;

    console->writeLine("Initialize system. . .");

    return;
}

bool System::initAudio(const int frequency, const int channels, const int chunkSize)
{
    return audio->init(frequency, channels, chunkSize);
}

bool System::initGraphic(SDL_Renderer* renderer, const int IMG_flags)
{
    return graphic->init(renderer, IMG_flags);
}

void System::initTimer()
{
    timer->init();
    return;
}

void System::initControl()
{
    control->init();
    return;
}

//load:
void System::load(std::string path)
{
    std::ifstream config(path);

    if (config.good())
    {
        config >> musicVolume >> channelVolume >> controlType >> zoomScale;
        console->writeLine("Loading system config done!");
    }
    else
    {
        console->writeLine("Could not read config file!");
    }

    config.close();
    return;
}

//update:
void System::update()
{
    audio->setMusicVolume(VOLUME_SETTING_VALUE[musicVolume]);
    audio->setChannelVolume(VOLUME_SETTING_VALUE[channelVolume]);

    control->setControl(controlType);

    graphic->setZoomScale(zoomScale);

    return;
}

//save:
void System::save(std::string path)
{
    std::ofstream config(path);

    if (config.good())
    {
        config << musicVolume << ' ' << channelVolume << '\n' << controlType << '\n' << zoomScale;
        console->writeLine("Saving system config done!");
    }
    else
    {
        console->writeLine("Could not write config file!");
    }

    config.close();
    return;
}

//close:
void System::close()
{
    console->writeLine("Closing system. . .");

    audio->close();
    graphic->close();
    timer->close();
    control->close();

    delete audio;
    audio = NULL;
    delete graphic;
    graphic = NULL;
    delete timer;
    timer = NULL;
    delete control;
    control = NULL;

    return;
}
