#ifndef GENETIC_ALGORITHM_GENETICALGORITHM_HPP
#define GENETIC_ALGORITHM_GENETICALGORITHM_HPP

#include <vector>
#include <random>
#include "DNA.hpp"

namespace GeneticAlgorithm {


    static double mutation_rate = 0.01;
    static std::size_t population_count = 200;
    static std::string target_phrase;
    static std::size_t phrase_length = target_phrase.length();

    namespace Population {
        static std::vector<DNA> genes;

        std::string random_phrase();

        void init_genes();
    }



}

#endif //GENETIC_ALGORITHM_GENETICALGORITHM_HPP
