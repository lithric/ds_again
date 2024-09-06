#include <iostream>
#include <cmath>

#ifndef __FRACTION_H__
#define __FRACTION_H__

class Fraction {
    public:
        Fraction(int _num=0, int _den=1, bool simplify=true);
        Fraction(double _num, double _den=1, bool simplify=true);
        Fraction(int _num, double _fnum, int _den, double _fden, bool simplify=true);
        ~Fraction() = default;

        Fraction operator-();
        Fraction operator-(Fraction rhs);
        Fraction operator+();
        Fraction operator+(Fraction rhs);
        Fraction operator*(Fraction rhs);
        Fraction operator/(Fraction rhs);
        Fraction operator^(int rhs);

        bool operator==(Fraction rhs);
        bool operator!=(Fraction rhs);
        bool operator>=(Fraction rhs);
        bool operator<=(Fraction rhs);
        bool operator>(Fraction rhs);
        bool operator<(Fraction rhs);

        int get_num() {return this->num;};
        int get_den() {return this->den;};
        double get_exact_num() {return this->num+this->fnum;};
        double get_exact_den() {return this->den+this->fden;};
        bool has_dec_num() {return this->fnum!=0;};
        bool has_dec_den() {return this->fden!=0;};

    private:
        int num = 0;
        int den = 1;
        double fnum = 0.0;
        double fden = 0.0;
};

std::ostream& operator<<(std::ostream& out, Fraction& fraction);
std::istream& operator>>(std::istream& in, Fraction fraction);

#endif