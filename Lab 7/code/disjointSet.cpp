#include "disjointSet.h"
#include <stdexcept>

DisjointSet::DisjointSet(uint32_t n) {
    elements = new uint32_t[n];
    rank = new uint32_t[n];
    nElements = n;
    
    for (uint32_t i=0;i<nElements;i++) {
        elements[i] = i;
        rank[i]=0;
    }
}

DisjointSet::~DisjointSet() {
    delete[] elements;
    delete[] rank;
}

uint32_t DisjointSet::find(uint32_t a) {
    if (a>=nElements) throw std::domain_error("find: Index outside domain");
    if (elements[a]!=a) {
        elements[a]=find(elements[a]);
    }
    return elements[a];
}

void DisjointSet::join(uint32_t a, uint32_t b) {
    a = find(a);
    b = find(b);

    if (a==b) return;
    if (rank[a]<rank[b]) {
        elements[a] = b;
        return;
    }
    if (rank[a]==rank[b]) {
        rank[a]++;
    }
    elements[b] = a;
}