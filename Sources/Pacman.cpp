///Pacman [Source]
#include "Pacman.h"

///Include header

///Pacman class
//Contructor:
Pacman::Pacman(PACMAN_TYPE _pacman_type) : Entity(Point(), OBJECT_PACMAN)
{
    pacman_type = _pacman_type;

    if (pacman_type == PACMAN_MS)
        type = OBJECT_PACMAN_MS;

    if (pacman_type == PACMAN_ANDROID)
        type = OBJECT_PACMAN_ANDROID;

    return;
}

//Destructor:
Pacman::~Pacman()
{
    graphic = NULL;
    timer = NULL;

    return;
}

///function:
//init:
void Pacman::init(Graphic* _graphic, Timer* _timer, Point _stand)
{
    graphic = _graphic;
    timer = _timer;

    sprite_val = frame = 0;
    frame_value = PACMAN_FRAME_VALUE;

    stand = _stand;

    graphic->setTextureBlending(PACMAN, SDL_BLENDMODE_BLEND);

    return;
}

//loop:
void Pacman::loop()
{
    handleState();
    handlePower();

    handleTunnel();

    return;
}

//render:
void Pacman::render()
{
    if (!animated)
    {
        graphic->draw(type, sprite_val, dest);
        return;
    }

    if (curState == PACMAN_RUNNING_STATE)
    {
        switch (getCurDirection())
        {
            case UP:
                sprite_val = PACMAN_UP;
                break;
            case RIGHT:
                sprite_val = PACMAN_RIGHT;
                break;
            case DOWN:
                sprite_val = PACMAN_DOWN;
                break;
            case LEFT:
                sprite_val = PACMAN_LEFT;
                break;
            default:
                break;
        }

        sprite_val += frame / frame_value;

        //Speed effect
        if (!lastPoint.empty())
        {
            int lastAlpha = graphic->getTextureAlpha(PACMAN);
            SDL_Rect lastDest = {0, 0, OBJECT_PIXEL, OBJECT_PIXEL};
            for (unsigned int index = 0; index < lastPoint.size(); index++)
            {
                lastDest.x = lastPoint[index].x;
                lastDest.y = lastPoint[index].y;
                graphic->setTextureAlpha(PACMAN, lastAlpha/(index+1));
                graphic->draw(type, sprite_val, lastDest);
            }
            graphic->setTextureAlpha(PACMAN, lastAlpha);
        }

        if (power[SPEED_PACMAN])
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

        ++frame;
        if (frame / frame_value >= PACMAN_ANIMTAION_FRAME)
            frame = 0;
    }

    if (curState == PACMAN_DEATH_STATE)
    {
        sprite_val = frame / frame_value;

        ++frame;
        if (frame / frame_value >= PACMAN_DEATH_ANIMATION_FRAME)
            frame = 0;
    }

    graphic->draw(type, sprite_val, dest);
    return;
}

///state function:
//state:
PACMAN_STATE Pacman::getState()
{
    return curState;
}

void Pacman::setState(PACMAN_STATE newState)
{
    curState = newState;
    startState = timer->getTicks();
    initState();
    return;
}

void Pacman::initState()
{
    switch (curState)
    {
        case PACMAN_INIT_STATE:
        {
            setPower(NORMAL_PACMAN);
            dotEaten = 0;
            life = PACMAN_LIFE;

            type = OBJECT_PACMAN;
            if (pacman_type == PACMAN_MS)
                type = OBJECT_PACMAN_MS;

            if (pacman_type == PACMAN_ANDROID)
                type = OBJECT_PACMAN_ANDROID;

            speed = PACMAN_SPEED;

            setState(PACMAN_STAND_STATE);

            graphic->setTextureAlpha(PACMAN, 0xFF);

            break;
        }
        case PACMAN_NEW_STATE:
        {
            setPower(NORMAL_PACMAN);

            type = OBJECT_PACMAN;
            if (pacman_type == PACMAN_MS)
                type = OBJECT_PACMAN_MS;

            if (pacman_type == PACMAN_ANDROID)
                type = OBJECT_PACMAN_ANDROID;

            speed = PACMAN_SPEED;

            setState(PACMAN_STAND_STATE);

            graphic->setTextureAlpha(PACMAN, 0xFF);

            break;
        }
        case PACMAN_STAND_STATE:
        {
            clearQueue();

            frame = 0;
            animated = false;

            //set Pacman position:
            setTile(stand);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            sprite_val = 0;
            if (pacman_type == PACMAN_MS)
                sprite_val = PACMAN_LEFT;

            if (pacman_type == PACMAN_ANDROID)
                sprite_val = PACMAN_LEFT;

            break;
        }
        case PACMAN_RUNNING_STATE:
        {
            animated = true;
            break;
        }
        case PACMAN_EATING_STATE:
        {
            animated = false;
            break;
        }
        case PACMAN_DEATH_STATE:
        {
            clearQueue();

            animated = true;
            frame = 0;
            frame_value = 16;
            type = OBJECT_PACMAN_DEATH;

            life--;
            break;
        }
        default:
            break;
    }
    return;
}

void Pacman::handleState()
{
    switch (curState)
    {
        case PACMAN_INIT_STATE:
        case PACMAN_NEW_STATE:
        {

            break;
        }
        case PACMAN_STAND_STATE:
        {
            if (!direction.empty())
                setState(PACMAN_RUNNING_STATE);
            break;
        }
        case PACMAN_RUNNING_STATE:
        {
            if (!direction.empty())
                move(direction.front().vel()*speed);
            break;
        }
        case PACMAN_EATING_STATE:
        {
            int tickPast = timer->getTicks() - startState;
            if (tickPast >= PACMAN_EATING_STATE_TIME)
                setState(PACMAN_RUNNING_STATE);
            break;
        }
        case PACMAN_DEATH_STATE:
        {

            break;
        }
        default:
            break;
    }
    return;
}

//power:
void Pacman::setPower(PACMAN_POWER_STATE newPower)
{
    if (newPower == NORMAL_PACMAN)
    {
        for (int index = 0; index <= PACMAN_POWER_STATE_TOTAL; index++)
        {
            power[index] = false;
            startPower[index] = 0;
        }
    }

    power[newPower] = true;
    startPower[newPower] = timer->getTicks();
    initPower(newPower);

    return;
}

void Pacman::initPower(PACMAN_POWER_STATE curNewPower)
{
    switch (curNewPower)
    {
        case NORMAL_PACMAN:
        {
            if (speed != PACMAN_SPEED)
                if (checkScreen())
                    speed = PACMAN_SPEED;
            frame_value = PACMAN_FRAME_VALUE;
            graphic->setTextureAlpha(PACMAN, 0xFF);
            break;
        }
        case POWER_PACMAN:
        {

            break;
        }
        case SPEED_PACMAN:
        {
            if (checkScreen())
                speed = 4;
            frame_value = 2;
            break;
        }
        case INVISIBLE_PACMAN:
        {
            graphic->setTextureAlpha(PACMAN, 75);
            break;
        }
        case FREE_TIME_PACMAN:
        {

            break;
        }
        default:
            break;
    }
    return;
}

void Pacman::handlePower()
{
    bool isNormal = true;
    for (int curPower = 1; curPower < PACMAN_POWER_STATE_TOTAL; curPower++)
        if (power[curPower])
        {
            int tickPast = timer->getTicks() - startPower[curPower];
            if (tickPast >= POWER_TIME[curPower])
            {
                removePower(curPower);
            }
            else
            {
                switch (curPower)
                {
                    case POWER_PACMAN:
                    {
                        break;
                    }
                    case SPEED_PACMAN:
                    {
                        if (checkScreen())
                            speed = 4;
                        break;
                    }
                    case INVISIBLE_PACMAN:
                    {
                        break;
                    }
                    case FREE_TIME_PACMAN:
                    {
                        break;
                    }
                }
            }
            isNormal = false;
        }

    if (isNormal)
    {
        if (speed != PACMAN_SPEED)
            if (checkScreen())
                speed = PACMAN_SPEED;
        frame_value = PACMAN_FRAME_VALUE;
    }

    return;
}

void Pacman::removePower(int curLastPower)
{
    power[curLastPower] = false;
    startPower[curLastPower] = 0;
    switch (curLastPower)
    {
        case POWER_PACMAN:
        {
            type = OBJECT_PACMAN;
            if (pacman_type == PACMAN_MS)
                type = OBJECT_PACMAN_MS;

            if (pacman_type == PACMAN_ANDROID)
                type = OBJECT_PACMAN_ANDROID;

            break;
        }
        case SPEED_PACMAN:
        {
            if (speed != PACMAN_SPEED)
                if (checkScreen())
                    speed = PACMAN_SPEED;
            frame_value = PACMAN_FRAME_VALUE;
            break;
        }
        case INVISIBLE_PACMAN:
        {
            graphic->setTextureAlpha(PACMAN, 0xFF);
            break;
        }
        case FREE_TIME_PACMAN:
        {
            break;
        }
    }
    return;
}

//playing function:
DIRECTION Pacman::getCurDirection()
{
    return (direction.empty()) ? (UNSET_DIRECTION) : (direction.front().type);
}

DIRECTION Pacman::getLastDirection()
{
    return (direction.empty()) ? (UNSET_DIRECTION) : (direction.back().type);
}

void Pacman::setDirection(DIRECTION newDirection)
{
    if (curState == PACMAN_STAND_STATE)
    {
        if (newDirection == RIGHT || newDirection == LEFT)
            direction.push(newDirection);
        return;
    }

    if (!direction.empty())
    {
        if (direction.front().against(newDirection))
            clearQueue();
    }

    if (direction.size() < 2)
        direction.push(newDirection);
    return;
}

void Pacman::eatDot()
{
    dotEaten++;
    return;
}

void Pacman::stop(bool canPacmanMove)
{
    if (direction.size() > 1)
    {
        if (checkScreen())
            if (canPacmanMove)
                direction.pop();
    }
    return;
}

bool Pacman::isDead()
{
    return (life <= 0);
}

void Pacman::dead()
{
    life--;
    return;
}

//dot function:
int Pacman::getDotEaten() const
{
    return dotEaten;
}

//life function:
int Pacman::getCurLife() const
{
    return life;
}

//queue function:
void Pacman::clearQueue()
{
    while (!direction.empty())
        direction.pop();
    return;
}
