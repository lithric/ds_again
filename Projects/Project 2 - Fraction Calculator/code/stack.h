#ifndef _STACK_H
#define _STACK_H
#include <cstdint>
#include <iostream>

template <typename T>
class Stack {
    public:
        Stack();
        ~Stack() {
            if (next!=nullptr) {
                delete top;
                delete next; // calls destructor for subsequent stacks
            }
        }

        bool isEmpty() const {return next==nullptr;}

        void clear() {while (!isEmpty()) pop();}

        void push(T);
        T pop();
        uint32_t size() const {return u_size;}

        T peek() const {
            if (isEmpty()) throw std::underflow_error("peek: Nothing to return. Stack empty.");
            return *top;
        }
        Stack<T> getNext() const {
            if (isEmpty()) throw std::underflow_error("getNext: Nothing to return. Stack empty.");
            return *next;
        }

    private:
        T* top;
        Stack<T>* next;
        uint32_t u_size;
};

#include "stack.cc"

#endif