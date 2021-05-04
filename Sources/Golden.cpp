///Golden [Source]
#include "Golden.h"

///Golden class
//Constructor:
Golden::Golden(Point _tile) : Entity(_tile, OBJECT_GOLDEN)
{
    lastPoint.clear();
    return;
}

//Destructor:
Golden::~Golden()
{
    graphic = NULL;
    timer = NULL;
    lastPoint.clear();
    return;
}

///function:
//init:
void Golden::init(Graphic* _graphic, Timer* _timer, Point _start_point, Point _show_up)
{
    graphic = _graphic;
    timer = _timer;
    sprite_val = frame = 0;
    frame_value = GOLDEN_FRAME_VALUE;

    direction = UNSET_DIRECTION;
    start_point = _start_point;
    show_up = _show_up;

    danger = false;

    setTile(start_point);
    update();

    return;
}

//loop:
void Golden::loop()
{
    handleState();

    handleTunnel();

    return;
}

//render:
void Golden::handleRender()
{
    //Handle type
    type = OBJECT_GOLDEN;
    if (curState.type == GOLDEN_DEATH_STATE)
        type = OBJECT_GOLDEN_DEATH;

    //Animation
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

    if (curState.type == GOLDEN_DEATH_STATE)
    {
        sprite_val = frame / frame_value;
        ++frame;
        if (frame / frame_value >= UNIQUE_GHOST_GOLDEN_DEATH_ANIMATION_FRAME )
        {
            dead = true;
            frame = 0;
        }

        return;
    }
    else
    {
        ++frame;
        if (frame / frame_value >= UNIQUE_ANIMATION_FRAME)
            frame = 0;
    }

    //Speed effect
    if (!lastPoint.empty() && !curMode[GOLDEN_EXHAUSTED_MODE])
    {
        int lastAlpha = graphic->getTextureAlpha(UNIQUE_GHOST);
        SDL_Rect lastDest = {0, 0, OBJECT_PIXEL, OBJECT_PIXEL};
        for (unsigned int index = 0; index < lastPoint.size(); index++)
        {
            lastDest.x = lastPoint[index].x;
            lastDest.y = lastPoint[index].y;
            graphic->setTextureAlpha(UNIQUE_GHOST, lastAlpha/(index+1));
            graphic->draw(type, sprite_val, lastDest);
        }
        graphic->setTextureAlpha(UNIQUE_GHOST, lastAlpha);
    }

    if (curMode[GOLDEN_SPEED_UP_MODE])
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

    //Invisible effect
    if (curMode[GOLDEN_INVISIBLE_MODE])
    {
        int tickLeft = GOLDEN_MODE_TIME[GOLDEN_INVISIBLE_MODE] - (timer->getTicks() - startMode[GOLDEN_INVISIBLE_MODE]);
        int tickPast = (timer->getTicks() - startMode[GOLDEN_INVISIBLE_MODE]);
        int alpha_mode = 0;

        if (tickLeft <= 1600)
        {
            alpha_mode = 255.0f*(1 - tickLeft / 2000.0f);
        }
        if (tickPast <= 1600)
        {
            alpha_mode = 255.0f*(1 - tickPast / 2000.0f);
        }

        graphic->setTextureAlpha(UNIQUE_GHOST, alpha_mode);
    }

    //Exhauted effect
    if (curMode[GOLDEN_EXHAUSTED_MODE])
    {
        int tickLeft = GOLDEN_MODE_TIME[GOLDEN_INVISIBLE_MODE] - (timer->getTicks() - startMode[GOLDEN_INVISIBLE_MODE]);
        if ((tickLeft/400) % 2 == 1)
            type = OBJECT_GOLDEN_EXHAUTED_DEFAULT;
        else
            type = OBJECT_GOLDEN_EXHAUTED_YELLOW;

        if ((tickLeft/200) % 2 == 1)
            graphic->setTextureAlpha(UNIQUE_GHOST, 0xFF);
        else
            graphic->setTextureAlpha(UNIQUE_GHOST, 0x7F);
    }

    return;
}

void Golden::render()
{
    if (!showed_up)
        return;

    if (animated)
    {
        handleRender();
    }

    if (!dead)
        graphic->draw(type, sprite_val, dest);

    type = OBJECT_GOLDEN;
    graphic->setTextureAlpha(UNIQUE_GHOST, 0xFF);

    return;
}

///state:
void Golden::setState(const GOLDEN_STATE_TYPE newState)
{
    curState = GOLDEN_STATE(newState, timer->getTicks());
    if (!curState.isInit)
        initState(curState.type);
    return;
}

void Golden::initState(const GOLDEN_STATE_TYPE state)
{
    switch (state)
    {
        case GOLDEN_INIT_STATE:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = GOLDEN_SPEED;
            sprite_val = frame = 0;
            frame_value = GOLDEN_FRAME_VALUE;

            setMode(GOLDEN_NORMAL_MODE);

            showed_up = false;

            dead = false;
            health_point = GOLDEN_HP;
            soul_remain = SOUL_TOTAL;
            for (int i = 0; i < soul_remain; i++)
                soul[i] = true;

            speed_up_time = 0;
            break;
        }
        case GOLDEN_SHOW_UP_STATE:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = 0;
            sprite_val = frame = 0;
            frame_value = GOLDEN_FRAME_VALUE;

            showed_up = true;

            setTile(show_up);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            dead = false;
            break;
        }
        case GOLDEN_RUNNING_STATE:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = GOLDEN_SPEED;
            sprite_val = frame = 0;
            frame_value = GOLDEN_FRAME_VALUE;

            dead = false;
            break;
        }
        case GOLDEN_DEATH_STATE:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = 0;
            sprite_val = frame = 0;

            setMode(GOLDEN_NORMAL_MODE);

            frame_value = GOLDEN_DEATH_FRAME_VALUE;

            dead = false;
            break;
        }
        default:
            break;
    }
    return;
}

void Golden::handleState()
{
    switch (curState.type)
    {
        case GOLDEN_INIT_STATE:
            return;
        case GOLDEN_SHOW_UP_STATE:
        {
            break;
        }
        case GOLDEN_RUNNING_STATE:
        {
            if (getCurDirection() != UNSET_DIRECTION)
                move(direction.vel()*speed);
            break;
        }
        case GOLDEN_DEATH_STATE:
        {
            if (dead)
                setState(GOLDEN_INIT_STATE);
            break;
        }
        default:
            break;
    }
    return;
}

void Golden::removeState(const GOLDEN_STATE_TYPE state)
{
    return;
}

GOLDEN_STATE_TYPE Golden::getState()
{
    return curState.type;
}

///Mode
void Golden::setMode(const GOLDEN_MODE_TYPE newMode)
{
    curMode[newMode] = true;
    startMode[newMode] = timer->getTicks();
    initMode(newMode);
    return;
}

void Golden::initMode(const GOLDEN_MODE_TYPE mode)
{
    switch (mode)
    {
        case GOLDEN_NORMAL_MODE:
        {
            removeMode(GOLDEN_SPEED_UP_MODE);
            removeMode(GOLDEN_INVISIBLE_MODE);
            removeMode(GOLDEN_EXHAUSTED_MODE);

            frame_value = GOLDEN_FRAME_VALUE;

            speed_up_time = 0;
            break;
        }
        case GOLDEN_SPEED_UP_MODE:
        {
            frame_value = GOLDEN_SPEED_UP_FRAME_VALUE;
            speed_up_time++;
            break;
        }
        case GOLDEN_INVISIBLE_MODE:
        {
            break;
        }
        case GOLDEN_EXHAUSTED_MODE:
        {
            removeMode(GOLDEN_SPEED_UP_MODE);
            removeMode(GOLDEN_INVISIBLE_MODE);
            frame_value = GOLDEN_EXHAUSTED_FRAME_VALUE;
            speed_up_time = 0;
            break;
        }
        default:
            break;
    }
    return;
}

void Golden::handleMode()
{
    for (int index = GOLDEN_NORMAL_MODE+1; index < GOLDEN_MODE_TOTAL; index++)
        if (curMode[index])
        {
            int timePast = timer->getTicks() - startMode[index];
            if (timePast >= GOLDEN_MODE_TIME[index])
            {
                removeMode(index);
                if (index == GOLDEN_SPEED_UP_MODE)
                {
                    if (speed_up_time == 5)
                        setMode(GOLDEN_EXHAUSTED_MODE);
                }
            }
        }

    if (checkScreen())
    {
        if (curMode[GOLDEN_SPEED_UP_MODE])
            speed = GOLDEN_SPEED_UP_SPEED;
        else
            if (curMode[GOLDEN_EXHAUSTED_MODE])
                speed = GOLDEN_EXHAUSTED_SPEED;
            else
                speed = GOLDEN_SPEED;
    }

    return;
}

void Golden::removeMode(const int mode)
{
    curMode[mode] = false;
    startMode[mode] = 0;

    return;
}

bool Golden::isGoldenMode(const GOLDEN_MODE_TYPE checkMode)
{
    return curMode[checkMode];
}

//playing function:
DIRECTION Golden::getCurDirection()
{
    return direction.type;
}

void Golden::setDirection(const DIRECTION newDirection)
{
    direction = Direction(newDirection);
    return;
}

void Golden::setStop(bool _stop)
{
    stop = _stop;
    return;
}

bool Golden::isStop()
{
    return stop;
}

void Golden::setTarget(Point newTarget)
{
    target = newTarget;
    return;
}

Point Golden::getTarget()
{
    return target;
}

void Golden::setDanger(bool _danger)
{
    danger = _danger;
    return;
}

bool Golden::isDanger()
{
    return danger;
}

bool Golden::isShowedUp()
{
    return showed_up;
}

bool Golden::isDead()
{
    return dead;
}

int Golden::dotGenerate()
{
    Uint32 dot = rand() % GENERATE_MAX;
    if (dot < GENERATE_FLAG)
        return NORMAL_DOT_GENERATE;
    dot = rand() % 4 + 1;
    return dot;
}

int Golden::soulGenerate()
{
    int soul_value = cur_soul;
    if (cur_soul < soul_remain)
        cur_soul++;
    return soul_value;
}

Uint16 Golden::getHP()
{
    return health_point;
}

void Golden::takeDamage(GOLDEN_DAMAGE_TYPE damage_type)
{
    health_point -= GOLDEN_DAMAGE_VALUE[damage_type];
    return;
}

Point Golden::getStartPoint()
{
    return start_point;
}
