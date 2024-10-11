#include <iostream>
#include "simpleStack.h"

using namespace std;

int main() {
  StackType digit;
  int x,d;

  Stack myStack;

  cout << "Enter a number: ";
  cin >> x;

  while (x != 0) {
    d = x % 10;
    x /= 10;

    digit.iVal = d;
    myStack.push(digit);
  }


  while (!myStack.isEmpty()) {
    digit = myStack.pop();
    cout << digit.iVal << endl;
  }

  return 0;
}
