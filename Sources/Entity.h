///Entity [Header]
#ifndef ENTITY_H_
#define ENTITY_H_

///Include header
#include <SDL.h>
#include "Graphic.h"
#include "Timer.h"
#include "Point.h"
#include "Point.h"

///Collision value
const int COLLISION_VALUE = 7*3;

///Entity class
class Entity
{
    public:
        //Constructor:
        Entity();
        Entity(Point _tile, OBJECT_TYPE _type);

        //Destructor:
        virtual ~Entity();

        ///function:
        //init:
        virtual void init(Graphic* _graphic, Timer* _timer);

        //get point:
        Point getTile() const;
        Point getScreen() const;

        //position:
        void move(Point vel);
        void setTile(Point newTile);
        void setScreen(Point newScreen);
        void handleTunnel();

        //check the screen point:
        bool checkScreen() const;

        //check collision:
        bool checkCollision(const Entity* another) const;

    protected:
        ///Graphic
        Graphic* graphic;
        Timer* timer;

        ///Object type
        OBJECT_TYPE type;

        ///Position
        Point tile, screen;
        SDL_Rect dest;

        ///Update screen & dest
        void update();
};

#endif // ENTITY_H_
