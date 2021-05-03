///Fruit [Source]
#include "Fruit.h"

///Include header

///Fruit class
//Contructor:
Fruit::Fruit(Point _tile) : Entity()
{
    console = new Console("Fruit");

    type = OBJECT_FRUIT;

    tile = _tile;
    update();

    return;
}

//Destructor:
Fruit::~Fruit()
{
    delete console;
    console = NULL;
    graphic = NULL;
    timer = NULL;
    return;
}

//function:
//init:
void Fruit::init(Graphic* _graphic, Timer* _timer, Point _stand, Point _wait)
{
    graphic = _graphic;
    timer = _timer;
    sprite_val = frame = 0;
    frame_value = FRUIT_FRAME_VALUE;

    direction = UNSET_DIRECTION;
    stand = _stand;
    wait = _wait;

    fruit_type = FRUIT_CHERRY;

    setTile(stand);
    update();

    return;
}

void Fruit::setType(const int level)
{
    setType(FRUIT_TYPE_AT[level]);
    return;
}

void Fruit::setType(const FRUIT_TYPE new_fruit_type)
{
    fruit_type = new_fruit_type;

    return;
}

//loop:
void Fruit::loop()
{
    handleState();

    //handleTunnel();

    return;
}

//render:
void Fruit::render()
{
    if (curState == FRUIT_STAND)
        return;
    if (animated)
    {
        sprite_val = frame / frame_value;

        ++frame;
        if (frame / frame_value >= FRUIT_ANIMTAION_FRAME)
            frame = 0;
    }

    graphic->draw(fruit_type, sprite_val, dest);
    return;
}

///state
void Fruit::setState(const FRUIT_STATE newState)
{
    curState = newState;
    startState = timer->getTicks();
    initState();
    return;
}

void Fruit::initState()
{
    switch (curState)
    {
        case FRUIT_INIT:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = FRUIT_SPEED;
            frame = 0;
            frame_value = FRUIT_FRAME_VALUE;
            sprite_val = 0;

            setState(FRUIT_STAND);

            outOfStandPosition = false;
            break;
        }
        case FRUIT_STAND:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            setTile(stand);
            break;
        }
        case FRUIT_MOVING:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = FRUIT_SPEED;
            outOfStandPosition = true;
            setTarget(wait);
            break;
        }
        case FRUIT_RETURNING:
        {
            animated = true;
            stop = true;
            direction.type = UNSET_DIRECTION;
            speed = FRUIT_SPEED;
            outOfStandPosition = true;
            setTarget(stand);
            break;
        }
        case FRUIT_WAITING:
        {
            animated = false;
            stop = true;
            direction.type = UNSET_DIRECTION;
            outOfStandPosition = true;

            //set Ghost position:
            setTile(wait);
            screen.x -= RESOURCES_PIXEL/2;
            dest.x = screen.x - RESOURCES_PIXEL/2;

            break;
        }
        default:
            break;

    }
    return;

}

void Fruit::handleState()
{
    switch (curState)
    {
        case FRUIT_INIT:
        {

            break;
        }
        case FRUIT_STAND:
        {

            break;
        }
        case FRUIT_MOVING:
        case FRUIT_RETURNING:
        {
            if (getCurDirection() != UNSET_DIRECTION)
                move(direction.vel()*speed);

            if (tile == wait && curState == FRUIT_MOVING)
            {
                setState(FRUIT_WAITING);
                break;
            }

            if (tile == stand && curState == FRUIT_RETURNING)
            {
                setState(FRUIT_STAND);
                break;
            }

            break;
        }
        case FRUIT_WAITING:
        {
            int tickPast = timer->getTicks() - startState;
            if (tickPast >= FRUIT_WAIT_TIME)
                setState(FRUIT_RETURNING);
            break;
        }
        default:
            break;

    }
    return;
}

FRUIT_STATE Fruit::getState()
{
    return curState;
}

//playing function:
DIRECTION Fruit::getCurDirection()
{
    return direction.type;
}

void Fruit::setDirection(const DIRECTION newDirection)
{
    direction = Direction(newDirection);
    return;
}

void Fruit::setStop(bool _stop)
{
    stop = _stop;
    return;
}

bool Fruit::isOutOfStandPosition()
{
    return outOfStandPosition;
}

bool Fruit::isStop() const
{
    return stop;
}

void Fruit::setTarget(Point newTarget)
{
    target = newTarget;
    return;
}

//get:
Point Fruit::getTarget()
{
    return target;
}

Point Fruit::getStand()
{
    return stand;
}

Point Fruit::getWait()
{
    return wait;
}

