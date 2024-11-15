#ifndef SAMPLER_H
#define SAMPLER_H

#include <cstdint>
#include <random>

class Sampler {
    public:
        Sampler(uint32_t);
        ~Sampler();

        uint32_t getSample();
    private:
        uint32_t nElements,*elements;
        std::random_device* rd;
        std::mt19937* mt;
};

#endif