#include "stack.h"
#include <stdexcept>
#include <iostream>

// initialize empty stack
template <typename T>
Stack<T>::Stack() {
    top = nullptr;
    next = nullptr;
    u_size = 0;
}

template <typename T>
void Stack<T>::push(T rhs) {
    if (next==nullptr) { // empty stack
        top = new T;
        next = new Stack<T>();
        *top = rhs;
        u_size++;
        return;
    }
    Stack<T>* _temp_next = next;
    T* _temp_top = top;
    next = new Stack<T>();
    top = new T;
    next->top = _temp_top;
    next->next = _temp_next;
    *top = rhs;
    u_size++;
}

template <typename T>
T Stack<T>::pop() {
    if (next==nullptr) throw std::underflow_error("pop: Stack is empty.");
    T data = *top;

    // data to be deleted/removed from the stack
    T* pt_top_del = top;
    Stack<T>* pt_next_del = next;

    top = next->top;
    next = next->next;
    delete pt_top_del; // free dangling ptr holding unreferenced T data
    pt_next_del->top = nullptr;
    pt_next_del->next = nullptr;
    delete pt_next_del; // free dangling ptr holding unreferenced Stack<T> data
    u_size--;
    return data;
}