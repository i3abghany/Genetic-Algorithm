#ifndef GENETIC_ALGORITHM_GENETICALGORITHM_HPP
#define GENETIC_ALGORITHM_GENETICALGORITHM_HPP

#include <vector>
#include <random>

std::string rand_str(std::size_t ph_size) {
    std::string res;
    std::random_device rand_dev;
    std::mt19937 mt(rand_dev());
    std::uniform_int_distribution<std::uint8_t> dist(65, 122);
    for(int i = 0; i < ph_size; i++) {
        char c = dist(mt);
        while(!isalpha(c) && !(c == 94 || c == 95 || c == 96)) {
            c = dist(mt);
        }
        if (c == 94 || c == 95 || c == 96) c = ' ';
        res += c;
    }
    return res;
}

class DNA {
private:
    std::string phrase;
    double fitness;
public:
    DNA() : phrase(""), fitness(0.0) {};
    DNA(std::string ph, double f) : phrase(std::move(ph)), fitness(f) {};
    std::string get_phrase() { return this->phrase; }
    double get_fitness() { return this->fitness; }
    void set_phrase(const std::string &ph) {
        this->phrase = ph;
    }
    void set_fitness(const double f) {
        this->fitness = f;
    }
};

namespace GeneticAlgorithm {
    inline static std::size_t pop_count = 200;
    inline static std::string target_phase = "ThisCakeIsALie";
    inline static std::size_t phrase_length = target_phase.length();
}

namespace GeneticAlgorithm::Population {
    inline static std::vector<DNA> genes;
    void init_genes();

    void calculate_fitness();

    void calculate_fitness(DNA &);
}

void GeneticAlgorithm::Population::init_genes() {
    GeneticAlgorithm::Population::genes.resize(pop_count);
    for(int i = 0; i < pop_count; i++) {
        GeneticAlgorithm::Population::genes[i].set_phrase(rand_str(phrase_length));
    }
}

void GeneticAlgorithm::Population::calculate_fitness(DNA &d) {
    std::string curr_ph = d.get_phrase();
    std::size_t good_chars = 0;
    for(int i = 0; i < GeneticAlgorithm::phrase_length; i++) {
        if(curr_ph[i] == GeneticAlgorithm::target_phase[i]) {
            good_chars++;
        }
    }
    d.set_fitness(good_chars * 1.0 / GeneticAlgorithm::phrase_length);
}

void GeneticAlgorithm::Population::calculate_fitness() {
    int i = 0;
    for(auto &g : GeneticAlgorithm::Population::genes) {
        GeneticAlgorithm::Population::calculate_fitness(g);
        i++;
    }
}

#endif //GENETIC_ALGORITHM_GENETICALGORITHM_HPP
