///Point [Header]
#ifndef POINT_H_
#define POINT_H_

#define INT(a) (int)(a)

struct Point
{
    Point();
    Point(int _x, int _y);
    Point(const Point& point);
    int getX();
    int getY();

    int x, y;

    static int distance(Point a, Point b);
    static bool checkEqual(Point a, Point b);
};

struct FPoint
{
    FPoint();
    FPoint(float _x, float _y);
    float getX();
    float getY();

    float x, y;
};

#endif // POINT_H_
