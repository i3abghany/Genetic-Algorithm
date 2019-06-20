#include "GeneticAlgorithm.hpp"

void GeneticAlgorithm::Population::init_genes() {
    Population::genes.resize(GeneticAlgorithm::population_count);
    for(auto &gene : Population::genes) {
        gene = DNA{random_phrase()};
    }
}

std::string GeneticAlgorithm::Population::random_phrase() {
    std::string res;
    std::random_device        rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution distr(65, 122);
    for(int i = 0; i < GeneticAlgorithm::phrase_length; i++) {
        char c = static_cast<char>(distr(generator));
        if(c == 95 || c == 96 || c == 94) {
            c = ' ';
        }
        res += c;
    }
    return res;
}