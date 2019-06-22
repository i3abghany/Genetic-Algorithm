#include <iostream>
#include <fstream>
#include "GeneticAlgorithm.hpp"

int main() {
    auto &av = GeneticAlgorithm::Population::genes;
    auto &muv = GeneticAlgorithm::Population::mating_pool;
    GeneticAlgorithm::Population::init_genes();
    GeneticAlgorithm::Population::calculate_fitness();
    DNA mx; double max_f = 0.0;
    std::ofstream g;
    g.open("../results.txt");
    for(int i = 0; i < 1000; i++) {
        GeneticAlgorithm::natural_selection();
        GeneticAlgorithm::new_generation();
        GeneticAlgorithm::Population::calculate_fitness();
        auto d = GeneticAlgorithm::Population::get_best_fit();
        g << GeneticAlgorithm::generations << " "<< d->get_phrase() << ' ' << d->get_fitness() << std::endl;
        if(d->get_phrase() == GeneticAlgorithm::target_phrase) {
            break;
        }
    }
    g.close();
    return 0;
}