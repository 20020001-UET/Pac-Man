///Unique Ghost [Source]
#include "UniqueGhost.h"

///Include header
#include <iostream>

///Unique Ghost class
//Contructor:
UniqueGhost::UniqueGhost(UNIQUE_GHOST_TYPE _unique_ghost_type, Point _tile) : Entity()
{
    unique_ghost_type = _unique_ghost_type;

    switch (unique_ghost_type)
    {
        case UNIQUE_GHOST_DEADLY:
            type = OBJECT_DEADLY;
            break;
        case UNIQUE_GHOST_SPEEDY:
            type = OBJECT_SPEEDY;
            break;
        case UNIQUE_GHOST_INVISY:
            type = OBJECT_INVISY;
            break;
        case UNIQUE_GHOST_FREEZY:
            type = OBJECT_FREEZY;
            break;
        default:
            break;
    }

    tile = _tile;
    update();

    lastPoint.clear();

    return;
}

//Destructor:
UniqueGhost::~UniqueGhost()
{
    graphic = NULL;
    timer = NULL;

    lastPoint.clear();

    return;
}

///function:
//init:
void UniqueGhost::init(Graphic* _graphic, Timer* _timer,Point _show_up, Point _start_point, Point _stand, Point _scatter)
{
    graphic = _graphic;
    timer = _timer;
    sprite_val = frame = 0;
    frame_value = UNIQUE_GHOST_FRAME_VALUE;

    direction = UNSET_DIRECTION;
    show_up = _show_up;
    start_point = _start_point;
    stand = _stand;
    scatter = _scatter;

    setTile(stand);
    update();

    lastPoint.clear();

    return;
}

//loop:
void UniqueGhost::loop()
{
    handleBehavior();

    handleTunnel();

    return;
}

//render:
void UniqueGhost::handleRender()
{
    if (curBehavior.empty())
        return;

    UNIQUE_GHOST_BEHAVIOR cur_behavior = curBehavior.back();

    OBJECT_TYPE cur_type = type;

    switch (cur_behavior)
    {
        case UNIQUE_GHOST_INIT:
        case UNIQUE_GHOST_SHOW_UP:
        case UNIQUE_GHOST_STAND:
        case UNIQUE_GHOST_CHASE:
        case UNIQUE_GHOST_SCATTER:
        case UNIQUE_GHOST_BLIND:
        case UNIQUE_GHOST_FREEZING:
        case UNIQUE_GHOST_FRIGHTENED:
        {
            switch (getCurDirection())
            {
                case UP:
                    sprite_val = UNIQUE_GHOST_UP;
                    break;
                case RIGHT:
                    sprite_val = UNIQUE_GHOST_RIGHT;
                    break;
                case DOWN:
                    sprite_val = UNIQUE_GHOST_DOWN;
                    break;
                case LEFT:
                    sprite_val = UNIQUE_GHOST_LEFT;
                    break;
                default:
                    break;
            }

            if (getCurDirection() == UNSET_DIRECTION)
                sprite_val = 0;
            else
                sprite_val += frame / frame_value;

            ++frame;
            if (frame / frame_value >= GHOST_ANIMATION_FRAME)
                frame = 0;

            break;
        }
        case UNIQUE_GHOST_REBORN:
        case UNIQUE_GHOST_EATEN:
        {
            switch (getCurDirection())
            {
                case UP:
                    sprite_val = EATEN_GHOST_UP;
                    break;
                case RIGHT:
                    sprite_val = EATEN_GHOST_RIGHT;
                    break;
                case DOWN:
                    sprite_val = EATEN_GHOST_DOWN;
                    break;
                case LEFT:
                    sprite_val = EATEN_GHOST_LEFT;
                    break;
                default:
                    break;
            }

            cur_type = OBJECT_EATEN_GHOST;

            break;
        }
        default:
            break;
    }

    //Speed effect
    if (!lastPoint.empty() && !curMode[UNIQUE_GHOST_FREEZING_MODE])
    {
        int lastAlpha = graphic->getTextureAlpha(UNIQUE_GHOST);
        SDL_Rect lastDest = {0, 0, OBJECT_PIXEL, OBJECT_PIXEL};
        for (unsigned int index = 0; index < lastPoint.size(); index++)
        {
            lastDest.x = lastPoint[index].x;
            lastDest.y = lastPoint[index].y;
            graphic->setTextureAlpha(UNIQUE_GHOST, lastAlpha/(index+1));
            graphic->draw(cur_type, sprite_val, lastDest);
        }
        graphic->setTextureAlpha(UNIQUE_GHOST, lastAlpha);
    }

    if (curMode[UNIQUE_GHOST_SPEED_UP_MODE])
    {
        lastPoint.push_front(Point(dest.x, dest.y));
        if (lastPoint.size() > 10)
            lastPoint.pop_back();
    }
    else
    {
        lastPoint.push_front(Point(dest.x, dest.y));
        lastPoint.pop_back();
        if (lastPoint.size() > 0)
            lastPoint.pop_back();
    }
    graphic->setTextureAlpha(UNIQUE_GHOST, 0xFF);

    if (curMode[UNIQUE_GHOST_FRIGHTENED_MODE])
    {
        int tickLeft = UNIQUE_GHOST_MODE_TIME[UNIQUE_GHOST_FRIGHTENED_MODE] - (timer->getTicks() - startMode[UNIQUE_GHOST_FRIGHTENED_MODE]);
        sprite_val = FRIGHTENED_GHOST_DEFAULT;

        if (tickLeft <= 2000)
        {
            if ((tickLeft/200 % 2) != 0)
                sprite_val = FRIGHTENED_GHOST_WHITE;
        }

        sprite_val += frame / frame_value;

        ++frame;
        if (frame / frame_value >= FRIGHTENED_GHOST_ANIMATION_FRAME)
            frame = 0;

        cur_type = OBJECT_FRIGHTENED_GHOST;
    }

    if (curMode[UNIQUE_GHOST_FREEZING_MODE])
    {
        int tickLeft = UNIQUE_GHOST_MODE_TIME[UNIQUE_GHOST_FREEZING_MODE] - (timer->getTicks() - startMode[UNIQUE_GHOST_FREEZING_MODE]);
        graphic->setTextureAlpha(UNIQUE_GHOST, 0x7F);

        if (tickLeft <= 2000)
        {
            if ((tickLeft/200 % 2) != 0)
                graphic->setTextureAlpha(UNIQUE_GHOST, 0xFF);
        }
    }

    if (curMode[UNIQUE_GHOST_INVISIBLE_MODE])
    {
        int tickLeft = UNIQUE_GHOST_MODE_TIME[UNIQUE_GHOST_INVISIBLE_MODE] - (timer->getTicks() - startMode[UNIQUE_GHOST_INVISIBLE_MODE]);
        int tickPast = (timer->getTicks() - startMode[UNIQUE_GHOST_INVISIBLE_MODE]);
        int alpha_mode = 0;

        if (tickLeft <= 2000)
        {
            alpha_mode = 255.0f*(1 - tickLeft / 2000.0f);
        }
        if (tickPast <= 2000)
        {
            alpha_mode = 255.0f*(1 - tickPast / 2000.0f);
        }

        graphic->setTextureAlpha(UNIQUE_GHOST, alpha_mode);
    }

    graphic->draw(cur_type, sprite_val, dest);
    graphic->setTextureAlpha(UNIQUE_GHOST, 0xFF);

    return;
}

void UniqueGhost::render()
{
    if (!animated)
    {
        if (!(!curBehavior.empty() && curBehavior.back() == UNIQUE_GHOST_BEING_EATEN))
            graphic->draw(type, sprite_val, dest);
        return;
    }

    handleRender();
    return;
}

///behavior function:
//behavior:
void UniqueGhost::setBehavior(const UNIQUE_GHOST_BEHAVIOR newBehavior)
{
    if (newBehavior == UNIQUE_GHOST_SHOW_UP)
    {
        while (!curBehavior.empty())
        {
            curBehavior.pop();
            startBehavior.pop();
        }
        curBehavior.push(newBehavior);
        startBehavior.push(timer->getTicks());
        initBehavior();
        return;
    }

    if (!curBehavior.empty())
    {
        if (curBehavior.front() == UNIQUE_GHOST_STAND && newBehavior != UNIQUE_GHOST_SCATTER)
        {
            return;
        }
    }

    switch (newBehavior)
    {
        case UNIQUE_GHOST_INIT:
        case UNIQUE_GHOST_WAIT:
        {
            while (!curBehavior.empty())
            {
                curBehavior.pop();
                startBehavior.pop();
            }
            break;
        }
        case UNIQUE_GHOST_STAND:
            break;
        case UNIQUE_GHOST_CHASE:
            break;
        case UNIQUE_GHOST_SCATTER:
            break;
        case UNIQUE_GHOST_EATEN:
            break;
        case UNIQUE_GHOST_REBORN:
            break;
        case UNIQUE_GHOST_FRIGHTENED:
        {
            setMode(UNIQUE_GHOST_FRIGHTENED_MODE);
            break;
        }
        case UNIQUE_GHOST_BEING_EATEN:
        {
            while (!curBehavior.empty())
            {
                curBehavior.pop();
                startBehavior.pop();
            }

            setMode(UNIQUE_GHOST_NORMAL);
            break;
        }
        case UNIQUE_GHOST_FREEZING:
        {
            if (!curBehavior.empty())
            {
                if (curBehavior.front() == UNIQUE_GHOST_EATEN)
                    break;
                if (curBehavior.front() == UNIQUE_GHOST_FRIGHTENED)
                    break;
                if (curBehavior.front() == UNIQUE_GHOST_REBORN)
                    break;
            }

            while (!curBehavior.empty())
            {
                curBehavior.pop();
                startBehavior.pop();
            }

            setMode(UNIQUE_GHOST_FREEZING_MODE);
            break;
        }
        case UNIQUE_GHOST_BLIND:
        {
            setMode(UNIQUE_GHOST_BLIND_MODE);
            break;
        }
        default:
            break;
    }

    if (!curBehavior.empty())
    {
        if (curBehavior.front() == UNIQUE_GHOST_STAND && newBehavior == UNIQUE_GHOST_SCATTER)
        {
            outGhostHouse = true;
            leaveGhostHouse();
            curBehavior.pop();
            startBehavior.pop();
        }

        if (curBehavior.front() == UNIQUE_GHOST_EATEN)
        {
            return;
        }
    }

    curBehavior.push(newBehavior);
    startBehavior.push(timer->getTicks());
    if (curBehavior.size() == 1)
        initBehavior();
    return;
}

void UniqueGhost::initBehavior()
{
    if (curBehavior.empty())
        return;

    switch (curBehavior.front())
    {
        case UNIQUE_GHOST_INIT:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = UNIQUE_GHOST_SPEED;
            frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE;
            sprite_val = 0;

            //set UniqueGhost position:
            setTile(stand);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            outGhostHouse = false;

            setMode(UNIQUE_GHOST_NORMAL);

            lastPoint.clear();

            removeBehavior();

            break;
        }
        case UNIQUE_GHOST_WAIT:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = 0;frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE;
            sprite_val = 0;

            //set Ghost position:
            setTile(show_up);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            setMode(UNIQUE_GHOST_NORMAL);

            break;
        }
        case UNIQUE_GHOST_SHOW_UP:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            showed_up = false;
            speed = 0;

            //set Ghost position:
            setTile(show_up);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE/2;
            break;
        }
        case UNIQUE_GHOST_STAND:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = UNIQUE_GHOST_SPEED;
            frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE;
            sprite_val = 0;

            //set UniqueGhost position:
            setTile(stand);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            break;
        }
        case UNIQUE_GHOST_CHASE:
        case UNIQUE_GHOST_SCATTER:
        {
            animated = true;
            speed = UNIQUE_GHOST_SPEED;
            frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE;
            break;
        }
        case UNIQUE_GHOST_FRIGHTENED:
        {
            animated = true;
            direction.type = opposite(direction.type);
            speed = UNIQUE_GHOST_SPEED;
            frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE;
            break;
        }
        case UNIQUE_GHOST_BLIND:
        {
            animated = true;
            speed = UNIQUE_GHOST_SPEED;
            frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE;
            break;
        }
        case UNIQUE_GHOST_BEING_EATEN:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = 0;
            break;
        }
        case UNIQUE_GHOST_REBORN:
        {
            setTile(start_point);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            break;
        }
        case UNIQUE_GHOST_EATEN:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            setMode(UNIQUE_GHOST_NORMAL);
            speed = UNIQUE_GHOST_SPEED*4;
            setTile(tile);
            frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE/2;
            break;
        }
        case UNIQUE_GHOST_FREEZING:
        {
            animated = true;
            speed = 0;
            frame = 0;
            frame_value = UNIQUE_GHOST_FRAME_VALUE;
            break;
        }
        default:
            break;
    }
    return;
}

void UniqueGhost::handleBehavior()
{
    if (!curBehavior.empty())
    {
        if (curBehavior.back() == UNIQUE_GHOST_SHOW_UP)
        {
            int tickLeft = timer->getTicks() - startBehavior.front();
            if (tickLeft >= UNIQUE_GHOST_BEHAVIOR_TIME[curBehavior.front()])
            {
                showed_up = true;
                return;
            }
            return;
        }

        if (curBehavior.back() == UNIQUE_GHOST_FREEZING || curBehavior.back() == UNIQUE_GHOST_REBORN)
        {
            removeBehavior();
            return;
        }
        else
            if (curBehavior.front() == UNIQUE_GHOST_STAND || curBehavior.front() == UNIQUE_GHOST_WAIT)
            {
                return;
            }
    }


    if (getCurDirection() != UNSET_DIRECTION)
        move(direction.vel()*speed);

    removeBehavior();

    return;
}

void UniqueGhost::removeBehavior()
{
    if (curBehavior.empty())
        return;

    if (curBehavior.front() == UNIQUE_GHOST_STAND || curBehavior.front() == UNIQUE_GHOST_WAIT)
        return;

    if (curBehavior.front() == UNIQUE_GHOST_REBORN)
    {
        int tickLeft = timer->getTicks() - startBehavior.front();
        if (tickLeft >= UNIQUE_GHOST_BEHAVIOR_TIME[curBehavior.front()])
        {
            curBehavior.pop();
            startBehavior.pop();
            setBehavior(UNIQUE_GHOST_CHASE);
        }
    }

    if (curBehavior.size() == 2)
    {
        if (curBehavior.front() == UNIQUE_GHOST_FRIGHTENED && curBehavior.back() == UNIQUE_GHOST_FREEZING)
        {
            int tickLeft = timer->getTicks() - startBehavior.front();
            if (tickLeft >= UNIQUE_GHOST_BEHAVIOR_TIME[curBehavior.front()])
            {
                curBehavior.pop();
                startBehavior.pop();
            }
        }
    }

    if (!checkScreen() && curBehavior.front() != UNIQUE_GHOST_BEING_EATEN && curBehavior.front() != UNIQUE_GHOST_FREEZING && curBehavior.front() != UNIQUE_GHOST_INIT)
        return;

    if (curBehavior.back() == UNIQUE_GHOST_FRIGHTENED && curBehavior.size() > 1)
    {
        while (!curBehavior.empty())
        {
            if (curBehavior.front() == UNIQUE_GHOST_FRIGHTENED)
                break;
            curBehavior.pop();
            startBehavior.pop();
        }
    }

    if (curBehavior.front() == UNIQUE_GHOST_EATEN)
    {
        if (checkScreen() && tile == target)
        {
            curBehavior.pop();
            startBehavior.pop();
            setBehavior(UNIQUE_GHOST_REBORN);
        }
        return;
    }

    if (curBehavior.back() == UNIQUE_GHOST_BLIND && curBehavior.size() > 1)
    {
        if (checkScreen())
        {
            while (curBehavior.front() != UNIQUE_GHOST_BLIND)
            {
                curBehavior.pop();
                startBehavior.pop();
            }
        }
    }

    bool remove_flag = true;
    UNIQUE_GHOST_BEHAVIOR lastBehavior = UNIQUE_GHOST_UNSET;
    while (!curBehavior.empty() && remove_flag)
    {
        int tickLeft = timer->getTicks() - startBehavior.front();
        if (tickLeft >= UNIQUE_GHOST_BEHAVIOR_TIME[curBehavior.front()])
        {
            lastBehavior = curBehavior.front();
            curBehavior.pop();
            startBehavior.pop();
        }
        else
        {
            remove_flag = false;
        }
    }

    if (lastBehavior != UNIQUE_GHOST_UNSET)
    {
        switch (lastBehavior)
        {
            case UNIQUE_GHOST_INIT:
            {
                setBehavior(UNIQUE_GHOST_STAND);
                break;
            }
            case UNIQUE_GHOST_CHASE:
            {
                setBehavior(UNIQUE_GHOST_SCATTER);
                break;
            }
            case UNIQUE_GHOST_SCATTER:
            {
                setBehavior(UNIQUE_GHOST_CHASE);
                break;
            }
            case UNIQUE_GHOST_FRIGHTENED:
            {
                if (!curBehavior.empty())
                    if (curBehavior.front() == UNIQUE_GHOST_FREEZING)
                        break;
                setBehavior(UNIQUE_GHOST_CHASE);
                break;
            }
            case UNIQUE_GHOST_BEING_EATEN:
            {
                setBehavior(UNIQUE_GHOST_EATEN);
                break;
            }
            case UNIQUE_GHOST_EATEN:
            {

                break;
            }
            case UNIQUE_GHOST_FREEZING:
            {
                setBehavior(UNIQUE_GHOST_CHASE);
                break;
            }
            case UNIQUE_GHOST_BLIND:
            {
                setBehavior(UNIQUE_GHOST_CHASE);
                break;
            }
            default:
                break;
        }

        initBehavior();
    }

    return;
}

UNIQUE_GHOST_BEHAVIOR UniqueGhost::getBehavior()
{
    return (curBehavior.empty()) ? (UNIQUE_GHOST_UNSET) : (curBehavior.back());
}

///Mode function:
//Mode:
void UniqueGhost::setMode(const UNIQUE_GHOST_MODE newMode)
{
    curMode[newMode] = true;
    startMode[newMode] = timer->getTicks();
    initMode(newMode);
    return;
}

void UniqueGhost::initMode(const UNIQUE_GHOST_MODE mode)
{
    switch (mode)
    {
        case UNIQUE_GHOST_NORMAL:
        {
            removeMode(UNIQUE_GHOST_SPEED_UP_MODE);
            removeMode(UNIQUE_GHOST_SLOW_DOWN_MODE);
            removeMode(UNIQUE_GHOST_INVISIBLE_MODE);
            removeMode(UNIQUE_GHOST_FRIGHTENED_MODE);
            removeMode(UNIQUE_GHOST_BLIND_MODE);
            removeMode(UNIQUE_GHOST_FREEZING_MODE);
            break;
        }
        case UNIQUE_GHOST_SPEED_UP_MODE:
        {
            removeMode(UNIQUE_GHOST_SLOW_DOWN_MODE);
            if (checkScreen())
                speed = UNIQUE_GHOST_SPEED_SPEED_UP;
            break;
        }
        case UNIQUE_GHOST_SLOW_DOWN_MODE:
        {
            removeMode(UNIQUE_GHOST_SPEED_UP_MODE);
            if (checkScreen())
                speed = UNIQUE_GHOST_SPEED;;
            break;
        }
        case UNIQUE_GHOST_INVISIBLE_MODE:
            break;
        case UNIQUE_GHOST_FRIGHTENED_MODE:
            break;
        case UNIQUE_GHOST_BLIND_MODE:
            break;
        case UNIQUE_GHOST_FREEZING_MODE:
            break;
        default:
            break;
    }
    return;
}

void UniqueGhost::handleMode()
{
    if (getBehavior() == UNIQUE_GHOST_EATEN)
    {
        if (checkScreen())
            speed = UNIQUE_GHOST_SPEED*4;
    }
    else
    {
        if (checkScreen())
            speed = UNIQUE_GHOST_SPEED;
    }

    for (int index = UNIQUE_GHOST_NORMAL+1; index < UNIQUE_GHOST_MODE_TOTAL; index++)
        if (curMode[index])
        {
            int timePast = timer->getTicks() - startMode[index];
            if (timePast >= UNIQUE_GHOST_MODE_TIME[index])
                removeMode(index);
            else
            {
                if (index == UNIQUE_GHOST_SPEED_UP_MODE && getBehavior() != UNIQUE_GHOST_EATEN)
                {
                    if (timePast <= 1600)
                    {
                        if (checkScreen())
                            speed = UNIQUE_GHOST_SPEED_SPEED_UP;
                    }
                    else
                    {
                        if (checkScreen())
                            speed = UNIQUE_GHOST_SPEED;
                    }
                }
            }
        }

    if (curMode[UNIQUE_GHOST_SLOW_DOWN_MODE] && getBehavior() != UNIQUE_GHOST_EATEN)
    {
        if (checkScreen())
            speed = UNIQUE_GHOST_SPEED;
    }

    return;
}

void UniqueGhost::removeMode(const int mode)
{
    curMode[mode] = false;
    startMode[mode] = 0;

    return;
}

bool UniqueGhost::isGhostMode(const UNIQUE_GHOST_MODE checkMode)
{
    return curMode[checkMode];
}

//playing function:
DIRECTION UniqueGhost::getCurDirection()
{
    return direction.type;
}

void UniqueGhost::setDirection(const DIRECTION newDirection)
{
    direction = Direction(newDirection);
    return;
}

void UniqueGhost::setStop(bool _stop)
{
    stop = _stop;
    return;
}

bool UniqueGhost::isOutGhostHouse()
{
    return outGhostHouse;
}

bool UniqueGhost::isStop() const
{
    return stop;
}

void UniqueGhost::setTarget(Point newTarget)
{
    target = newTarget;
    return;
}

void UniqueGhost::leaveGhostHouse()
{
    setTile(start_point);
}

//get:
Point UniqueGhost::getTarget()
{
    return target;
}

Point UniqueGhost::getScatter()
{
    return scatter;
}

Point UniqueGhost::getStand()
{
    return stand;
}

Point UniqueGhost::getStartPoint()
{
    return start_point;
}

UNIQUE_GHOST_TYPE UniqueGhost::getType()
{
    return unique_ghost_type;
}

bool UniqueGhost::isShowedUp()
{
    return showed_up;
}
