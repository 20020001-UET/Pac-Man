///Mystery [Source]
#include "Mystery.h"

///Include header

///Mystery class
//Contructor:
Mystery::Mystery(Point _tile) : Entity()
{
    console = new Console("Mystery");

    type = OBJECT_MYSTERY;

    tile = _tile;
    update();

    return;
}

//Destructor:
Mystery::~Mystery()
{
    delete console;
    console = NULL;
    graphic = NULL;
    timer = NULL;
    return;
}

//function:
//init:
void Mystery::init(Graphic* _graphic, Timer* _timer, Point _stand, Point _wait, Point _speech, Point _upgrade)
{
    graphic = _graphic;
    timer = _timer;
    sprite_val = frame = 0;
    frame_value = MYSTERY_FRAME_VALUE;

    direction = UNSET_DIRECTION;
    stand = _stand;
    wait = _wait;
    speech = _speech;
    upgrade = _upgrade;

    curSpeech = -1;

    setTile(stand);
    update();

    return;
}

void Mystery::setSpeechPoint(Point _speech_upgrade, Point _speech_show_up)
{
    speech_upgrade = _speech_upgrade;
    speech_show_up = _speech_show_up;
    return;
}

//loop:
void Mystery::loop()
{
    handleState();

    //handleTunnel();

    return;
}

//render:
void Mystery::render()
{
    if (curState == MYSTERY_STAND)
        return;

    int sprite = 0;

    if (animated)
    {
        sprite_val = frame / frame_value;

        ++frame;
        if (frame / frame_value >= UNIQUE_GHOST_MYSTERY_ANIMATION_FRAME)
            frame = 0;

        if (curState == MYSTERY_WAITING_TO_SHOW_UP)
        {
            int tickPast = timer->getTicks() - startState;

            if (tickPast <= 3200)
            {
                if ((tickPast/200) % 2 == 0)
                    sprite = UNIQUE_GHOST_MYSTERY_DEFAULT;
                else
                    sprite = UNIQUE_GHOST_MYSTERY_WHITE;
            }
            else
            {
                if ((tickPast/200) % 2 == 0)
                    sprite = UNIQUE_GHOST_MYSTERY_UPGRADE_DEFAULT;
                else
                    sprite = UNIQUE_GHOST_MYSTERY_UPGRADE_WHITE;
            }
        }
    }

    graphic->draw(type, sprite_val + sprite, dest);

    if (curState == MYSTERY_SPEECH_UPGRADE)
    {
        int tickPast = timer->getTicks() - startState;
        if (tickPast >= 2000)
            graphic->draw(SPEECH_UPGRADE, curSpeech, speech_upgrade);
    }

    if (curState == MYSTERY_SPEECH_SHOW_UP)
    {
        int tickPast = timer->getTicks() - startState;
        if (tickPast >= 2100)
            graphic->draw(SPEECH_SHOW_UP, 1, speech_show_up);
        else
            graphic->draw(SPEECH_SHOW_UP, 0, speech_show_up);
    }

    return;
}

///state
void Mystery::setState(const MYSTERY_STATE newState)
{
    curState = newState;
    startState = timer->getTicks();
    initState();
    return;
}

void Mystery::initState()
{
    switch (curState)
    {
        case MYSTERY_INIT:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = MYSTERY_SPEED;
            frame = 0;
            frame_value = MYSTERY_FRAME_VALUE;
            sprite_val = 0;

            setState(MYSTERY_STAND);

            outOfStandPosition = false;
            break;
        }
        case MYSTERY_STAND:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            setTile(stand);
            break;
        }
        case MYSTERY_MOVING:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = MYSTERY_SPEED;
            outOfStandPosition = true;
            setTarget(wait);
            break;
        }
        case MYSTERY_MOVING_TO_SPEECH:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = MYSTERY_SPEED;
            outOfStandPosition = true;
            setTarget(speech);
            break;
        }
        case MYSTERY_MOVING_TO_SHOW_UP:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = MYSTERY_SPEED;
            outOfStandPosition = true;
            setTarget(upgrade);
            break;
        }
        case MYSTERY_RETURNING:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = MYSTERY_SPEED;
            outOfStandPosition = true;
            setTarget(stand);
            break;
        }
        case MYSTERY_WAITING:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            outOfStandPosition = true;

            //set Ghost position:
            setTile(wait);
            screen.x += RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            break;
        }
        case MYSTERY_SPEECH_UPGRADE:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            outOfStandPosition = true;

            curSpeech++;

            setTile(speech);

            break;
        }
        case MYSTERY_SPEECH_SHOW_UP:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            outOfStandPosition = true;

            //set Ghost position:
            setTile(upgrade);
            screen.x += RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            break;
        }
        case MYSTERY_WAITING_TO_SPEECH:
        case MYSTERY_WAITING_TO_SHOW_UP:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            outOfStandPosition = true;
            break;
        }
        default:
            break;

    }
    return;

}

void Mystery::handleState()
{
    switch (curState)
    {
        case MYSTERY_INIT:
        {

            break;
        }
        case MYSTERY_STAND:
        {

            break;
        }
        case MYSTERY_MOVING_TO_SPEECH:
        {
            if (getCurDirection() != UNSET_DIRECTION)
                move(direction.vel()*speed);

            if (tile == speech)
            {
                setState(MYSTERY_WAITING_TO_SPEECH);
                break;
            }

            break;
        }
        case MYSTERY_MOVING_TO_SHOW_UP:
        {
            if (getCurDirection() != UNSET_DIRECTION)
                move(direction.vel()*speed);

            if (tile == upgrade)
            {
                setState(MYSTERY_SPEECH_SHOW_UP);
                break;
            }

            break;
        }
        case MYSTERY_MOVING:
        case MYSTERY_RETURNING:
        {
            if (getCurDirection() != UNSET_DIRECTION)
                move(direction.vel()*speed);

            if (tile == wait && curState == MYSTERY_MOVING)
            {
                setState(MYSTERY_WAITING);
                break;
            }

            if (tile == stand && curState == MYSTERY_RETURNING)
            {
                setState(MYSTERY_STAND);
                break;
            }

            break;
        }
        case MYSTERY_WAITING:
        {
            int tickPast = timer->getTicks() - startState;
            if (tickPast >= MYSTERY_STATE_TIME[MYSTERY_WAITING])
                setState(MYSTERY_RETURNING);
            break;
        }
        case MYSTERY_SPEECH_UPGRADE:
            break;
        case MYSTERY_WAITING_TO_SPEECH:
            break;
        case MYSTERY_SPEECH_SHOW_UP:
        {
            int tickPast = timer->getTicks() - startState;
            if (tickPast >= MYSTERY_STATE_TIME[MYSTERY_SPEECH_SHOW_UP])
                setState(MYSTERY_WAITING_TO_SHOW_UP);
        }
        case MYSTERY_WAITING_TO_SHOW_UP:
            break;
        default:
            break;

    }
    return;
}

MYSTERY_STATE Mystery::getState()
{
    return curState;
}

//playing function:
DIRECTION Mystery::getCurDirection()
{
    return direction.type;
}

void Mystery::setDirection(const DIRECTION newDirection)
{
    direction = Direction(newDirection);
    return;
}

void Mystery::setStop(bool _stop)
{
    stop = _stop;
    return;
}

bool Mystery::isOutOfStandPosition()
{
    return outOfStandPosition;
}

bool Mystery::isStop() const
{
    return stop;
}

void Mystery::setTarget(Point newTarget)
{
    target = newTarget;
    return;
}

//get:
Point Mystery::getTarget()
{
    return target;
}

Point Mystery::getStand()
{
    return stand;
}

Point Mystery::getWait()
{
    return wait;
}

Point Mystery::getSpeech()
{
    return speech;
}

Point Mystery::getUpgrade()
{
    return upgrade;
}
