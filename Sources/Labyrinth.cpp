///Labyrinth [Source]
#include "Labyrinth.h"

///Include header
#include <fstream>
#include <random>

///Labyrinth class
Labyrinth::Labyrinth()
{
    console = new Console("Labyrinth");
    graphic = NULL;
    type = LABYRINTH_DEFAULT;
    dest = {0, 0, LABYRINTH_WIDTH, LABYRINTH_HEIGHT};
    return;
}

Labyrinth::~Labyrinth()
{
    delete console;
    console = NULL;
    graphic = NULL;
    return;
}

///function:
//init:
void Labyrinth::init(Graphic* _graphic)
{
    graphic = _graphic;
    animated = false;
    frame = 0;
    frame_value = LABYRINTH_FRAME_VALUE;
    dotRemain = 0;
    return;
}

//load:
void Labyrinth::renew()
{
    for (int x = 0; x < LABYRINTH_DATA_WIDTH; x++)
    {
        for (int y = 0; y < LABYRINTH_DATA_HEIGHT; y++)
        {
            data[x][y] = 0;
            isDot[x][y] = false;
        }
    }
    return;
}

void Labyrinth::load(const std::string path)
{
    renew();

    std::ifstream input(path);

    if (input.good())
    {
        for (int y = 0; y < LABYRINTH_DATA_HEIGHT; y++)
        {
            for (int x = 0; x < LABYRINTH_DATA_WIDTH; x++)
            {
                input >> data[x][y];
                isDot[x][y] = (data[x][y] == DOT_DATA || data[x][y] == POWER_DOT_DATA);
                if (data[x][y] == PACMAN_STAND_DATA)
                {
                    pacman_stand = Point(x, y);
                    data[x][y] = 1;
                }

                if (data[x][y] == GHOST_START_DATA)
                {
                    ghost_start = Point(x, y);
                    blinky_stand = ghost_start;
                    data[x][y] = 1;
                }

                if (data[x][y] == PINKY_STAND_DATA)
                {
                    pinky_stand = Point(x, y);
                    data[x][y] = 1;
                }

                if (data[x][y] == INKY_STAND_DATA)
                {
                    inky_stand = Point(x, y);
                    data[x][y] = 1;
                }

                if (data[x][y] == CLYDE_STAND_DATA)
                {
                    clyde_stand = Point(x, y);
                    data[x][y] = 1;
                }

                if (isDot[x][y])
                {
                    dotRemain++;
                    powerDot[x][y] = 0;
                    if (data[x][y] == POWER_DOT_DATA)
                    {
                        powerDot[x][y] = rand() % 4 + 1;
                    }
                }
                else
                {
                    powerDot[x][y] = -1;
                }
            }
        }
    }
    else
    {
        console->writeLine("Can't load labyrinth data file");
    }

    return;
}

//set animation:
void Labyrinth::setAnimated(const bool _animated)
{
    animated = _animated;
    if (!animated)
        type = LABYRINTH_DEFAULT;
    return;
}

//render:
void Labyrinth::render()
{
    if (animated)
    {
        type = LABYRINTH_TYPE_AT[frame / frame_value];
        ++frame;
        if (frame / frame_value >= LABYRINTH_TYPE_TOTAL)
            frame = 0;
    }

    //not animated
    graphic->draw(type, dest);

    dot_render();

    return;
}

void Labyrinth::dot_render()
{
    for (int x = 0; x < LABYRINTH_DATA_WIDTH; x++)
    {
        for (int y = 0; y < LABYRINTH_DATA_HEIGHT; y++)
            if (isDot[x][y])
            {
                dot_dest = {x*RESOURCES_PIXEL-RESOURCES_PIXEL/2, y*RESOURCES_PIXEL-RESOURCES_PIXEL/2, OBJECT_PIXEL, OBJECT_PIXEL};
                DOT_SPRITE type = DOT_SPRITE_TOTAL;
                switch (powerDot[x][y])
                {
                    case DEFAULT_DOT:
                        type = DEFAULT_DOT;
                        break;
                    case POWER_DOT:
                        type = POWER_DOT;
                        break;
                    case SPEED_DOT:
                        type = SPEED_DOT;
                        break;
                    case INVISIBLE_DOT:
                        type = INVISIBLE_DOT;
                        break;
                    case TIME_FREE_DOT:
                        type = TIME_FREE_DOT;
                        break;
                    default:
                        break;
                }
                graphic->draw(OBJECT_DOT, type, dot_dest);
            }
    }
    return;
}

///Check function
bool Labyrinth::isIntersection(Point tile) const
{
    int cnt = 0;
    Point pcnt = Point();
    for (int dir = 1; dir < DIRECTION_TOTAL; dir++)
        if (checkIn(tile + DIRECTION_VALUE[dir]))
            if (getData(tile + DIRECTION_VALUE[dir]) != WALL_DATA)
            {
                cnt++;
                pcnt = pcnt + DIRECTION_VALUE[dir];
            }
    return ( ((cnt == 2) && (pcnt.x != 0) && (pcnt.y != 0)) || (cnt > 2) );
}

bool Labyrinth::isDotOver() const
{
    return (dotRemain == 0);
}

///Pacman function
Point Labyrinth::getPacmanStand() const
{
    return pacman_stand;
}

bool Labyrinth::pacmanCanMove(Point tile, DIRECTION dir) const
{
    if (checkIn(tile + DIRECTION_VALUE[dir]))
        return (getData(tile + DIRECTION_VALUE[dir]) != WALL_DATA && getData(tile + DIRECTION_VALUE[dir]) != GHOST_HOUSE_DATA);
    if (checkIn(tile))
        return (getData(tile) != WALL_DATA && getData(tile) != GHOST_HOUSE_DATA);
    return false;
}

bool Labyrinth::isDotHere(Point tile) const
{
    if (checkIn(tile))
        return isDot[tile.x][tile.y];
    return false;
}

bool Labyrinth::isDotHere(Point screen, DIRECTION dir) const
{
    Point newTile = (screen + DIRECTION_VALUE[dir]*PACMAN_SPEED) / RESOURCES_PIXEL;
    if (checkIn(newTile))
        return isDot[newTile.x][newTile.y];
    return false;
}

int Labyrinth::isPowerDotHere(Point tile) const
{
    if (checkIn(tile))
        if (isDot[tile.x][tile.y])
            if (data[tile.x][tile.y] == POWER_DOT_DATA)
            {
                switch (powerDot[tile.x][tile.y])
                {
                    case DEFAULT_DOT:
                        return DEFAULT_DOT;
                        break;
                    case POWER_DOT:
                        return POWER_DOT;
                        break;
                    case SPEED_DOT:
                        return SPEED_DOT;
                        break;
                    case INVISIBLE_DOT:
                        return INVISIBLE_DOT;
                        break;
                    case TIME_FREE_DOT:
                        return TIME_FREE_DOT;
                        break;
                    default:
                        break;
                }
            }
    return -1;
}

int Labyrinth::isPowerDotHere(Point screen, DIRECTION dir) const
{
    Point newTile = (screen + DIRECTION_VALUE[dir]*PACMAN_SPEED/2) / RESOURCES_PIXEL;
    if (checkIn(newTile))
        if (isDot[newTile.x][newTile.y])
            if (data[newTile.x][newTile.y] == POWER_DOT_DATA)
            {
                switch (powerDot[newTile.x][newTile.y])
                {
                    case DEFAULT_DOT:
                        return DEFAULT_DOT;
                        break;
                    case POWER_DOT:
                        return POWER_DOT;
                        break;
                    case SPEED_DOT:
                        return SPEED_DOT;
                        break;
                    case INVISIBLE_DOT:
                        return INVISIBLE_DOT;
                        break;
                    case TIME_FREE_DOT:
                        return TIME_FREE_DOT;
                        break;
                    default:
                        break;
                }
            }
    return -1;
}

void Labyrinth::removeDot(Point tile)
{
    isDot[tile.x][tile.y] = false;
    dotRemain--;
    return;
}

void Labyrinth::removeDot(Point screen, DIRECTION dir)
{
    Point newTile = (screen + DIRECTION_VALUE[dir]*PACMAN_SPEED/2) / RESOURCES_PIXEL;
    if (isDot[newTile.x][newTile.y])
        dotRemain--;
    isDot[newTile.x][newTile.y] = false;
    return;
}

///Ghost function:
Point Labyrinth::getGhostStart() const
{
    return ghost_start;
}

Point Labyrinth::getBlinkyStand() const
{
    return blinky_stand;
}

Point Labyrinth::getPinkyStand() const
{
    return pinky_stand;
}

Point Labyrinth::getInkyStand() const
{
    return inky_stand;
}

Point Labyrinth::getClydeStand() const
{
    return clyde_stand;
}

bool Labyrinth::ghostCanMove(Point tile, DIRECTION dir) const
{
    if (checkIn(tile + DIRECTION_VALUE[dir]))
        return (getData(tile + DIRECTION_VALUE[dir]) != WALL_DATA);
    if (checkIn(tile))
        return (getData(tile) != WALL_DATA);
    return false;
}

///Fruit function:
bool Labyrinth::fruitCanMove(Point tile, DIRECTION dir) const
{
    if (checkIn(tile + DIRECTION_VALUE[dir]))
        return (getData(tile + DIRECTION_VALUE[dir]) != WALL_DATA && getData(tile + DIRECTION_VALUE[dir]) != GHOST_HOUSE_DATA);
    if (checkIn(tile))
        return (getData(tile) != WALL_DATA && getData(tile) != GHOST_HOUSE_DATA);
    return false;
}

///Check point
bool Labyrinth::checkIn(Point tile) const
{
    return (!(tile.x == LABYRINTH_DATA_WIDTH || tile.y == LABYRINTH_DATA_HEIGHT || tile.x == -1 || tile.y == -1));
}

int Labyrinth::getData(Point tile) const
{
    return (data[tile.x][tile.y]);
}
