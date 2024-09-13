#include "fraction.h"
#include "point.h"
#include <iostream>

// allows recursion
#define CONTINUE_COMPILE
// ends recurrsion
#define FINISH_COMPILE(...)

#define MAP_IS_END_SIGNAL() 0, FINISH_COMPILE
#define MAP_NEXT0(test_end,next_macro,...) next_macro CONTINUE_COMPILE
#define MAP_NEXT1(test_end,next_macro) MAP_NEXT0 (test_end, next_macro, 0)
#define MAP_NEXT(test_end,next_macro) MAP_NEXT1 (MAP_IS_END_SIGNAL test_end, next_macro)
#define MAP0(f, x, test_end, args...) f(x)MAP_NEXT(test_end,MAP1) (f, test_end, args)
#define MAP1(f, x, test_end, args...) , f(x)MAP_NEXT(test_end,MAP2) (f, test_end, args)
#define MAP2(f, x, test_end, args...) , f(x)MAP_NEXT(test_end,MAP1) (f, test_end, args)
#define MAP(f,args...) EVAL(MAP0(f,args,()))
#define EVAL0(args...) args
#define EVAL1(args...) EVAL0(EVAL0(EVAL0(args)))
#define EVAL2(args...) EVAL1(EVAL1(EVAL1(args)))
#define EVAL3(args...) EVAL2(EVAL2(EVAL2(args)))
#define EVAL4(args...) EVAL3(EVAL3(EVAL3(args)))
#define EVAL(args...)  EVAL4(EVAL4(EVAL4(args)))

using namespace std;

template <typename T>
void writing(T text) {
    cout << text;
}
template <typename T>
T reading() {
    T data;
    cin >> data;
    return data;
}

#define prompt(type,args...) (MAP(writing,args), reading<type>())

bool intersect(Point p1, Point p2, Point q1, Point q2, Point* x) {
    Fraction t,u;
    Point r = p2 - p1; // Distance from p1 to p2
    Point s = q2 - q1; // Distance from q1 to q2

    Point v = q1 - p1;
    Fraction d = r % s;

    if (d!=0) {
        t = (v%s)/d; // Intersection point along P in units of r
        u = (v%r)/d; // Intersection point along Q in units of s

        if (t>0&&t<1&&u>0&&u<1) {
            *x = p1+r*t;
            return true;
        }
    }

    return false;
}

bool isInsidePolygon(Point p, Point c, Point* q, int32_t q_size) {
    Point v1,v2,h1,h2,z1,z2,x;
    int32_t w = 0; // Winding number

    v1 = Point(p.getX(),0); // v1 is point on board boundary directly below p
    v2 = Point(p.getX(),c.getY()); // v2 is point on board boundary directly above p

    h1 = Point(0,p.getY()); // h1 is point on board boundary directly left of p
    h2 = Point(c.getX(),p.getY()); // h2 is point on board boundary directly right of p

    for (int i=0;i<q_size;i++) {
        if (intersect(v1,v2,q[i],q[i+1],&x)) { // Passing directly above or below p
            z1=x-p;
            z2=q[i+1]-q[i];

            if (z1.getY()*z2.getX()<0) {
                w=w+1; // Add if we are moving counterclockwise around p
            }
            else {
                w=w-1; // Subtract if we are moving clockwise around p
            }
        }

        if (intersect(h1,h2,q[i],q[i+1],&x)) { // Passing directly left or right of p
            z1=x-p;
            z2=q[i+1]-q[i];

            if (z1.getX()*z2.getY()>0) {
                w=w+1;
            }
            else {
                w=w-1;
            }
        }
    }

    if (w==0) {
        return false;
    }
    else {
        return true;
    }
}

int main() {
    Point* p; // dart board polygon
    Point* d; // dart board darts
    int32_t n, // number of points
    m; // number of darts
    Point b; // dart board rect end
    b = prompt(Point,"Input the point for the opposite corner of the dartboard:\n");
    n = prompt(int32_t,"How many points do you want to enter? (<=100):\n");
    if (n>100) throw "number of points must be less than 100!";
    p = new Point[n+2];
    p[0] = Point(0,0);
    for (int i=1;i<=n;i++) {
        p[i] = prompt(Point,"Enter point ",i,": ");
    }
    p[n+1] = b;
    cout << "How many darts were thrown (<=10)?:\n";
    cin >> m;
    d = new Point[m];
    for (int i=0;i<m;i++) {
        d[i] = prompt(Point,"Where did dart ",i," land?:");
    }
    delete [] p;
    return 0;
}