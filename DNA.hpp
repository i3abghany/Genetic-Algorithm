#ifndef GENETIC_ALGORITHM_DNA_HPP
#define GENETIC_ALGORITHM_DNA_HPP

#include <string>
#include "GeneticAlgorithm.hpp"

namespace GeneticAlgorithm {

    class DNA {
        std::string phrase;
        double fitness;
    public:
        DNA() = default;
        explicit DNA(std::string ph, double f = 0.0)
            : phrase(std::move(ph)), fitness(f) {}

        // calculates fitness with respect to the given phrase ph.
        void calculate_fitness(const std::string &ph);
    };
}


void GeneticAlgorithm::DNA::calculate_fitness(const std::string &ph) {
    
}

#endif //GENETIC_ALGORITHM_DNA_HPP
