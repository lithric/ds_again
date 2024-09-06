#include "fraction.h"

int abs(int n) {
    return n>0?n:-n;
}
double abs(double n) {
    return n>0?n:-n;
}

int gcd(int n, int m) {
    int n1,n2,gcd_x1,gcd_x2,_temp;
    n = abs(n);
    m = abs(m);

    n1 = n<m?n:m;
    n2 = n<m?m:n;

    // n1 <= n2

    gcd_x1 = n2;
    gcd_x2 = n1;

    while (gcd_x2!=0) {
        _temp = gcd_x2;
        gcd_x2 = gcd_x1 % gcd_x2;
        gcd_x1 = _temp;
    }

    return gcd_x1;
}

void reval(int* integer, double* decimal) {
    int n,d;
    n = *integer;
    d = *decimal;
    if (n>=0&&d>=0) {
        *integer += std::floor(d);
        *decimal -= std::floor(d);
    }
    else if (n>=1&&d<0) {
        *integer += std::ceil(d)-1;
        *decimal -= std::ceil(d)-1;
    }
    else if (n<0&&d<=-1) {
        *integer += std::ceil(d);
        *decimal -= std::ceil(d);
    }
    else if (n<0&&d>0) {
        *integer += std::floor(d)+1;
        *decimal -= std::floor(d)+1;
    }
}

void mult_vals(int* integer1, double* decimal1, int integer2, double decimal2) {
    *decimal1 = static_cast<double>(*integer1)*decimal2+
                static_cast<double>(integer2)**decimal1+
                *decimal1*decimal2;
    *integer1 = *integer1*integer2;
    reval(integer1,decimal1);
}

Fraction::Fraction(int _num, int _den, bool simplify) {
    int gcd_n;
    fnum = 0.0;
    fden = 0.0;
    if (_den<0) {_num=-_num;_den=-_den;}
    if (!simplify) {num=_num;den=_den;return;}
    gcd_n = gcd(_num, _den);

    num = _num/gcd_n;
    den = _den/gcd_n;
}

Fraction::Fraction(double _num_float, double _den_float, bool simplify) {
    int gcd_n, _num, _den;
    double _fnum, _fden;

    _num = static_cast<int>(_num_float);
    _den = static_cast<int>(_den_float);
    _fnum = _num_float - static_cast<double>(_num);
    _fden = _den_float - static_cast<double>(_den);
    
    reval(&_num,&_fnum);
    reval(&_den,&_fden);

    if (_den<0||_fden<0) {_num=-_num;_fnum=-_fnum;}

    if (!simplify) {num=_num;fnum=_fnum;den=_den;fden=_fden;}

    gcd_n = gcd(_num,_den);

    num = _num/gcd_n;
    den = _den/gcd_n;
    fnum = _fnum/static_cast<double>(gcd_n);
    fden = _fden/static_cast<double>(gcd_n);
}

Fraction::Fraction(int _num, double _fnum, int _den, double _fden, bool simplify) {
    int gcd_n;
    
    reval(&_num,&_fnum);
    reval(&_den,&_fden);

    if (_den<0||_fden<0) {_num=-_num;_fnum=-_fnum;}

    if (!simplify) {num=_num;fnum=_fnum;den=_den;fden=_fden;return;}

    gcd_n = gcd(_num,_den);

    num = _num/gcd_n;
    den = _den/gcd_n;
    fnum = _fnum/static_cast<double>(gcd_n);
    fden = _fden/static_cast<double>(gcd_n);
}

Fraction Fraction::operator+() {
    return Fraction(num,fnum,den,fden,false);
}

Fraction Fraction::operator+(Fraction rhs) {
    int _num, _den;
    double _fnum, _fden;

    _num = num*rhs.den+rhs.num*den;
    _fnum = num*rhs.fden+rhs.num*fden+
            rhs.den*fnum+den*rhs.fnum+
            fnum*rhs.fden+rhs.fnum*fden;
    _den = den*rhs.den;
    _fden = den*rhs.fden+rhs.den*fden+fden*rhs.fden;

    return Fraction(_num,_fnum,_den,_fden);
}

Fraction Fraction::operator-() {
    return Fraction(-num,-fnum,den,fden,false);
}

Fraction Fraction::operator-(Fraction rhs) {
    int _num, _den;
    double _fnum, _fden;

    _num = num*rhs.den-rhs.num*den;
    _fnum = static_cast<double>(num)*rhs.fden-static_cast<double>(rhs.num)*fden+
            static_cast<double>(rhs.den)*fnum-static_cast<double>(den)*rhs.fnum+
            fnum*rhs.fden-rhs.fnum*fden;
    _den = den*rhs.den;
    _fden = static_cast<double>(den)*rhs.fden+
            static_cast<double>(rhs.den)*fden+
            fden*rhs.fden;

    return Fraction(_num,_fnum,_den,_fden);
}

Fraction Fraction::operator*(Fraction rhs) {
    int _num, _den;
    double _fnum, _fden;
    _num = num;
    _fnum = fnum;
    _den = den;
    _fden = fden;

    mult_vals(&_num,&_fnum,rhs.num,rhs.fnum);
    mult_vals(&_den,&_fden,rhs.den,rhs.fden);

    return Fraction(_num,_fnum,_den,_fden);
}

Fraction Fraction::operator/(Fraction rhs) {
    int _num, _den;
    double _fnum, _fden;
    _num = num;
    _fnum = fnum;
    _den = den;
    _fden = fden;

    mult_vals(&_num,&_fnum,rhs.den,rhs.fden);
    mult_vals(&_den,&_fden,rhs.num,rhs.fnum);

    return Fraction(_num,_fnum,_den,_fden);
}

Fraction Fraction::operator^(int rhs) {
    int _num, _den;
    double _fnum, _fden, _lnum, _lden;
    if (rhs==0) return Fraction(1,1,false);
    _num = rhs>0?num:den;
    _fnum = rhs>0?fnum:fden;
    _den = rhs>0?den:num;
    _fden = rhs>0?fden:fnum;
    rhs = abs(rhs);
    while (rhs>1) {
        _lnum = _num*fnum+_fnum*num;
        _lden = _den*fden+_fden*den;
        _num = _num*num+std::floor(_lnum);
        _fnum = _fnum*fnum+(_lnum-std::floor(_lnum));
        reval(&_num,&_fnum);
        _den = _den*den+std::floor(_lden);
        _fden = _fden*fden+(_lden-std::floor(_lden));
        reval(&_den,&_fden);
        rhs--;
    }
    return Fraction(_num,_fnum,_den,_fden);
}

bool Fraction::operator==(Fraction rhs) {
    return num==rhs.num&&den==rhs.den&&
           fnum==rhs.fnum&&fden==rhs.fden;
}

bool Fraction::operator!=(Fraction rhs) {
    return num!=rhs.num||den!=rhs.den||
           fnum!=rhs.fnum||fden!=rhs.fden;
}

bool Fraction::operator>=(Fraction rhs) {
    if (*this==rhs) return true;
    return (num+fnum)*(rhs.den+rhs.fden)>=(den+fden)*(rhs.num+rhs.fnum);
}

bool Fraction::operator<=(Fraction rhs) {
    if (*this==rhs) return true; // faster
    return (num+fnum)*(rhs.den+rhs.fden)<=(den+fden)*(rhs.num+rhs.fnum);
}

bool Fraction::operator>(Fraction rhs) {
    if (*this==rhs) return false; // faster
    return (num+fnum)*(rhs.den+rhs.fden)>(den+fden)*(rhs.num+rhs.fnum);
}

bool Fraction::operator<(Fraction rhs) {
    if (*this==rhs) return false; // faster
    return (num+fnum)*(rhs.den+rhs.fden)<(den+fden)*(rhs.num+rhs.fnum);
}

std::ostream& operator<<(std::ostream& out, Fraction& fraction) {
    if (fraction.has_dec_num()) {
        out << fraction.get_exact_num();
    }
    else {
        out << fraction.get_num(); 
    }
    out << "/";
    if (fraction.has_dec_den()) {
        out << fraction.get_exact_den();
    }
    else {
        out << fraction.get_den();
    }
    return out;
}

std::istream& operator>>(std::istream& in, Fraction fraction) {
    int _num, _den;
    char delimiter;
    in >> _num >> delimiter >> _den;
    fraction = Fraction(_num,_den);
    return in;
}