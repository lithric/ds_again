#include <iostream>
#include "fraction.h"
#include "stack.h"

// allows recursion
#define AS_MACRO
// ends recurrsion
#define END_SIGNAL(...)

#define MAP_IS_END_SIGNAL() 0, END_SIGNAL
#define MAP_NEXT0(test_end,next_macro,...) next_macro AS_MACRO
#define MAP_NEXT1(test_end,next_macro) MAP_NEXT0 (test_end, next_macro, 0)
#define MAP_NEXT(test_end,next_macro) MAP_NEXT1 (MAP_IS_END_SIGNAL test_end, next_macro)
#define MAP0(f, x, test_end, args...) f(x)MAP_NEXT(test_end,MAP1) (f, test_end, args)
#define MAP1(f, x, test_end, args...) , f(x)MAP_NEXT(test_end,MAP2) (f, test_end, args)
#define MAP2(f, x, test_end, args...) , f(x)MAP_NEXT(test_end,MAP1) (f, test_end, args)
#define MAP(f,args...) EVAL(MAP0(f,args,()))
#define EVAL0(args...) args
#define EVAL1(args...) EVAL0(EVAL0(EVAL0(args)))
#define EVAL2(args...) EVAL1(EVAL1(EVAL1(args)))
#define EVAL3(args...) EVAL2(EVAL2(EVAL2(args)))
#define EVAL4(args...) EVAL3(EVAL3(EVAL3(args)))
#define EVAL(args...)  EVAL4(EVAL4(EVAL4(args)))

#define SHIFT_NAME(MACRO_NAME,FUNC_MACRO,args...) FUNC_MACRO AS_MACRO (args,MACRO_NAME)
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define FOO(args...) GET_MACRO(args, FOO4, FOO3, FOO2, FOO1)(args)

using namespace std;

template <typename T>
void writing(T text) {
    cout << text;
}
template <typename T>
T reading() {
    T data;
    cin >> data;
    return data;
}

template <typename T>
T clean_reading(T (*func)(T)) {
    T data;
    cin >> data;
    return func(data);
}

#define print(args...) (MAP(writing,args))
#define prompt(type,args...) (MAP(writing,args), reading<type>())
#define func_prompt(type,func,args...) (MAP(writing,args), clean_reading<type>(func))

int main() {
    Stack<Fraction> numStack;
    return 0;
}