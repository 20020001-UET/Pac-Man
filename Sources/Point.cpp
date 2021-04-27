///Point [Source]
#include "Point.h"

#include <cstdlib>
#define SQR(a) a*a

///Struct Point
//Operator:
Point& Point::operator=(const Point& another)
{
    x = another.x;
    y = another.y;
    return *this;
}

bool Point::operator==(const Point& another) const
{
    return (x == another.x && y == another.y);
}

Point Point::operator+(const Point& another) const
{
    return Point(x + another.x, y + another.y);
}

Point Point::operator-(const Point& another) const
{
    return Point(x - another.x, y - another.y);
}

Point Point::operator*(const int& number) const
{
    return Point(x * number, y * number);
}

Point Point::operator/(const int& number) const
{
    return Point(x / number, y / number);
}

//Function:
int distance(const Point& first, const Point& second)
{
    return SQR(abs(first.x - second.x)) + SQR(abs(first.y - second.y));
}
