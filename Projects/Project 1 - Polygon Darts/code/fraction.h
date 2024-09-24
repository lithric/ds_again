#include <iostream>
#include <cstdint>
#include <cmath>

#ifndef _FRACTION_H
#define _FRACTION_H

class Fraction {
    public:
        Fraction(int32_t _num=0, int32_t _den=1, bool simplify=true);
        Fraction(double _num, double _den=1, bool simplify=true);
        Fraction(int32_t _num, double _dnum, int32_t _den, double _dden, bool simplify=true);
        ~Fraction() = default;

        Fraction* operator=(Fraction rhs);
        Fraction operator-();
        Fraction operator-(Fraction rhs);
        Fraction* operator-=(Fraction rhs) {*this=*this-rhs;return this;}
        Fraction operator+();
        Fraction operator+(Fraction rhs);
        Fraction* operator+=(Fraction rhs) {*this=*this+rhs;return this;}
        Fraction operator*(Fraction rhs);
        Fraction* operator*=(Fraction rhs) {*this=*this*rhs;return this;}
        Fraction operator/(Fraction rhs);
        Fraction* operator/=(Fraction rhs) {*this=*this/rhs;return this;}
        Fraction operator^(int32_t rhs);
        Fraction* operator^=(int32_t rhs) {*this=*this^rhs;return this;}

        bool operator==(Fraction rhs);
        bool operator!=(Fraction rhs);
        bool operator>=(Fraction rhs);
        bool operator<=(Fraction rhs);
        bool operator>(Fraction rhs);
        bool operator<(Fraction rhs);

        int32_t getNum() {return num;};
        int32_t getDen() {return den;};
        double get_exact_num() {return num+dnum;};
        double get_exact_den() {return den+dden;};
        bool has_dec_num() {return dnum!=0;};
        bool has_dec_den() {return dden!=0;};

    private:
        int32_t num;
        int32_t den;
        double dnum;
        double dden;
};

std::ostream& operator<<(std::ostream& out, Fraction fraction);
std::istream& operator>>(std::istream& in, Fraction& fraction);

#endif