#ifndef STATE_H_
#define STATE_H_

class State
{
    public:
        virtual void init() {};
        virtual void loop() = 0;
        virtual void render() = 0;
        virtual void keyPressed(int key_code) = 0;
        virtual void keyReleased(int key_code) = 0;
        virtual void close() {};
};

#endif // STATE_H_
