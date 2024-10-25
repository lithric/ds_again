#ifndef _STACK_H
#define _STACK_H

#include <stdexcept>
#include <cstdint>

using namespace std;

const uint32_t
    STACK_SIZE = 16;
  
template <typename StackType>
class Stack {
public:
    Stack() { 
        data = new StackType[STACK_SIZE];
        capacity = STACK_SIZE;
        count = 0;
    }

    ~Stack() { delete[] data; }

    void clear() { count = 0; }

    uint32_t size() { return count; }

    bool isEmpty() { return count == 0; }
  

    void push(const StackType &d) {
  
        if (count == capacity) {
            uint32_t tmpCap = 2 * capacity;
            StackType *tmpData = new StackType[tmpCap];
            if (tmpData == nullptr)
                throw overflow_error("Stack is full");
            for (uint32_t i=0;i<capacity;i++) tmpData[i]=data[i];
            delete[] data;
            data = tmpData;
            capacity = tmpCap;
        }
      
        data[count++] = d;
    }
  
    StackType pop() {

        if (count == 0)
            throw underflow_error("Stack is empty");
      
        return data[--count];
    }
    
    StackType peek() {
  
        if (count == 0)
            throw underflow_error("Stack is empty");
      
        return data[count-1];
    }
  
private:
    StackType
        *data;
    
    uint32_t
        count,
        capacity;
};

#endif

