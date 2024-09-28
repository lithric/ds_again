#include "fraction.h"

constexpr int32_t abs(int32_t n) {return n>=0?n:-n;}
constexpr double abs(double n) {return n>=0?n:-n;}

constexpr int32_t gcd(int32_t n, int32_t m) {
    n = abs(n);
    m = abs(m);

    int32_t n1 = n<m?n:m;
    int32_t n2 = n<m?m:n;

    // n1 <= n2

    int32_t gcd_x1 = n2;
    int32_t gcd_x2 = n1;

    while (gcd_x2!=0) {
        int32_t _temp = gcd_x2;
        gcd_x2 = gcd_x1 % gcd_x2;
        gcd_x1 = _temp;
    }

    return gcd_x1;
}

constexpr void format_int_decimal(int32_t* integer, double* decimal) {
    int32_t n = 0;
    double d = 0.0;
    // remove decimal overflow
    *integer += static_cast<int32_t>(*decimal);
    *decimal -= static_cast<int32_t>(*decimal);
    // decimal is now less than 1 in magnitude

    n = *integer;
    d = *decimal;
    if (d==0||n==0||(n>=1&&d>0)||(n<=-1&&d<0)) return; // decimal is correct
    // integer is now confirmed greater than 1 in magnitude (by being non-zero)
    // decimal is now confirmed a non-zero number

    if (n>=1&&d<0) {
        // decimal needs to be positive
        *integer -= 1;
        *decimal += 1;
        return;
    }
    else if (n<=-1&&d>0) {
        // decimal needs to be negative
        *integer += 1;
        *decimal -= 1;
        return;
    }
}

constexpr void mult_int_decimal(int32_t* integer1, double* decimal1, int32_t integer2, double decimal2) {
    *decimal1 = static_cast<double>(*integer1)*decimal2+
                static_cast<double>(integer2)*(*decimal1)+
                (*decimal1)*decimal2;
    *integer1 *= integer2;
    format_int_decimal(integer1,decimal1);
}

Fraction::Fraction(int32_t _num, int32_t _den, bool simplify) {
    int32_t gcd_n = 0;
    dnum = 0.0;
    dden = 0.0;
    if (_den<0) {_num=-_num;_den=-_den;}
    if (!simplify) {num=_num;den=_den;return;}
    gcd_n = gcd(_num, _den);
    if (gcd_n==0) throw std::logic_error("fraction: 0/0 is not a fraction.");

    num = _num/gcd_n;
    den = _den/gcd_n;
}

Fraction::Fraction(double _num_double, double _den_double, bool simplify) {
    int32_t gcd_n = 0, _num, _den;
    double _dnum, _dden;

    _num = static_cast<int32_t>(_num_double);
    _den = static_cast<int32_t>(_den_double);
    _dnum = _num_double - static_cast<double>(_num);
    _dden = _den_double - static_cast<double>(_den);
    
    format_int_decimal(&_num,&_dnum);
    format_int_decimal(&_den,&_dden);

    if (_den<0||_dden<0) {_num=-_num;_dnum=-_dnum;_den=-_den;_dden=-_dden;}

    if (!simplify) {num=_num;dnum=_dnum;den=_den;dden=_dden;}

    gcd_n = gcd(_num,_den);
    if (gcd_n==0) throw std::logic_error("fraction: 0/0 is not a fraction.");

    num = _num/gcd_n;
    den = _den/gcd_n;
    dnum = _dnum/static_cast<double>(gcd_n);
    dden = _dden/static_cast<double>(gcd_n);
}

Fraction::Fraction(int32_t _num, double _dnum, int32_t _den, double _dden, bool simplify) {
    int32_t gcd_n = 0;
    
    format_int_decimal(&_num,&_dnum);
    format_int_decimal(&_den,&_dden);

    if (_den<0||_dden<0) {_num=-_num;_dnum=-_dnum;_den=-_den;_dden=-_dden;}

    if (!simplify) {num=_num;dnum=_dnum;den=_den;dden=_dden;return;}

    gcd_n = gcd(_num,_den);
    if (gcd_n==0) throw std::logic_error("fraction: 0/0 is not a fraction.");

    num = _num/gcd_n;
    den = _den/gcd_n;
    dnum = _dnum/static_cast<double>(gcd_n);
    dden = _dden/static_cast<double>(gcd_n);
}

const Fraction& Fraction::operator=(const Fraction& rhs) {
    num = rhs.num;
    den = rhs.den;
    dnum = rhs.dnum;
    dden = rhs.dden;
    return rhs;
}

Fraction Fraction::operator+() const {
    return Fraction(num,dnum,den,dden,false);
}

Fraction Fraction::operator+(const Fraction& rhs) const {
    int32_t _num, _den;
    double _dnum, _dden;
    if (isNaN()||rhs.isNaN()) return Fraction(0,0);

    if (isInfinity()||rhs.isInfinity()) {
        if ((isPInfinity()&&rhs.isNInfinity())||
            (isNInfinity()&&rhs.isPInfinity())) return Fraction(0,0);
        if (isPInfinity()&&rhs.isPInfinity()) return Fraction(1,0);
        if (isNInfinity()&&rhs.isNInfinity()) return Fraction(-1,0);
    }

    _num = num*rhs.den+den*rhs.num;
    _dnum = static_cast<double>(num)*rhs.dden+static_cast<double>(rhs.num)*dden+
            static_cast<double>(rhs.den)*dnum+static_cast<double>(den)*rhs.dnum+
            dnum*rhs.dden+rhs.dnum*dden;
    _den = den*rhs.den;
    _dden = static_cast<double>(den)*rhs.dden+
            static_cast<double>(rhs.den)*dden+
            dden*rhs.dden;

    return Fraction(_num,_dnum,_den,_dden);
}

Fraction Fraction::operator-() const {
    return Fraction(-num,-dnum,den,dden,false);
}

Fraction Fraction::operator-(const Fraction& rhs) const {
    int32_t _num, _den;
    double _dnum, _dden;

    _num = num*rhs.den-den*rhs.num;
    _dnum = static_cast<double>(num)*rhs.dden-static_cast<double>(rhs.num)*dden+
            static_cast<double>(rhs.den)*dnum-static_cast<double>(den)*rhs.dnum+
            dnum*rhs.dden-rhs.dnum*dden;
    _den = den*rhs.den;
    _dden = static_cast<double>(den)*rhs.dden+
            static_cast<double>(rhs.den)*dden+
            dden*rhs.dden;

    return Fraction(_num,_dnum,_den,_dden);
}

Fraction Fraction::operator*(const Fraction& rhs) const {
    int32_t _num, _den;
    double _dnum, _dden;
    _num = num;
    _dnum = dnum;
    _den = den;
    _dden = dden;

    mult_int_decimal(&_num,&_dnum,rhs.num,rhs.dnum);
    mult_int_decimal(&_den,&_dden,rhs.den,rhs.dden);

    return Fraction(_num,_dnum,_den,_dden);
}

Fraction Fraction::operator/(const Fraction& rhs) const {
    int32_t _num = num;
    double _dnum = dnum;
    int32_t _den = den;
    double _dden = dden;

    mult_int_decimal(&_num,&_dnum,rhs.den,rhs.dden);
    mult_int_decimal(&_den,&_dden,rhs.num,rhs.dnum);

    return Fraction(_num,_dnum,_den,_dden);
}

Fraction Fraction::operator^(const int32_t& rhs) const {
    int32_t _num, _den;
    double _dnum, _dden, _lnum, _lden;
    if (rhs==0) return Fraction(1,1,false);
    _num = rhs>0?num:den;
    _dnum = rhs>0?dnum:dden;
    _den = rhs>0?den:num;
    _dden = rhs>0?dden:dnum;
    int32_t _rhs = abs(rhs);
    while (_rhs>1) {
        _lnum = _num*dnum+_dnum*num;
        _lden = _den*dden+_dden*den;
        _num = _num*num+std::floor(_lnum);
        _dnum = _dnum*dnum+(_lnum-std::floor(_lnum));
        format_int_decimal(&_num,&_dnum);
        _den = _den*den+std::floor(_lden);
        _dden = _dden*dden+(_lden-std::floor(_lden));
        format_int_decimal(&_den,&_dden);
        _rhs--;
    }
    return Fraction(_num,_dnum,_den,_dden);
}

bool Fraction::operator==(const Fraction& rhs) const {
    return num==rhs.num&&den==rhs.den&&
           dnum==rhs.dnum&&dden==rhs.dden;
}

bool Fraction::operator!=(const Fraction& rhs) const {
    return num!=rhs.num||den!=rhs.den||
           dnum!=rhs.dnum||dden!=rhs.dden;
}

bool Fraction::operator>=(const Fraction& rhs) const {
    if (*this==rhs) return true;
    return (num+dnum)*(rhs.den+rhs.dden)>=(den+dden)*(rhs.num+rhs.dnum);
}

bool Fraction::operator<=(const Fraction& rhs) const {
    if (*this==rhs) return true; // faster
    return (num+dnum)*(rhs.den+rhs.dden)<=(den+dden)*(rhs.num+rhs.dnum);
}

bool Fraction::operator>(const Fraction& rhs) const {
    if (*this==rhs) return false; // faster
    return (num+dnum)*(rhs.den+rhs.dden)>(den+dden)*(rhs.num+rhs.dnum);
}

bool Fraction::operator<(const Fraction& rhs) const {
    if (*this==rhs) return false; // faster
    return (num+dnum)*(rhs.den+rhs.dden)<(den+dden)*(rhs.num+rhs.dnum);
}

std::ostream& operator<<(std::ostream& out, Fraction fraction) {
    if (fraction.has_dec_num()) {
        out << fraction.get_exact_num();
    }
    else {
        out << fraction.getNum(); 
    }
    out << " / ";
    if (fraction.has_dec_den()) {
        out << fraction.get_exact_den();
    }
    else {
        out << fraction.getDen();
    }
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& fraction) {
    int32_t _num=0, _den=1;
    char slash;
    in >> _num >> slash;
    if (slash=='/') in >> _den;
    fraction = Fraction(_num,_den);
    return in;
}