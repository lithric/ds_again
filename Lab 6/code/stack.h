#ifndef _STACK_H
#define _STACK_H

#include <stdexcept>

const int STACK_SIZE = 10;

template <class StackType>
class Stack {
 public:
  Stack() { count = 0; }
  ~Stack() { }

  void clear() { count = 0; }
  int size() { return count; }
  bool isEmpty() { return count == 0; }

  void push(const StackType &d) {

    if (count == STACK_SIZE)
      throw std::overflow_error("push: Stack is full");

    data[count] = d;

    count++;
  }

  StackType pop() {

    if (!count)
      throw std::underflow_error("pop: Stack is empty");

    count--;

    return data[count];

  }

  StackType peek() {

    if (!count)
      throw std::underflow_error("peek: Stack is empty");

    return data[count-1];
  }

 private:
  StackType
   data[STACK_SIZE];
  int
   count;
};

#endif
