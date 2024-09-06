#include "fraction.h"

static int32_t gcd(int32_t gcd_x1, int32_t gcd_x2) {
    int32_t _remainder;

    gcd_x1 = (gcd_x1>=0) ? gcd_x1:-gcd_x1;
    gcd_x2 = (gcd_x2>=0) ? gcd_x2:-gcd_x2;

    while (gcd_x2 != 0) {
        _remainder = gcd_x1 % gcd_x2;
        gcd_x1 = gcd_x2;
        gcd_x2 = _remainder;
    }

    return gcd_x1;
}

Fraction::Fraction(int32_t _num, int32_t _den) {
    int32_t gcd_int;

    if (_den < 0) {
        _num = -_num;
        _den = -_den;
    }

    gcd_int = gcd(_num,_den);

    num = _num/gcd_int;
    den = _den/gcd_int;
}

Fraction Fraction::operator+(Fraction rhs) {
    int32_t _num, _den;

    _num = num*rhs.den+rhs.num*den;
    _den = den*rhs.den;

    return Fraction(_num,_den);
}
Fraction Fraction::operator-(Fraction rhs) {
    int32_t _num, _den;

    _num = num*rhs.den-rhs.num*den;
    _den = den*rhs.den;

    return Fraction(_num,_den);
}
Fraction Fraction::operator*(Fraction rhs) {
    int32_t _num, _den;

    _num = num*rhs.num;
    _den = den*rhs.den;

    return Fraction(_num,_den);
}
Fraction Fraction::operator/(Fraction rhs) {
    int32_t _num, _den;

    _num = num*rhs.den;
    _den = den*rhs.num;

    return Fraction(_num,_den);
}

bool Fraction::operator==(Fraction rhs) {
    return num==rhs.num&&den==rhs.den;
}
bool Fraction::operator!=(Fraction rhs) {
    return num!=rhs.num||den!=rhs.den;
}
bool Fraction::operator>=(Fraction rhs) {
    return num*rhs.den>=rhs.num*den;
}
bool Fraction::operator<=(Fraction rhs) {
    return num*rhs.den<=rhs.num*den;
}
bool Fraction::operator>(Fraction rhs) {
    return num*rhs.den>rhs.num*den;
}
bool Fraction::operator<(Fraction rhs) {
    return num*rhs.den<rhs.num*den;
}

std::ostream& operator<<(std::ostream& out, Fraction fraction) {
    out << fraction.getNum() << " / " << fraction.getDen();
    return out;
}
std::istream& operator>>(std::istream& in, Fraction& fraction) {
    int32_t _num, _den;
    char _delim;
    in >> _num >> _delim >> _den;
    fraction = Fraction(_num,_den);
    return in;
}
