#ifndef _UNSORTEDDICTIONARY_H
#define _UNSORTEDDICTIONARY_H
#include <cstdint>
#include <string>
#include "fraction.h"

const uint32_t MAX_ITEMS = 100;

class UnsortedDictionary {
    public:
        UnsortedDictionary() {nItems=0;};
        ~UnsortedDictionary() = default;

        bool isEmpty() {return nItems == 0;}
        uint32_t size() {return nItems;}
        
        void clear() {nItems = 0;}

        void insert(const std::string &k, Fraction f);
        void remove(const std::string &k);

        Fraction search(const std::string &k);

    private:
        Fraction values[MAX_ITEMS]; // array of values (fractions)
        std::string keys[MAX_ITEMS]; // array of keys (strings)
        uint32_t nItems; // number of items
};

#endif