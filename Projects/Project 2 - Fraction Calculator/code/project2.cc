#include <iostream>
#include <string>
#include "fraction.h"
#include "stack.h"
#include "dictionary.h"

// allows recursion
#define AS_FUNC_MACRO
// ends recursion
#define END_SIGNAL(...)

#define MAP_IS_END_SIGNAL() 0, END_SIGNAL
#define MAP_NEXT0(test_end,next_macro,...) next_macro AS_FUNC_MACRO
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

#define SHIFT_NAME(MACRO_NAME,FUNC_MACRO,args...) FUNC_MACRO AS_FUNC_MACRO (args,MACRO_NAME)
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
string readln() {
    string data;
    getline(cin,data);
    return data;
}

#define print(args...) (MAP(writing,args))
#define prompt(type,args...) (MAP(writing,args), reading<type>())
#define promptln(args...) (MAP(writing,args), readln())

bool debugging = false;

struct VarNum {
    string varName = "";
    Fraction number = 0;
};

bool hasPrecedence(char lhs, char rhs) {
    switch(lhs) {
        case '*':
        case '/':
            switch(rhs) {
                case '*':
                case '/':
                    return true;
                case '+':
                case '-':
                    return true;
                case '=':
                    return true;
                default: throw std::domain_error("unrecognized operation.");
            }
        case '+':
        case '-':
            switch(rhs) {
                case '*':
                case '/':
                    return false;
                case '+':
                case '-':
                    return true;
                case '=':
                    return true;
                default: throw std::domain_error("unrecognized operation.");
            }
        case '=':
        case '(':
        case '$':
            switch(rhs) {
                case '*':
                case '/':
                    return false;
                case '+':
                case '-':
                    return false;
                case '=':
                    return false;
                default: throw std::domain_error("unrecognized operation.");
            }
        default: throw std::domain_error("unrecognized operation.");
    }
}

bool isDigit(char s) {
    return s>='0'&&s<='9';
}

int32_t convertDigit(char s) {
    return s-'0';
}

bool isLetter(char s) {
    return (s>='a'&&s<='z')||(s>='A'&&s<='Z');
}

bool isOperator(char s) {
    return s=='+'||s=='-'||s=='*'||s=='/'||s=='=';
}

Fraction convertDigitsToFraction(string s,uint32_t start,uint32_t* end) {
    if (start>s.length()) throw std::range_error("start index beyond length while converting digits.");
    Fraction result = s[start]-'0';
    start++;
    while (isDigit(s[start])) {
        result *= 10;
        result += convertDigit(s[start]);
        start++;
    }
    *end = start-1;
    return result;
}

string convertLettersToString(string s,uint32_t start,uint32_t* end) {
    if (start>s.length()) throw std::range_error("start index beyond length while converting letters.");
    string result = "";
    result += s[start];
    start++;
    while (isLetter(s[start])) {
        result += s[start];
        start++;
    }
    *end = start-1;
    return result;
}

Fraction getNumber(VarNum num,Dictionary<string, Fraction>* varDict) {
    if (num.varName=="") {
        return num.number;
    }
    else {
        return varDict->search(num.varName);
    }
}

void performOperation(Stack<VarNum>* numStack, Stack<char>* opStack, Dictionary<string,Fraction>* varDict) {
    char op = opStack->pop();
    VarNum rhs = numStack->pop();
    VarNum lhs = numStack->pop();
    switch(op) {
        case '+': {
            numStack->push(VarNum { .number = getNumber(lhs,varDict)+getNumber(rhs,varDict) });
            break;
        }
        case '-': {
            numStack->push(VarNum { .number = getNumber(lhs,varDict)-getNumber(rhs,varDict) });
            break;
        }
        case '*': {
            numStack->push(VarNum { .number = getNumber(lhs,varDict)*getNumber(rhs,varDict) });
            break;
        }
        case '/': {
            numStack->push(VarNum { .number = getNumber(lhs,varDict)/getNumber(rhs,varDict) });
            break;
        }
        case '=': {
            if (lhs.varName=="") throw std::domain_error("calc: operation (=): left hand side does not have variable name.");
            numStack->push(VarNum { .number = getNumber(rhs,varDict) });
            varDict->insert(lhs.varName,getNumber(rhs,varDict));
            break;
        }
        default: {
            throw std::domain_error("calc: operation (?): operation symbol not found.");
        }
    }
    return;
}

Fraction evaluate(string s,Stack<VarNum>* numStack, Stack<char>* opStack, Dictionary<string,Fraction>* varDict) {
    uint32_t digitsEnd = 0;
    uint32_t lettersEnd = 0;
    numStack->clear();
    opStack->clear();
    opStack->push('$');
    uint32_t first = 0;

    while (first<s.length()) {
        if (isDigit(s[first])) {
            Fraction number = convertDigitsToFraction(s,first,&digitsEnd);
            numStack->push(VarNum {.number = number});
            if (debugging) print("[",numStack->peek().number,"]","\n");
            first = digitsEnd+1;
        } 
        else if (isLetter(s[first])) {
            string varName = convertLettersToString(s,first,&lettersEnd);
            numStack->push(VarNum {.varName = varName});
            if (debugging) print("[",numStack->peek().varName,"]","\n");
            first = lettersEnd+1;
        } 
        else if (s[first]=='(') {
            opStack->push('(');
            if (debugging) print(opStack->peek(),"\n");
            first++;
        } 
        else if (s[first]==')') {
            while (opStack->peek()!='(') {
                if (!debugging) performOperation(numStack,opStack,varDict);
                if (debugging) opStack->pop();
            }
            char _temp = opStack->pop();
            if (debugging) print(_temp,"\n");
            first++;
        } 
        else if (isOperator(s[first])) {
            if (!debugging) while (hasPrecedence(opStack->peek(),s[first])) {
                performOperation(numStack,opStack,varDict);
            }
            opStack->push(s[first]);
            if (debugging) print(opStack->peek(),"\n");
            first++;
        } 
        else {
            first++;
        }
    }

    if (!debugging) while (opStack->peek()!='$') {
        performOperation(numStack,opStack,varDict);
    }

    if (!debugging) if (numStack->size()>1||opStack->size()>1) throw std::domain_error("calc: malformed input");

    return getNumber(numStack->peek(),varDict);
}

int main(int argc, const char* argv[]) {
    string userInput = "";
    Stack<VarNum> numStack;
    Stack<char> opStack;
    Dictionary<string,Fraction> varDict;

    if (argc>1&&argv[1][0]=='-'&&argv[1][1]=='t') debugging = true;

    while (userInput!="#") {
        string userInput = promptln("calc: ");
        if (userInput == "#") break;
        try {
            Fraction result = evaluate(userInput,&numStack,&opStack,&varDict);
            if (!debugging) print(result,"\n");
        }
        catch (const range_error& ex) {
            print(ex.what(),"\n");
        }
        catch (const domain_error& ex) {
            print(ex.what(),"\n");
        }
        catch (const logic_error& ex) {
            print(ex.what(),"\n");
        }
        catch (const overflow_error& ex) {
            print(ex.what(),"\n");
        }
        catch (const underflow_error& ex) {
            print(ex.what(),"\n");
        }
        catch (...) {
            print("Error has been caught","\n");
        }
    }

    print("\n");

    return 0;
}