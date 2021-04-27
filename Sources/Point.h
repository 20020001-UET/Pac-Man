///Point [Header]
#ifndef POINT_H_
#define POINT_H_

///Struct Point
struct Point
{
    //Constructor:
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) { };

    //Operator:
    Point& operator=(const Point& another);
    bool operator==(const Point& another) const;
    Point operator+(const Point& another) const;
    Point operator-(const Point& another) const;
    Point operator*(const int& number) const;
    Point operator/(const int& number) const;

    //Point x and y value:
    int x, y;
};

//Function:
int distance(const Point& first, const Point& second);

#endif // POINT_H_
