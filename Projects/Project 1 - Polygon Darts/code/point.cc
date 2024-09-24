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
    int32_t num1,den1=1,num2,den2=1;
    char left_paren, comma, right_paren, slash;
    in >> left_paren >> num1 >> slash;
    if (slash=='/') {
        in >> den1 >> comma >> num2 >> slash;
        if (slash=='/') {
            in >> den2 >> right_paren;
        }
    }
    else if (slash==',') {
        in >> num2 >> slash;
        if (slash=='/') {
            in >> den2 >> right_paren;
        }
    }
    x = Fraction(num1,den1);
    y = Fraction(num2,den2);
    point = Point(x,y);
    return in;
}