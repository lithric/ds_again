#include "sampler.h"
#include <stdexcept>

Sampler::Sampler(uint32_t n) {
    elements = new uint32_t[n];
    nElements = n;

    for (uint32_t i=0;i<n;i++) elements[i] = i;
    
    rd = new std::random_device;
    mt = new std::mt19937((*rd)());
}

Sampler::~Sampler() {
    delete mt;
    delete rd;

    delete[] elements;
}

uint32_t Sampler::getSample() {
    uint32_t i,e;
    std::uniform_int_distribution<> dis(0,nElements-1);

    if (nElements==0) throw std::underflow_error("getSample: Sampler is empty");

    i = dis(*mt);

    e = elements[i];

    nElements--;

    elements[i] = elements[nElements];

    return e;
}