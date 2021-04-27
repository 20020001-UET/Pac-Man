///Entity [Source]
#include "Entity.h"

///Include header
#include "Labyrinth.h"

///Entity class
//Constructor:
Entity::Entity()
{
    graphic = NULL;
    timer = NULL;
    return;
}

Entity::Entity(Point _tile, OBJECT_TYPE _type)
{
    graphic = NULL;
    timer = NULL;
    type = _type;
    tile = _tile;
    update();
    return;
}

//Destructor:
Entity::~Entity()
{
    graphic = NULL;
    timer = NULL;
    return;
}

///function:
//init:
void Entity::init(Graphic* _graphic, Timer* _timer)
{
    graphic = _graphic;
    timer = _timer;
    return;
}

//get point:
Point Entity::getTile() const
{
    return tile;
}

Point Entity::getScreen() const
{
    return screen;
}

//position:
void Entity::move(Point vel)
{
    screen = screen + vel;
    dest = {screen.x - RESOURCES_PIXEL/2, screen.y - RESOURCES_PIXEL/2, OBJECT_PIXEL, OBJECT_PIXEL};

    if (checkScreen())
    {
        tile = screen / RESOURCES_PIXEL;
    }

    return;
}

void Entity::setTile(Point newTile)
{
    tile = newTile;
    update();
    return;
}

void Entity::setScreen(Point newScreen)
{
    screen = newScreen;
    dest = {screen.x - RESOURCES_PIXEL/2, screen.y - RESOURCES_PIXEL/2, OBJECT_PIXEL, OBJECT_PIXEL};
    tile = screen / RESOURCES_PIXEL;
    return;
}

void Entity::handleTunnel()
{
    if (checkScreen())
    {
        //tile.x == LABYRINTH_DATA_WIDTH || tile.y == LABYRINTH_DATA_HEIGHT || tile.x == -1 || tile.y == -1

        if (tile.x == LABYRINTH_DATA_WIDTH)
            setTile(Point(0, tile.y));
        if (tile.x == -1)
            setTile(Point(LABYRINTH_DATA_WIDTH - 1, tile.y));

        if (tile.y == LABYRINTH_DATA_HEIGHT)
            setTile(Point(tile.x, 0));
        if (tile.y == -1)
            setTile(Point(tile.x, LABYRINTH_DATA_HEIGHT - 1));
    }
    return;
}

//check screen:
bool Entity::checkScreen() const
{
    return (screen.x % RESOURCES_PIXEL == 0 && screen.y % RESOURCES_PIXEL == 0);
}

//check collision:
bool Entity::checkCollision(const Entity* another) const
{
    return !( ((screen.y + OBJECT_PIXEL - COLLISION_VALUE) <= another->screen.y) || (screen.y >= (another->screen.y + OBJECT_PIXEL - COLLISION_VALUE)) ||
              ((screen.x + OBJECT_PIXEL - COLLISION_VALUE) <= another->screen.x) || (screen.x >= (another->screen.x + OBJECT_PIXEL - COLLISION_VALUE)) );
}

//Update:
void Entity::update()
{
    screen = tile * RESOURCES_PIXEL;
    dest = {screen.x - RESOURCES_PIXEL/2, screen.y - RESOURCES_PIXEL/2, OBJECT_PIXEL, OBJECT_PIXEL};
    return;
}
