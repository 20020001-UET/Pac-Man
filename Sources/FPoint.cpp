///FPoint [Source]
#include "FPoint.h"

///Struct FPoint
//Operator:
FPoint& FPoint::operator=(const FPoint& another)
{
    x = another.x;
    y = another.y;
    return *this;
}

bool FPoint::operator==(const FPoint& another) const
{
    return (x == another.x && y == another.y);
}

FPoint FPoint::operator+(const FPoint& another) const
{
    return FPoint(x + another.x, y + another.y);
}

FPoint FPoint::operator-(const FPoint& another) const
{
    return FPoint(x - another.x, y - another.y);
}

FPoint FPoint::operator*(const float& number) const
{
    return FPoint(x * number, y * number);
}

FPoint FPoint::operator/(const float& number) const
{
    return FPoint(x / number, y / number);
}
