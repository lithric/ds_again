#include <iostream>

using namespace std;

void showBits(unsigned int n) {
    for (int i=31;i>=0;i--) cout << (n & (1 << i) ? '1':'0');
}

int countBits(unsigned int n) {
    int count=0;

    while (n != 0) {
        count++;
        n &= n - 1;
    }

    return count;
}

int main(void) {
    unsigned int a,b,c;

    cout << "Enter two non-negative integers: ";
    cin >> a >> b;
    cout << endl;

    cout << "Bits in 'a': " << countBits(a) << endl;
    cout << "Bits in 'b': " << countBits(b) << endl;
    cout << endl;

    
    c = a;
    cout << "a: " << c << endl;
    showBits(c);
    cout << endl << endl;
    
    c = b;
    cout << "b: " << c << endl;
    showBits(c);
    cout << endl << endl;
    
    c = (a & b);
    cout << "a & b : " << c << endl;
    cout << "'a'   : ";
    showBits(a);
    cout << endl;
    cout << "'b'   : ";
    showBits(b);
    cout << endl;
    cout << "Result: ";
    showBits(c);
    cout << endl << endl;

    
    c = (a | b);
    cout << "a | b : " << c << endl;
    cout << "'a'   : ";
    showBits(a);
    cout << endl;
    cout << "'b'   : ";
    showBits(b);
    cout << endl;
    cout << "Result: ";
    showBits(c);
    cout << endl << endl;
    
    c = ~a;
    cout << "~a    : " << c << endl;
    cout << "'a'   : ";
    showBits(a);
    cout << endl;
    cout << "Result: ";
    showBits(c);
    cout << endl << endl;
    
    c = ~b;
    cout << "~b    : " << c << endl;
    cout << "'b'   : ";
    showBits(b);
    cout << endl;
    cout << "Result: ";
    showBits(c);
    cout << endl << endl;
    
    c = (a ^ b);
    cout << "a ^ b : " << c << endl;
    cout << "'a'   : ";
    showBits(a);
    cout << endl;
    cout << "'b'   : ";
    showBits(b);
    cout << endl;
    cout << "Result: ";
    showBits(c);
    cout << endl << endl;

    c = a << b;
    cout << "a << b: " << c << endl;
    cout << "'a'   : ";
    showBits(a);
    cout << endl;
    cout << "'b'   : ";
    showBits(b);
    cout << endl;
    cout << "Result: ";
    showBits(c);
    cout << endl << endl;

    c = a >> b;
    cout << "a >> b: " << c << endl;
    cout << "'a'   : ";
    showBits(a);
    cout << endl;
    cout << "'b'   : ";
    showBits(b);
    cout << endl;
    cout << "Result: ";
    showBits(c);
    cout << endl << endl;

    return 0;
}