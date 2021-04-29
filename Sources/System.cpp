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

    highscore = 0;
    highscore_set.clear();

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
        config >> musicVolume >> channelVolume >> controlType >> mainCharacter;
        console->writeLine("Loading system config done!");
    }
    else
    {
        console->writeLine("Could not read config file!");
    }

    config.close();

    return;
}

void System::loadHighscore(std::string path)
{
    std::ifstream highscore_file(path);

    highscore_set.clear();

    if (highscore_file.good())
    {
        int total;
        highscore_file >> total;
        while (total--)
        {
            Uint32 tmp;
            highscore_file >> tmp;
            highscore_set.insert(tmp);
        }
        if (!highscore_set.empty())
            highscore = (*highscore_set.begin());
        console->writeLine("Loading highscore done!");
    }
    else
    {
        highscore = 0;
        console->writeLine("Could not read highscore file!");
    }

    highscore_file.close();

    return;
}

//update:
void System::update()
{
    audio->setMusicVolume(VOLUME_SETTING_VALUE[musicVolume]);
    audio->setChannelVolume(VOLUME_SETTING_VALUE[channelVolume]);

    control->setControl(controlType);

    return;
}

//save:
void System::save(std::string path)
{
    std::ofstream config(path);

    if (config.good())
    {
        config << musicVolume << ' ' << channelVolume << '\n' << controlType << '\n' << mainCharacter;
        console->writeLine("Saving system config done!");
    }
    else
    {
        console->writeLine("Could not write config file!");
    }

    config.close();

    return;
}

void System::saveHighscore(Uint32 score, std::string path)
{
    std::ofstream highscore_file(path);

    if (highscore_file.good())
    {
        highscore_set.insert(score);

        if (highscore_set.size() >= 10)
        {
            highscore_file << "10\n";
        }
        else
        {
            highscore_file << highscore_set.size() << '\n';
        }

        int cnt = 0;
        std::multiset<Uint32, std::greater<Uint32>>::iterator it;
        for (it = highscore_set.begin(); it != highscore_set.end(); ++it)
        {
            Uint32 tmp = (*it);

            cnt++;
            if (cnt <= 10)
            {
                highscore_file << tmp << '\n';
            }
            else
                break;
        }
        console->writeLine("Saving highscore done!");
    }
    else
    {
        highscore = 0;
        console->writeLine("Could not write highscore file!");
    }

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
