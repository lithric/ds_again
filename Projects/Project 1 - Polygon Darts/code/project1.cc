#include "fraction.h"
#include "point.h"
#include <iostream>
#include <memory>

using namespace std;

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
    unique_ptr<Point>* p; // dart board polygon
    int32_t n, // number of points
    m; // number of darts
    unique_ptr<Point> b = make_unique<Point>(); // dart board rect end
    cout << "Input the point for the opposite corner of the dartboard:\n";
    cin >> *b;
    cout << "How many points do you want to enter? (<=100):\n";
    cin >> n;
    if (n>100) throw "number of points must be less than 100!";
    p = new std::unique_ptr<Point>[n+2];
    *p[0] = Point(0,0);
    for (int i=1;i<=n;i++) {
        cout << "Enter point " << n << ": ";
        cin >> *p[i];
    }
    p[n+1] = std::move(b);
    cout << "How many darts were thrown (<=10)?:\n";
    cin >> m;

    delete [] p;
    return 0;
}