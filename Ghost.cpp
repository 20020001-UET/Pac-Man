///Ghost [Source]
#include "Ghost.h"

#include "Labyrinth.h"
#include "Texture.h"
#include <iostream>
#include <random>

///Ghost class
Ghost::Ghost(int x, int y, int w, int h, GHOST_TYPE _type) : Entity(x, y, w, h)
{
    type = _type;
    cur_dir = DEFAULT;
    setBehavior(SCATTER);
    waitTime = 0;
    frame = 0;
    sprite_frame = 0;
    stop = true;
}

void Ghost::loop()
{
    if (state_time == 0)
    {
        if (cur_behavior == CHASE)
            setBehavior(SCATTER);

        if (cur_behavior == SCATTER)
            setBehavior(CHASE);

        if (cur_behavior == FRIGHTENED)
            setBehavior(CHASE);
    }

    if (waitTime != 0)
    {
        waitTime--;
        return;
    }

    float speed = GHOST_SPEED;
    if (cur_behavior == EATEN)
        speed = 6.25f;

    switch (cur_dir)
    {
        case UP:
            move(0, -speed);
            break;
        case DOWN:
            move(0, speed);
            break;
        case LEFT:
            move(-speed, 0);
            break;
        case RIGHT:
            move(speed, 0);
            break;
        case DEFAULT:
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

    if (cur_behavior != EATEN)
        state_time--;
    else
        if (Point::checkEqual(tile, target))
            setBehavior(CHASE);

    return;
}

void Ghost::render()
{
    //Default:
    switch (cur_dir)
    {
        case UP:
            sprite_frame = GHOST_UP;
            break;

        case DOWN:
            sprite_frame = GHOST_DOWN;
            break;

        case LEFT:
            sprite_frame = GHOST_LEFT;
            break;

        case RIGHT:
            sprite_frame = GHOST_RIGHT;
            break;

        default:
            sprite_frame = GHOST_DEFAUT;
            break;
    }

    sprite_frame += frame / GHOST_FRAME_VALUE;

    OBJECT_VAL object_val;

    switch (type)
    {
        case BLINKY:
            object_val = BLINKY_SPIRTE;
            break;
        case PINKY:
            object_val = PINKY_SPRITE;
            break;
        case INKY:
            object_val = INKY_SPRITE;
            break;
        case CLYDE:
            object_val = CLYDE_SPRITE;
            break;
    }

    if (cur_behavior == FRIGHTENED)
    {
        object_val = OBJECT_VAL::FRIGHTENED_GHOST;
        sprite_frame = 0 + frame / GHOST_FRAME_VALUE;
    }

    if (cur_behavior == EATEN)
    {
        object_val = OBJECT_VAL::EATEN_GHOST;
        switch (cur_dir)
        {
            case UP: sprite_frame = 0; break;
            case DOWN: sprite_frame = 1; break;
            case LEFT: sprite_frame = 2; break;
            case RIGHT: sprite_frame = 3; break;
            case DEFAULT: break;
        }
    }

    srcRect = Resources::getSprite(object_val,
                                   sprite_frame);

    Texture::draw(Resources::getTexture(object_val),
                  srcRect, destRect);

    ++frame;

    if (frame / GHOST_FRAME_VALUE >= GHOST_ANIMATION_FRAME)
    {
        frame = 0;
    }
}

void Ghost::setBehavior(BEHAVIOR behavior)
{
    cur_behavior = behavior;
    switch (cur_behavior)
    {
        case CHASE:
            state_time = 4000;
            break;
        case SCATTER:
            state_time = 250;
            break;
        case FRIGHTENED:
            state_time = 1000;
            break;
        case EATEN:
            if (tile.x < LABYRINTH_W/2)
                setTarget(Point(13, 11));
            else
                setTarget(Point(14, 11));
            teleport(tile.x, tile.y);
            state_time = 0;
            break;
    }
}

BEHAVIOR Ghost::getBehavior()
{
    return cur_behavior;
}

void Ghost::setTarget(Point _target)
{
    target = _target;
}

Point Ghost::getTarget()
{
    return target;
}

void Ghost::setMoving(DIRECTION dir)
{
    cur_dir = dir;
}

DIRECTION Ghost::getDir()
{
    return cur_dir;
}

void Ghost::setStop(bool _stop)
{
    stop = _stop;
}

bool Ghost::isStop()
{
    return stop;
}
