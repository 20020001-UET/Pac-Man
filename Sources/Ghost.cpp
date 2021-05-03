///Ghost [Source]
#include "Ghost.h"

///Include header
#include <iostream>

///Ghost class
//Contructor:
Ghost::Ghost(GHOST_TYPE _ghost_type, Point _tile) : Entity()
{
    console = new Console("Ghost");

    ghost_type = _ghost_type;

    switch (ghost_type)
    {
        case GHOST_BLINKY:
            type = OBJECT_BLINKY;
            break;
        case GHOST_PINKY:
            type = OBJECT_PINKY;
            break;
        case GHOST_INKY:
            type = OBJECT_INKY;
            break;
        case GHOST_CLYDE:
            type = OBJECT_CLYDE;
            break;
        default:
            break;
    }

    tile = _tile;
    update();

    return;
}

//Destructor:
Ghost::~Ghost()
{
    delete console;
    console = NULL;
    graphic = NULL;
    timer = NULL;
    return;
}

///function:
//init:
void Ghost::init(Graphic* _graphic, Timer* _timer, Point _start_point, Point _stand, Point _scatter, Point _upgrade)
{
    graphic = _graphic;
    timer = _timer;
    sprite_val = frame = 0;
    frame_value = GHOST_FRAME_VALUE;

    direction = UNSET_DIRECTION;
    start_point = _start_point;
    stand = _stand;
    scatter = _scatter;
    upgrade = _upgrade;

    upgraded = false;

    setTile(stand);
    update();

    return;
}

//loop:
void Ghost::loop()
{
    handleBehavior();

    handleTunnel();

    return;
}

//render:
void Ghost::handleRender()
{
    if (curBehavior.empty())
        return;

    GHOST_BEHAVIOR cur_behavior = curBehavior.back();

    OBJECT_TYPE cur_type = type;

    if (cur_behavior == GHOST_UPGRADE_UNIQUE)
    {
        int tickPast = GHOST_BEHAVIOR_TIME[cur_behavior] - (timer->getTicks() - startBehavior.front());
        sprite_val = 0;
        if (tickPast <= 2000)
        {
            if ((tickPast/200) % 2 == 0)
                sprite_val = 1;
            else
                sprite_val = 2;
        }
        sprite_val += GHOST_UPGRADE;
        graphic->draw(type, sprite_val, dest);
        return;
    }

    switch (cur_behavior)
    {
        case GHOST_INIT:
        case GHOST_STAND:
        case GHOST_CHASE:
        case GHOST_SCATTER:
        case GHOST_BLIND:
        case GHOST_FREEZING:
        {
            switch (getCurDirection())
            {
                case UP:
                    sprite_val = GHOST_UP;
                    break;
                case RIGHT:
                    sprite_val = GHOST_RIGHT;
                    break;
                case DOWN:
                    sprite_val = GHOST_DOWN;
                    break;
                case LEFT:
                    sprite_val = GHOST_LEFT;
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
        case GHOST_REBORN:
        case GHOST_EATEN:
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

    if (curMode[GHOST_FRIGHTENED_MODE])
    {
        int tickLeft = GHOST_MODE_TIME[GHOST_FRIGHTENED_MODE] - (timer->getTicks() - startMode[GHOST_FRIGHTENED_MODE]);
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

    if (curMode[GHOST_FREEZING_MODE])
    {
        int tickLeft = GHOST_MODE_TIME[GHOST_FREEZING_MODE] - (timer->getTicks() - startMode[GHOST_FREEZING_MODE]);
        graphic->setTextureAlpha(OBJECT, 0x7F);

        if (tickLeft <= 2000)
        {
            graphic->setTextureAlpha(OBJECT, 0x7F);
            if ((tickLeft/200 % 2) != 0)
                graphic->setTextureAlpha(OBJECT, 0xFF);
        }
    }

    graphic->draw(cur_type, sprite_val, dest);
    graphic->setTextureAlpha(OBJECT, 0xFF);

    return;
}

void Ghost::render()
{
    if (!animated)
    {
        if (!(!curBehavior.empty() && curBehavior.back() == GHOST_BEING_EATEN))
            graphic->draw(type, sprite_val, dest);
        return;
    }

    handleRender();
    return;
}

///behavior function:
//behavior:
void Ghost::setBehavior(const GHOST_BEHAVIOR newBehavior)
{
    if (newBehavior == GHOST_UPGRADE_UNIQUE)
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
        if (curBehavior.front() == GHOST_STAND && newBehavior != GHOST_SCATTER)
        {
            return;
        }
    }

    switch (newBehavior)
    {
        case GHOST_INIT:
        {
            while (!curBehavior.empty())
            {
                curBehavior.pop();
                startBehavior.pop();
            }
            break;
        }
        case GHOST_STAND:
            break;
        case GHOST_CHASE:
            break;
        case GHOST_SCATTER:
            break;
        case GHOST_EATEN:
            break;
        case GHOST_REBORN:
            break;
        case GHOST_FRIGHTENED:
        {
            setMode(GHOST_FRIGHTENED_MODE);
            break;
        }
        case GHOST_BEING_EATEN:
        {
            while (!curBehavior.empty())
            {
                curBehavior.pop();
                startBehavior.pop();
            }

            setMode(GHOST_NORMAL);
            break;
        }
        case GHOST_FREEZING:
        {
            if (!curBehavior.empty())
            {
                if (curBehavior.front() == GHOST_EATEN)
                    break;
                if (curBehavior.front() == GHOST_FRIGHTENED)
                    break;
                if (curBehavior.front() == GHOST_REBORN)
                    break;
            }

            while (!curBehavior.empty())
            {
                curBehavior.pop();
                startBehavior.pop();
            }

            setMode(GHOST_FREEZING_MODE);
            break;
        }
        case GHOST_BLIND:
        {
            setMode(GHOST_BLIND_MODE);
            break;
        }
        default:
            break;
    }

    if (!curBehavior.empty())
    {
        if (curBehavior.front() == GHOST_STAND && newBehavior == GHOST_SCATTER)
        {
            outGhostHouse = true;
            leaveGhostHouse();
            curBehavior.pop();
            startBehavior.pop();
        }

        if (curBehavior.front() == GHOST_EATEN)
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

void Ghost::initBehavior()
{
    if (curBehavior.empty())
        return;

    switch (curBehavior.front())
    {
        case GHOST_INIT:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = GHOST_SPEED;
            frame = 0;
            frame_value = GHOST_FRAME_VALUE;
            sprite_val = 0;

            //set Ghost position:
            setTile(stand);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            outGhostHouse = false;

            setMode(GHOST_NORMAL);

            removeBehavior();

            break;
        }
        case GHOST_STAND:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = GHOST_SPEED;
            frame = 0;
            frame_value = GHOST_FRAME_VALUE;
            sprite_val = 0;

            //set Ghost position:
            setTile(stand);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            break;
        }
        case GHOST_CHASE:
        case GHOST_SCATTER:
        {
            animated = true;
            speed = GHOST_SPEED;
            frame = 0;
            frame_value = GHOST_FRAME_VALUE;
            break;
        }
        case GHOST_FRIGHTENED:
        {
            animated = true;
            direction.type = opposite(direction.type);
            speed = GHOST_SPEED;
            frame = 0;
            frame_value = GHOST_FRAME_VALUE;
            break;
        }
        case GHOST_BLIND:
        {
            animated = true;
            speed = GHOST_SPEED;
            frame = 0;
            frame_value = GHOST_FRAME_VALUE;
            break;
        }
        case GHOST_BEING_EATEN:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = 0;
            break;
        }
        case GHOST_REBORN:
        {
            setTile(start_point);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            break;
        }
        case GHOST_EATEN:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = GHOST_SPEED*4;
            setTile(tile);
            frame = 0;
            frame_value = GHOST_FRAME_VALUE/2;
            break;
        }
        case GHOST_FREEZING:
        {
            animated = true;
            speed = 0;
            frame = 0;
            frame_value = GHOST_FRAME_VALUE;
            break;
        }
        case GHOST_UPGRADE_UNIQUE:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            upgraded = false;
            speed = 0;

            //set Ghost position:
            setTile(upgrade);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            frame = 0;
            frame_value = GHOST_FRAME_VALUE/2;
            break;
        }
        default:
            break;
    }
    return;
}

void Ghost::handleBehavior()
{
    if (!curBehavior.empty())
    {
        if (curBehavior.back() == GHOST_UPGRADE_UNIQUE)
        {
            int tickLeft = timer->getTicks() - startBehavior.front();
            if (tickLeft >= GHOST_BEHAVIOR_TIME[curBehavior.front()])
            {
                upgraded = true;
                return;
            }
            return;
        }

        if (curBehavior.back() == GHOST_FREEZING || curBehavior.back() == GHOST_REBORN)
        {
            removeBehavior();
            return;
        }
        else
            if (curBehavior.front() == GHOST_STAND)
            {
                return;
            }
    }

    if (getCurDirection() != UNSET_DIRECTION)
        move(direction.vel()*speed);

    removeBehavior();

    return;
}

void Ghost::removeBehavior()
{
    if (curBehavior.empty())
        return;

    if (curBehavior.front() == GHOST_STAND)
        return;

    if (curBehavior.front() == GHOST_REBORN)
    {
        int tickLeft = timer->getTicks() - startBehavior.front();
        if (tickLeft >= GHOST_BEHAVIOR_TIME[curBehavior.front()])
        {
            curBehavior.pop();
            startBehavior.pop();
            setBehavior(GHOST_CHASE);
        }
    }

    if (curBehavior.size() == 2)
    {
        if (curBehavior.front() == GHOST_FRIGHTENED && curBehavior.back() == GHOST_FREEZING)
        {
            int tickLeft = timer->getTicks() - startBehavior.front();
            if (tickLeft >= GHOST_BEHAVIOR_TIME[curBehavior.front()])
            {
                curBehavior.pop();
                startBehavior.pop();
            }
        }
    }

    if (!checkScreen() && curBehavior.front() != GHOST_BEING_EATEN && curBehavior.front() != GHOST_FREEZING && curBehavior.front() != GHOST_INIT)
        return;

    if (curBehavior.back() == GHOST_FRIGHTENED && curBehavior.size() > 1)
    {
        while (!curBehavior.empty())
        {
            if (curBehavior.front() == GHOST_FRIGHTENED)
                break;
            curBehavior.pop();
            startBehavior.pop();
        }
    }

    if (curBehavior.front() == GHOST_EATEN)
    {
        if (checkScreen() && tile == target)
        {
            curBehavior.pop();
            startBehavior.pop();
            setBehavior(GHOST_REBORN);
        }
        return;
    }

    if (curBehavior.back() == GHOST_BLIND && curBehavior.size() > 1)
    {
        if (checkScreen())
        {
            while (curBehavior.front() != GHOST_BLIND)
            {
                curBehavior.pop();
                startBehavior.pop();
            }
        }
    }

    bool remove_flag = true;
    GHOST_BEHAVIOR lastBehavior = GHOST_UNSET;
    while (!curBehavior.empty() && remove_flag)
    {
        int tickLeft = timer->getTicks() - startBehavior.front();
        if (tickLeft >= GHOST_BEHAVIOR_TIME[curBehavior.front()])
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

    if (lastBehavior != GHOST_UNSET)
    {
        switch (lastBehavior)
        {
            case GHOST_INIT:
            {
                setBehavior(GHOST_STAND);
                break;
            }
            case GHOST_CHASE:
            {
                setBehavior(GHOST_SCATTER);
                break;
            }
            case GHOST_SCATTER:
            {
                setBehavior(GHOST_CHASE);
                break;
            }
            case GHOST_FRIGHTENED:
            {
                if (!curBehavior.empty())
                    if (curBehavior.front() == GHOST_FREEZING)
                        break;
                setBehavior(GHOST_CHASE);
                break;
            }
            case GHOST_BEING_EATEN:
            {
                setBehavior(GHOST_EATEN);
                break;
            }
            case GHOST_EATEN:
            {
                break;
            }
            case GHOST_FREEZING:
            {
                setBehavior(GHOST_CHASE);
                break;
            }
            case GHOST_BLIND:
            {
                setBehavior(GHOST_CHASE);
                break;
            }
            default:
                break;
        }

        initBehavior();
    }

    return;
}

GHOST_BEHAVIOR Ghost::getBehavior()
{
    return (curBehavior.empty()) ? (GHOST_UNSET) : (curBehavior.back());
}

///Mode function:
//Mode:
void Ghost::setMode(const GHOST_MODE newMode)
{
    curMode[newMode] = true;
    startMode[newMode] = timer->getTicks();
    initMode(newMode);
    return;
}

void Ghost::initMode(const GHOST_MODE mode)
{
    switch (mode)
    {
        case GHOST_NORMAL:
        {
            removeMode(GHOST_FRIGHTENED_MODE);
            removeMode(GHOST_BLIND_MODE);
            removeMode(GHOST_FREEZING_MODE);
            break;
        }
        case GHOST_FRIGHTENED_MODE:
        case GHOST_BLIND_MODE:
        case GHOST_FREEZING_MODE:
            break;
        default:
            break;
    }
    return;
}

void Ghost::handleMode()
{
    for (int index = GHOST_FRIGHTENED_MODE; index < GHOST_MODE_TOTAL; index++)
        if (curMode[index])
        {
            int timePast = timer->getTicks() - startMode[index];
            if (timePast >= GHOST_MODE_TIME[index])
                removeMode(index);
        }
}

void Ghost::removeMode(const int mode)
{
    curMode[mode] = false;
    startMode[mode] = 0;
    return;
}

bool Ghost::isGhostMode(const GHOST_MODE checkMode)
{
    return curMode[checkMode];
}

//playing function:
DIRECTION Ghost::getCurDirection()
{
    return direction.type;
}

void Ghost::setDirection(const DIRECTION newDirection)
{
    direction = Direction(newDirection);
    return;
}

void Ghost::setStop(bool _stop)
{
    stop = _stop;
    return;
}

bool Ghost::isOutGhostHouse()
{
    return outGhostHouse;
}

bool Ghost::isStop() const
{
    return stop;
}

void Ghost::setTarget(Point newTarget)
{
    target = newTarget;
    return;
}

void Ghost::leaveGhostHouse()
{
    setTile(start_point);
}

//get:
Point Ghost::getTarget()
{
    return target;
}

Point Ghost::getScatter()
{
    return scatter;
}

Point Ghost::getStand()
{
    return stand;
}

Point Ghost::getStartPoint()
{
    return start_point;
}

Point Ghost::getUpgrade()
{
    return upgrade;
}

GHOST_TYPE Ghost::getType()
{
    return ghost_type;
}

bool Ghost::isUpgraded()
{
    return upgraded;
}
