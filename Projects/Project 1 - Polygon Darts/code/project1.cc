#include "fraction.h"
#include "point.h"
#include <iostream>

bool intersect(Point p1, Point p2, Point q1, Point q2, Point& x) {
    Fraction t,u;
    Point r = p2 - p1;
    Point s = q2 - q1;

    Point v = q1 - p1;
    Fraction d = r % s;

    if (d!=0) {
        t = (v%s)/d;
        u = (v%r)/d;
    }

    return true;
}

int main() {
    Fraction a = Fraction(1,1);
    Fraction b = Fraction(2,3);
    Fraction c = a + b;
    std::cout << c << std::endl;
    return 0;
}