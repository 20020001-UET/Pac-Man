///FPoint [Header]
#ifndef FPOINT_H_
#define FPOINT_H_

///Struct FPoint
struct FPoint
{
    //Constructor:
    FPoint(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) { };

    //Operator:
    FPoint& operator=(const FPoint& another);
    bool operator==(const FPoint& another) const;
    FPoint operator+(const FPoint& another) const;
    FPoint operator-(const FPoint& another) const;
    FPoint operator*(const float& number) const;
    FPoint operator/(const float& number) const;

    //FPoint x and y value:
    float x, y;
};

#endif // FPOINT_H_

