#include "fraction.h"

int abs(int n) {
    return n>0?n:-n;
}

int gcd(int n, int m) {
    int n1,n2,gcd_int,running_remainder;
    n = abs(n);
    m = abs(m);

    n1 = n<m?n:m;
    n2 = n<m?m:n;

    // n1 <= n2

    gcd_int = n2 % n1;
    running_remainder = n1 % gcd_int;
    while (running_remainder!=0) {
        gcd_int = running_remainder;
        running_remainder = n1 % running_remainder;
    }

    return gcd_int;
}

Fraction::Fraction(int _num, int _den) {
    int gcd_n = gcd(_num, _den);

    if (_den<0) {
        _num = -_num;
        _den = -_den;
    }

    num = _num/gcd_n;
    den = _den/gcd_n;
}