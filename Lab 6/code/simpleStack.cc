#include "simpleStack.h"

void Stack::push(const StackType &d) {

  if (count == STACK_SIZE)
    throw std::overflow_error("push: SimpleStack is full");

  data[count] = d;

  count++;

// data[count++] = d;
}

StackType Stack::pop() {

  if (!count)
    throw std::underflow_error("pop: SimpleStack is empty");

  count--;

  return data[count];

// return data[--count];
}

StackType Stack::peek() {

  if (!count)
    throw std::underflow_error("peek: SimpleStack is empty");

  return data[count-1];
}
