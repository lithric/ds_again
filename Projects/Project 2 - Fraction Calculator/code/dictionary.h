#ifndef _DICTIONARY_H
#define _DICTIONARY_H
#include <cstdint>

const uint32_t MAX_ITEMS = 100;

template <typename KeyType, typename ValueType>
class Dictionary {
    public:
        Dictionary(){nItems=0;};
        ~Dictionary() = default;

        bool isEmpty() {return nItems==0;}
        uint32_t size() {return nItems;}
        
        void clear() {nItems=0;}

        void insert(const KeyType &k, ValueType v);
        void remove(const KeyType &k);

        ValueType search(const KeyType &k);
    private:
        ValueType values[MAX_ITEMS]; // array of values
        KeyType keys[MAX_ITEMS]; // array of keys
        uint32_t nItems; // number of items
        // key is like a pointer address to the values
        // supplying a dictionary with a key will directly get the value
        // KeyType
};

#include "dictionary.cc"

#endif