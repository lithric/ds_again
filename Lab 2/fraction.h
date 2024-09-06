#include <iostream>
#include <cstdint>
#include <cmath>

#ifndef _FRACTION_H
#define _FRACTION_H

class Fraction {
    public:
        Fraction(int32_t _num=0, int32_t _den=1);
        ~Fraction() = default;

        Fraction operator-();
        Fraction operator-(Fraction rhs);
        Fraction operator+();
        Fraction operator+(Fraction rhs);
        Fraction operator*(Fraction rhs);
        Fraction operator/(Fraction rhs);

        bool operator==(Fraction rhs);
        bool operator!=(Fraction rhs);
        bool operator>=(Fraction rhs);
        bool operator<=(Fraction rhs);
        bool operator>(Fraction rhs);
        bool operator<(Fraction rhs);

        int32_t getNum() {return num;};
        int32_t getDen() {return den;};

    private:
        int32_t num;
        int32_t den;
};

std::ostream& operator<<(std::ostream& out, Fraction fraction);
std::istream& operator>>(std::istream& in, Fraction& fraction);

#endif