#ifndef __MACROLIB_H
#define __MACROLIB_H

// function-like macros are evaluated ONCE during pre-processing.
// they are evaluated IMMEDIATELY from left to right.
// the pre-processor skips the text inserted by the macro and continues pre-processing.
// parameters of function-like macros are evaluated ONCE and IMMEDIATELY BEFORE the macro is evaluated.
// evaluating all function-like macros DOES NOT end pre-processing.

// plain text macros are evaluated ONCE during pre-processing.
// they are evaluated IMMEDIATELY from left to right.
// Once all plain text macros are evaluated, pre-processing ends.

#define AS_PLAIN
#define REVAL(args...) args
#define CF_SLICE_1(_0,args...) args
#define CF_SLICE_2(args...) CF_SLICE_1 AS_PLAIN (CF_SLICE_1(args)) 
CF_SLICE_2(1,REVAL(REVAL AS_PLAIN (12)),3,4)

#define CF_0(macro,...) macro
#define CF_1(_0,macro,...) macro
#define CF_2(args...) CF_1(args)
#define MACRO_TRUE ,
#define MACRO_FALSE ,,
#define CF_EVAL(cf,...) cf
#define MACRO_IF(cf,...) cf
// ends recursion
#define END_SIGNAL(...)
#define YIELD_MACRO_TRUE() MACRO_TRUE
#define YIELD_MACRO_FALSE() MACRO_FALSE
#define REVAL4(args...) REVAL(REVAL(REVAL(args)))
#define REVAL13(args...) REVAL4(REVAL4(REVAL4(args)))
#define REVAL40(args...) REVAL13(REVAL13(REVAL13(args)))
#define REVAL121(args...) REVAL40(REVAL40(REVAL40(args)))
// max iterations: 364
#define LOOP_REVAL(args...) REVAL121(REVAL121(REVAL121(args)))

// #define SWAP0(garbage,macro1,macro2,...) macro1,macro2
// #define SWAP(test,macro1,macro2) REVAL(SWAP0 AS_PLAIN (YIELD_MACRO_TRUE test macro1,macro2,macro1))

// #define MACRO_IF0(macro_result,...) macro_result
// #define MACRO_IF(test,on_true,on_false) REVAL(MACRO_IF0 AS_PLAIN (SWAP(test,on_false,on_true)))

#define MAP_IS_END_SIGNAL() 0, END_SIGNAL
#define MAP_NEXT0(test_end,next_macro,...) next_macro AS_PLAIN
#define MAP_NEXT1(test_end,next_macro) MAP_NEXT0 (test_end, next_macro, 0)
#define MAP_NEXT(test_end,next_macro) MAP_NEXT1 (MAP_IS_END_SIGNAL test_end, next_macro)
#define MAP0(f, x, test_end, args...) f(x)MAP_NEXT(test_end,MAP1) (f, test_end, args)
#define MAP1(f, x, test_end, args...) , f(x)MAP_NEXT(test_end,MAP2) (f, test_end, args)
#define MAP2(f, x, test_end, args...) , f(x)MAP_NEXT(test_end,MAP1) (f, test_end, args)
#define MAP(f,args...) LOOP_REVAL(MAP0(f,args,()))

// #define MAP0(f,test,args...) f(test) MACRO_IF(test,MAP1,END_SIGNAL) (f,args)
// #define MAP1(f,test,args...) f(test) MACRO_IF(test,MAP0,END_SIGNAL) (f,args)
// #define MAP(f,args...) MAP0(f,args,())

#endif