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
        Fraction operator-() const;
        Fraction operator-(const Fraction& rhs) const;
        const Fraction& operator-=(const Fraction& rhs) {return *this=*this-rhs;}
        Fraction operator+() const;
        Fraction operator+(const Fraction& rhs) const;
        const Fraction& operator+=(const Fraction& rhs) {return *this=*this+rhs;}
        Fraction operator*(const Fraction& rhs) const;
        const Fraction& operator*=(const Fraction& rhs) {return *this=*this*rhs;}
        Fraction operator/(const Fraction& rhs) const;
        const Fraction& operator/=(const Fraction& rhs) {return *this=*this/rhs;}
        Fraction operator^(const int32_t& rhs) const;
        const Fraction& operator^=(const int32_t& rhs) {return *this=*this^rhs;}

        bool operator==(const Fraction& rhs) const;
        bool operator!=(const Fraction& rhs) const;
        bool operator>=(const Fraction& rhs) const;
        bool operator<=(const Fraction& rhs) const;
        bool operator>(const Fraction& rhs) const;
        bool operator<(const Fraction& rhs) const;

        int32_t getNum() const {return num;}
        int32_t getDen() const {return den;}
        double get_exact_num() const {return num+dnum;}
        double get_exact_den() const {return den+dden;}
        bool has_dec_num() const {return dnum!=0;}
        bool has_dec_den() const {return dden!=0;}
        bool isNaN() const {return num==0&&dnum==0&&den==0&&dden==0;}
        bool isInfinity() const {return (num!=0||dnum!=0)&&(den==0&&dden==0);}
        bool isPInfinity() const {return (num>0||dnum>0)&&(den==0&&dden==0);}
        bool isNInfinity() const {return (num<0||dnum<0)&&(den==0&&dden==0);}

    private:
        int32_t num;
        int32_t den;
        double dnum;
        double dden;
};

std::ostream& operator<<(std::ostream& out, Fraction fraction);
std::istream& operator>>(std::istream& in, Fraction& fraction);

#endif