#include "fraction.h"

#ifndef __POINT_H__
#define __POINT_H__

class Point {
    public:
        Point(Fraction _x=Fraction(0), Fraction _y=Fraction(0));
        ~Point() = default;

        Point operator-(Point rhs) {
            return Point(this->x-rhs.x,this->y-rhs.y);
        }
        Point operator+(Point rhs) {
            return Point(this->x+rhs.x,this->y+rhs.y);
        }
    private:
        Fraction x;
        Fraction y;
};

#endif