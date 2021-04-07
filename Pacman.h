///Pacman [Header]
#ifndef PACMAN_H_
#define PACMAN_H_

///Project headers
#include <queue>
#include "Direction.h"
#include "Entity.h"

const int FRAME_VALUE = 5;
const float PACMAN_SPEED = 2.50f;
const int PACMAN_LIFE = 5;

///Pacman class
class Pacman :
    public Entity
{
    public:
        Pacman(int x, int y, int w, int h);
        void loop();
        void render();

        void setDir(DIRECTION dir);
        DIRECTION getDir();
        void stop();

        void eatDot();
        int getDot();

        void dead();
        void keepAlive();
        bool isAlive();
        bool isDead();

    private:
        std::queue<DIRECTION> cur_dir;
        bool stand;
        int life;
        bool alive;
        int dotCount;
        int frame, sprite_frame;
        int waitTime;

};

#endif // PACMAN_H_
