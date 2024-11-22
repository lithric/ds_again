#ifndef __MACROLIB_H
#define __MACROLIB_H

// allows recursion
#define AS_PLAIN
#define TO_PLAIN(macro) macro AS_PLAIN
// ends recursion
#define END_SIGNAL(...)
#define MACRO_FALSE (),
#define MACRO_TRUE ,
#define YIELD_MACRO_TRUE() MACRO_TRUE
#define YIELD_MACRO_FALSE() MACRO_FALSE

#define REVAL(args...) args
#define REVAL4(args...) REVAL(REVAL(REVAL(args)))
#define REVAL13(args...) REVAL4(REVAL4(REVAL4(args)))
#define REVAL40(args...) REVAL13(REVAL13(REVAL13(args)))
#define REVAL121(args...) REVAL40(REVAL40(REVAL40(args)))
// max iterations: 364
#define LOOP_REVAL(args...) REVAL121(REVAL121(REVAL121(args)))

#define SWAP0(garbage,macro1,macro2,...) macro1,macro2
#define SWAP(test,macro1,macro2) REVAL(SWAP0 AS_PLAIN (YIELD_MACRO_TRUE test macro1,macro2,macro1))

#define MACRO_IF0(macro_result,...) macro_result
#define MACRO_IF(test,on_true,on_false) REVAL(MACRO_IF0 AS_PLAIN (SWAP(test,on_false,on_true)))

#define MAP0(f,test,args...) f(test) MACRO_IF(test,MAP1,END_SIGNAL) (f,args)
#define MAP1(f,test,args...) f(test) MACRO_IF(test,MAP0,END_SIGNAL) (f,args)
#define MAP(f,args...) MAP0(f,args,())

#endif