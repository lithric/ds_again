#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <cstdint>

class DisjointSet {
    public:
        DisjointSet(uint32_t);
        ~DisjointSet();

        uint32_t find(uint32_t a);
        void join(uint32_t a, uint32_t b);
    private:
        uint32_t *elements, *rank;
        uint32_t nElements;
};

#endif