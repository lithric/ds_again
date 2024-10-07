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
        uint32_t size() const {
            uint32_t count = 0;
            Stack<T>* q = next;
            while (q!=nullptr) {
                q = q->next;
                count++;
            }
            return count;
        }

        void clear() {while (!isEmpty()) pop();}

        void push(T);
        T pop();

        T getTop() const {
            if (isEmpty()) throw std::underflow_error("getTop: Nothing to return. Stack empty.");
            return *top;
        }
        Stack<T> getNext() const {
            if (isEmpty()) throw std::underflow_error("getNext: Nothing to return. Stack empty.");
            return *next;
        }

    private:
        T* top;
        Stack<T>* next;
};

#include "stack.cc"

#endif