#include "fraction.h"
#include "point.h"
#include <iostream>

// allows recursion
#define AS_MACRO
// ends recurrsion
#define END_SIGNAL(...)

#define MAP_IS_END_SIGNAL() 0, END_SIGNAL
#define MAP_NEXT0(test_end,next_macro,...) next_macro AS_MACRO
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

#define SHIFT_NAME(MACRO_NAME,FUNC_MACRO,args...) FUNC_MACRO AS_MACRO (args,MACRO_NAME)
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define FOO(args...) GET_MACRO(args, FOO4, FOO3, FOO2, FOO1)(args)

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

template <typename T>
T clean_reading(T (*func)(T)) {
    T data;
    cin >> data;
    return func(data);
}

#define print(args...) (MAP(writing,args))
#define prompt(type,args...) (MAP(writing,args), reading<type>())
#define func_prompt(type,func,args...) (MAP(writing,args), clean_reading<type>(func))

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

    for (int i=0;i<q_size;i++) { // q[q_size] -> q[0]
        if (intersect(v1,v2,q[i],q[(i+1)%q_size],&x)) { // Passing directly above or below p
            z1=x-p;
            z2=q[(i+1)%q_size]-q[i];

            if (z1.getY()*z2.getX()<0) {
                w=w+1; // Add if we are moving counterclockwise around p
            }
            else {
                w=w-1; // Subtract if we are moving clockwise around p
            }
        }

        if (intersect(h1,h2,q[i],q[(i+1)%q_size],&x)) { // Passing directly left or right of p
            z1=x-p;
            z2=q[(i+1)%q_size]-q[i];

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

Fraction findArea(Point* polygon, int32_t total_vertices) {
    Fraction area = 0;
    if (total_vertices<3) return Fraction(0);
    for (int i=0;i<total_vertices;i++) {
        area += polygon[i]%polygon[(i+1)%total_vertices];
    }
    area *= Fraction(1,2);
    return area;
}

int32_t _check_data(int32_t data) {
    if (data>100) {
        throw "Number of polygons must be less than 100!";
    }
    return data;
}

Fraction abs(Fraction num) {
    return num>=0?num:-num;
}

int main() {
    Point* dartboard_rectangle = new Point[4];
    dartboard_rectangle[0] = Point(0,0);
    Point** polygons; // polygons on the dartboard
    int32_t total_polygons; // total number of polygons (including the dartboard rectangle)
    int32_t* total_vertices_arr; // total number of vertices per polygon on the dartboard (including the dartboard rectange)
    Point* darts; // points of the darts on the dartboard
    int32_t total_darts; // total number of darts on the dartboard
    Fraction dartboard_area; // the area of the dartboard
    Fraction score = 0; // the score of the game

    print(Fraction(0,1)*Fraction(10,10));
    
    dartboard_rectangle[2] = prompt(Point,"Input the point for the opposite corner of the dartboard:\n");
    dartboard_rectangle[1] = Point(0,dartboard_rectangle[2].getY());
    dartboard_rectangle[3] = Point(dartboard_rectangle[2].getX(),0);
    if (dartboard_rectangle[2].getX()<0||dartboard_rectangle[2].getY()<0) {
        Point temp = dartboard_rectangle[1];
        dartboard_rectangle[1] = dartboard_rectangle[3];
        dartboard_rectangle[3] = temp;
    }
    dartboard_area = findArea(dartboard_rectangle,4);

    total_polygons = func_prompt(int32_t,_check_data,"How many polygons are on the dartboard? (<=100):\n");
    polygons = new Point*[total_polygons];
    total_vertices_arr = new int32_t[total_polygons];
    for (int i=0;i<total_polygons;i++) {
        total_vertices_arr[i] = prompt(int32_t,"How many vertices are in polygon ",i+1,"?:");
        polygons[i] = new Point[total_vertices_arr[i]];
        for (int j=0;j<total_vertices_arr[i];j++) {
            polygons[i][j] = prompt(Point,"Input the point for vertice ",j+1," of polygon ",i+1,":");
        }
    }
    total_darts = prompt(int32_t,"How many darts were thrown?:\n");
    darts = new Point[total_darts];
    for (int i=0;i<total_darts;i++) {
        darts[i] = prompt(Point,"Where did dart ",i+1," land?:");
    }

    for (int p=0;p<total_polygons;p++) {
        for (int d=0;d<total_darts;d++) {
            if (isInsidePolygon(darts[d],dartboard_rectangle[2],polygons[p],total_vertices_arr[p])) {
                score += dartboard_area/findArea(polygons[p],total_vertices_arr[p]);
                break;
            }
        }
    }

    print("Your final score is: ",score,"\n");

    for (int i=0;i<total_polygons;i++) {
        delete[] polygons[i]; // free sub-array of vertices
    }
    delete[] polygons; // free array of polygon pointers
    delete[] darts; // free array of darts
    delete[] total_vertices_arr; // free array of total vertices for each polygon
    delete[] dartboard_rectangle; // free array of dartboard points
    return 0;
}