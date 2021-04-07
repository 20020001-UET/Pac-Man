///Point [Source]
#include "Point.h"

#include <cstdlib>
#define SQR(a) a*a

Point::Point()
{
    x = y = 0;
}

Point::Point(int _x, int _y)
{
    x = _x;
    y = _y;
}

Point::Point(const Point& point)
{
    x = point.x;
    y = point.y;
}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

int Point::distance(Point a, Point b)
{
    return (SQR(abs(a.x - b.x)) + SQR(abs(a.y - b.y)));
}

bool Point::checkEqual(Point a, Point b)
{
    return (a.x == b.x) && (a.y == b.y);
}

FPoint::FPoint()
{
    x = y = 0.0f;
}

FPoint::FPoint(float _x, float _y)
{
    x = _x;
    y = _y;
}

float FPoint::getX()
{
    return x;
}

float FPoint::getY()
{
    return y;
}
