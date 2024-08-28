#ifndef __FRACTION_H__
#define __FRACTION_H__

class Fraction {
    public:
        Fraction(int _num=0, int _den=1);
        ~Fraction() = default;

        Fraction operator-(Fraction rhs);
        Fraction operator+(Fraction rhs);
    private:
        int num;
        int den;
};

#endif