#ifndef _SIMPLESTACK_H
#define _SIMPLESTACK_H

#include <stdexcept>

const int STACK_SIZE = 10;
union UItem {
   int iVal;
   double dVal;
};
typedef union UItem StackType;

class Stack {
 public:
  Stack() { count = 0; }
  ~Stack() { }

  void clear() { count = 0; }
  int size() { return count; }
  bool isEmpty() { return count == 0; }

  void push(const StackType &);
  StackType pop();
  StackType peek();

 private:
  StackType
   data[STACK_SIZE];
  int
   count;
};

#endif
