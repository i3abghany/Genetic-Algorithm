#include <iostream>
#include "GeneticAlgorithm.hpp"

int main() {
    GeneticAlgorithm::Population::init_genes();
//    for(auto c : GeneticAlgorithm::Population::genes)
//        std::cout << c.get_phrase() << std::endl;
    GeneticAlgorithm::Population::calculate_fitness();
    DNA mx; double max_f = 0.0;
    for(auto &c : GeneticAlgorithm::Population::genes) {
        if(c.get_fitness() > max_f) {
            mx = c, max_f = c.get_fitness();
        }
    }
    std::cout << mx.get_phrase() << ' ' << mx.get_fitness();
    return 0;
}