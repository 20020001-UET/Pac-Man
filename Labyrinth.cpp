///Labyrinth [Source]
#include "Labyrinth.h"

#include <fstream>
#include <iomanip>
#include "Resources.h"
#include "Engine.h"
#include <iostream>

///Labyrinth class
Labyrinth::Labyrinth()
{
    console = new Console("Labyrinth");
    width = LABYRINTH_W;
    height = LABYRINTH_H;

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
        {
            data[row][col] = 0;
            isDot[row][col] = false;
        }
}

void Labyrinth::load(std::string file)
{
    std::ifstream input(file);
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            input >> data[row][col];
            if (data[row][col] > 0)
                isDot[row][col] = true;
        }
    }
    input.close();

    /*
    std::ofstream output(file);
    output << std::setfill(' ');
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            output << std::setw(3) << data[row][col];
        }
        output << '\n';
    }
    */
}

void Labyrinth::render()
{
    srcRect = {0, 0, Engine::getPixel()*width, Engine::getPixel()*height};
    destRect = {0, 0, Engine::getPixel()*width, Engine::getPixel()*height};
    Texture::draw(Resources::getTextureLabyrinth(), srcRect, destRect);

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            if (isDot[row][col])
            {
                if (data[row][col] == 1)
                    srcRect = Resources::getSprite(DOT, DOT_SPRITE_VAL::SMALL_DOT);
                else
                    if (data[row][col] == 2)
                        srcRect = Resources::getSprite(DOT, DOT_SPRITE_VAL::BIG_DOT);
                destRect = {col*Engine::getPixel(), row*Engine::getPixel(), Engine::getPixel(), Engine::getPixel()};
                Texture::draw(Resources::getTexture(DOT), srcRect, destRect);
            }
}

bool Labyrinth::canMove(Point point, DIRECTION dir)
{
    int vx = vel_x[dir], vy = vel_y[dir];
    if (point.y+vy == height || point.x+vx == width || point.y+vy == -1 || point.x+vx == -1)
        return (data[point.y][point.x] != 0);
    return (data[point.y+vy][point.x+vx] != 0);
}

bool Labyrinth::intersection(Point point)
{
    int cnt = 0, hcnt = 0, vcnt = 0;
    for (int id = 0; id < 4; id++)
    if (!(point.y+vel_y[id] == height || point.x+vel_x[id] == width || point.y+vel_y[id] == -1 || point.x+vel_x[id] == -1))
        if (data[point.y+vel_y[id]][point.x+vel_x[id]] != 0)
        {
            cnt++;
            hcnt += vel_y[id];
            vcnt += vel_x[id];
        }
    return ( ((cnt == 2) && (hcnt != 0) && (vcnt != 0)) || (cnt > 2) );
}

bool Labyrinth::isDotHere(Point point)
{
    return isDot[point.y][point.x];
}

bool Labyrinth::isPowerUpHere(Point point)
{
    return (data[point.y][point.x] == 2);
}

void Labyrinth::removeDot(Point point)
{
    isDot[point.y][point.x] = false;
}
