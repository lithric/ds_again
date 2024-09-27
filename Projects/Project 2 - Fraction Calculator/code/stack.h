#include <iostream>

#ifndef _STACK_H
#define _STACK_H

template <typename T>
class Stack {
    public:
        Stack();
        Stack(T top);
        Stack(T top, Stack<T>* next);
        ~Stack() = default;

        void push(T);
        T pop();
    private:
        T* top;
        Stack<T>* next;
};

#include "stack.cc"

#endif