#include "point.h"

Point::Point(Fraction _x, Fraction _y) {
    x = _x;
    y = _y;
}

Point Point::operator+() {
    return Point(x,y);
}

Point Point::operator+(Point rhs) {
    Fraction _x, _y;

    _x = x+rhs.x;
    _y = y+rhs.y;

    return Point(_x,_y);
}

Point Point::operator-() {
    return Point(-x,-y);
}

Point Point::operator-(Point rhs) {
    Fraction _x, _y;

    _x = x-rhs.x;
    _y = y-rhs.y;

    return Point(_x,_y);
}
Point Point::operator*(Fraction rhs) {
    Fraction _x, _y;

    _x = x*rhs;
    _y = y*rhs;

    return Point(_x,_y);
}

Point Point::operator/(Fraction rhs) {
    Fraction _x, _y;

    _x = x/rhs;
    _y = y/rhs;

    return Point(_x,_y);
}

Fraction Point::norm() {
    Fraction abs_2;
    double _num, _den;
    abs_2 = x*x+y*y;
    _num = std::sqrt(abs_2.get_exact_num());
    _den = std::sqrt(abs_2.get_exact_den());
    return Fraction(_num,_den);
}

// dot product
Fraction Point::operator*(Point rhs) {
    return x*rhs.x+y*rhs.y;
}

// cross product
Fraction Point::operator%(Point rhs) {
    return x*rhs.y-y*rhs.x;
}

bool Point::operator==(Point rhs) {
    return x==rhs.x&&y==rhs.y;
}
bool Point::operator!=(Point rhs) {
    return x!=rhs.x||y!=rhs.y;
}

std::ostream& operator<<(std::ostream& out, Point point) {
    out << "( " << point.getX() << " , " << point.getY() << " )";
    return out;
}
std::istream& operator>>(std::istream& in, Point& point) {
    Fraction x, y;
    char left_peren, comma, right_peren;
    in >> left_peren >> x >> comma >> y >> right_peren;
    point = Point(x,y);
    return in;
}