///Distance [Source]
#include "Distance.h"

///Header include
#include <math.h>
#include <cstdlib>
#define SQR(a) a*a

///Distance namespace
int DISTANCE::Euclidean(const Point& first, const Point& second)
{
    return SQR(abs(first.x - second.x)) + SQR(abs(first.y - second.y));
}

float DISTANCE::Euclidean(const FPoint& first, const FPoint& second)
{
    return sqrt(SQR(abs(first.x - second.x)) + SQR(abs(first.y - second.y)));
}

int DISTANCE::Manhattan(const Point& first, const Point& second)
{
    return abs(first.x - second.x) + abs(first.y - second.y);
}
