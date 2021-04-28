///Distance [Header]

///Header include
#include "Point.h"
#include "FPoint.h"

///Distance namespace

namespace DISTANCE
{
    int Euclidean(const Point& first, const Point& second);
    float Euclidean(const FPoint& first, const FPoint& second);
    int Manhattan(const Point& first, const Point& second);
}
