#include "stack.h"

// empty stack
template <typename T>
Stack<T>::Stack() {
    top = nullptr;
    next = nullptr;
}

// length 1 stack
template <typename T>
Stack<T>::Stack(T _top) {
    *top = _top;
    *next = Stack<T>();
}

// arbitrary length stack
template <typename T>
Stack<T>::Stack(T _top, Stack<T> _next) {
    *top = _top;
    *next = _next;
}

template <typename T>
void Stack<T>::push(T rhs) {
    if (top==nullptr) { // empty stack
        next = Stack<T>();
        *top = rhs;
        return;
    }
    else {
        next = Stack<T>(*top,next);
        *top = rhs;
        return;
    }
}

template <typename T>
T Stack<T>::pop() {
    if (top==nullptr) { // empty stack
        throw "tried to remove from empty stack";
    }
    else {
        T data = *top;
        top = *next.top;
        next = *next.next;
        return data;
    }
}