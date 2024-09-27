#include "unsortedDictionary.h"
#include <stdexcept>

void UnsortedDictionary::insert(const std::string &k, Fraction f) {
    for (uint32_t i=0;i<nItems;i++) {
        if (keys[i]==k) {
            values[i] = f;
            return;
        }
    }
    if (nItems==MAX_ITEMS) throw std::overflow_error("insert: Dictionary is full.");
    keys[nItems] = k;
    values[nItems] = f;
    nItems++;
}

void UnsortedDictionary::remove(const std::string &k) {
    for (uint32_t i=0;i<nItems;i++) {
        if (keys[i]==k) {
            nItems--;
            keys[i] = keys[nItems];
            values[i] = values[nItems];
            // messy removal as the order does not matter
            return;
        }
    }

    throw std::domain_error("remove: Key not found.");
}

Fraction UnsortedDictionary::search(const std::string &k) {
    for (uint32_t i=0;i<nItems;i++) {
        if (keys[i]==k) return values[i];
    }

    throw std::domain_error("search: Key not found.");
}