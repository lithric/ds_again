#include "fraction.h"
#include <iostream>
#include <cmath>

#ifndef __POINT_H__
#define __POINT_H__

class Point {
    public:
        Point(Fraction _x=Fraction(), Fraction _y=Fraction());
        ~Point() = default;

        Point operator+();
        Point operator+(Point rhs);
        Point operator-();
        Point operator-(Point rhs);
        Point operator*(Fraction rhs);
        Point operator/(Fraction rhs);

        Fraction operator*(Point rhs); // dot product
        Fraction operator%(Point rhs); // cross product

        Fraction norm();
        
    private:
        Fraction x;
        Fraction y;
};

std::ostream& operator<<(std::ostream& out, Point& point);
std::istream& operator>>(std::istream& in, Point point);

#endif