#include <iostream>
#include "zenStack.h"

using namespace std;

int main() {
  int x,d;

  ZenStack myStack(sizeof(int));

  cout << "Enter a number: ";
  cin >> x;

  while (x != 0) {
    d = x % 10;
    x /= 10;

    myStack.push(&d);
  }


  while (!myStack.isEmpty()) {
    myStack.pop(&d);
    cout << d << endl;
  }

  return 0;
}
