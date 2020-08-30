#ifndef POINT_H
#define POINT_H

struct Point
{
    explicit Point() : x(0), y(0), code(0) {}
    explicit Point(int y, int x, int code) : x(x), y(y), code(code) {}

    int x;
    int y;
    int code;
};

#endif // POINT_H
