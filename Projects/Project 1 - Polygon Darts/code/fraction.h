#ifndef _FRACTION_H
#define _FRACTION_H
#include <iostream>
#include <cstdint>
#include <cmath>

class Fraction {
    public:
        Fraction(int32_t _num=0, int32_t _den=1, bool simplify=true);
        Fraction(double _num, double _den=1, bool simplify=true);
        Fraction(int32_t _num, double _dnum, int32_t _den, double _dden, bool simplify=true);
        Fraction(const Fraction& rhs) {
            num = rhs.num;
            dnum = rhs.dnum;
            den = rhs.den;
            dden = rhs.dden;
        };
        ~Fraction() = default;

        const Fraction& operator=(const Fraction& rhs);
        Fraction operator-();
        Fraction operator-(const Fraction& rhs);
        const Fraction& operator-=(const Fraction& rhs) {return *this=*this-rhs;}
        Fraction operator+();
        Fraction operator+(const Fraction& rhs);
        const Fraction& operator+=(const Fraction& rhs) {return *this=*this+rhs;}
        Fraction operator*(const Fraction& rhs);
        const Fraction& operator*=(const Fraction& rhs) {return *this=*this*rhs;}
        Fraction operator/(const Fraction& rhs);
        const Fraction& operator/=(const Fraction& rhs) {return *this=*this/rhs;}
        Fraction operator^(const int32_t& rhs);
        const Fraction& operator^=(const int32_t& rhs) {return *this=*this^rhs;}

        bool operator==(const Fraction& rhs);
        bool operator!=(const Fraction& rhs);
        bool operator>=(const Fraction& rhs);
        bool operator<=(const Fraction& rhs);
        bool operator>(const Fraction& rhs);
        bool operator<(const Fraction& rhs);

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