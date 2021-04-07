///Pacman [Source]
#include "Pacman.h"

///Project headers
#include "Resources.h"
#include "Texture.h"
#include "Labyrinth.h"
#include "Engine.h"
#include <iostream>

///Pacman class
Pacman::Pacman(int x, int y, int w, int h) : Entity(x, y, w, h)
{
    setScreenCenter(x, y);
    stand = true;
    frame = 0;
    sprite_frame = 0;
    dotCount = 0;
    life = PACMAN_LIFE;
    alive = true;
}

void Pacman::loop()
{
    if (cur_dir.empty())
        return;

    if (stand)
    {
        move(0, 0);
        stand = false;
    }

    if (waitTime != 0)
    {
        waitTime = 0;
        return;
    }

    switch (cur_dir.front())
    {
        case UP:
            move(0, -PACMAN_SPEED);
            break;

        case DOWN:
            move(0, PACMAN_SPEED);
            break;

        case LEFT:
            move(-PACMAN_SPEED, 0);
            break;

        case RIGHT:
            move(PACMAN_SPEED, 0);
            break;

        default:
            break;
    }

    if (tile.x == LABYRINTH_W)
        teleport(0, tile.y);
    if (tile.x < 0)
        teleport(LABYRINTH_W-1, tile.y);

    if (tile.y == LABYRINTH_H)
        teleport(tile.x, 0);
    if (tile.y < 0)
        teleport(tile.x, LABYRINTH_H-1);

    waitTime = 0;
}

void Pacman::render()
{
    if (!cur_dir.empty())
    {
        switch (cur_dir.front())
        {
            case UP:
                sprite_frame = PACMAN_UP;
                break;

            case DOWN:
                sprite_frame = PACMAN_DOWN;
                break;

            case LEFT:
                sprite_frame = PACMAN_LEFT;
                break;

            case RIGHT:
                sprite_frame = PACMAN_RIGHT;
                break;

            default:
                break;
        }

        sprite_frame += frame / FRAME_VALUE;
    }
    else
    {
        sprite_frame = 0;
    }

    srcRect = Resources::getSprite(OBJECT_VAL::PACMAN_SPRITE,
                                   sprite_frame);

    Texture::draw(Resources::getTexture(PACMAN_SPRITE),
                  srcRect, destRect);

    ++frame;

    if (frame / FRAME_VALUE >= PACMAN_ANIMATION_FRAME)
    {
        frame = 0;
    }
}

void Pacman::stop()
{
    if (cur_dir.size() > 1)
    {
        if (stand && (cur_dir.front() == UP || cur_dir.front() == DOWN))
        {
            cur_dir.pop();
            return;
        }

        if (checkScreen())
        {
            cur_dir.pop();
            return;
        }
    }
}

void Pacman::setDir(DIRECTION dir)
{
    if (!cur_dir.empty())
    {
        if (checkOppositeDir(dir, cur_dir.front()))
        {
            while (!cur_dir.empty())
                cur_dir.pop();
        }
    }

    if (cur_dir.size() < 2)
    {
        cur_dir.push(dir);
    }
}

void Pacman::eatDot()
{
    dotCount++;
}

int Pacman::getDot()
{
    return dotCount;
}

DIRECTION Pacman::getDir()
{
    if (cur_dir.empty())
        return DEFAULT;
    return cur_dir.front();
}

void Pacman::dead()
{
    alive = false;
    life--;
}

void Pacman::keepAlive()
{
    alive = true;
    while (!cur_dir.empty())
        cur_dir.pop();
    setScreenCenter(14, 22);
    stand = true;
    frame = 0;
    sprite_frame = 0;
}

bool Pacman::isAlive()
{
    return alive;
}

bool Pacman::isDead()
{
    return life <= 0;
}
