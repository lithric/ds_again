#include "dictionary.h"
#include <stdexcept>

template <typename KeyType, typename ValueType>
void Dictionary<KeyType,ValueType>::insert(const KeyType &k,ValueType v) {
    for (uint32_t i=0;i<nItems;i++) {
        if (keys[i]==k) {
            values[i]=v;
            return;
        }
    }
    if (nItems==MAX_ITEMS) throw std::overflow_error("insert: Dictionary is full.");
    keys[nItems] = k;
    values[nItems] = v;
    nItems++;
}

template <typename KeyType, typename ValueType>
void Dictionary<KeyType,ValueType>::remove(const KeyType &k) {
    for (uint32_t i=0;i<nItems;i++) {
        if (keys[i]==k) {
            nItems--;
            keys[i] = keys[nItems];
            values[i] = keys[nItems];
            return;
        }
    }
    throw std::domain_error("remove: Key not found.");
}

template <typename KeyType, typename ValueType>
constexpr ValueType Dictionary<KeyType,ValueType>::search(const KeyType &k) const {
    for (uint32_t i=0;i<nItems;i++) if (keys[i]==k) return values[i];
    throw std::domain_error("search: Key not found.");
}