#ifndef GENETIC_ALGORITHM_GENETICALGORITHM_HPP
#define GENETIC_ALGORITHM_GENETICALGORITHM_HPP

#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

class DNA {
private:
    std::string phrase;
    double fitness;
public:
    DNA() : phrase(""), fitness(0.0) {};
    DNA(std::string ph, double f) : phrase(std::move(ph)), fitness(f) {};
    std::string get_phrase() const { return this->phrase;  }
    double get_fitness()     const { return this->fitness; }

    void set_phrase(const std::string &ph) {
        this->phrase = ph;
    }

    void set_fitness(const double f) {
        this->fitness = f;
    }

};

namespace GeneticAlgorithm {
    inline const static std::size_t pop_count = 200;
    inline static std::string target_phrase = "This cake is a lie";
    inline static std::size_t phrase_length = target_phrase.length();
    inline static double mutation_rate = 0.02;
    inline static std::size_t generations = 0;

    void natural_selection();
    void new_generation();

    int rand_int_in_range(int imin, int imax);
    double rand_double_in_range(double imin, double imax);
    char rand_char();

    DNA *crossover(const DNA*, const DNA*);
    void mutate(DNA*);
}

namespace GeneticAlgorithm::Population {

    inline static std::vector<DNA*> genes;
    inline static std::vector<DNA*> mating_pool;
    inline static DNA* best_fit;
    void init_genes();

    std::string rand_str(std::size_t);

    void calculate_fitness();
    void calculate_fitness(DNA *);

    DNA *get_best_fit();

}

int GeneticAlgorithm::rand_int_in_range(int imin, int imax) {
    std::random_device rand_dev;
    std::mt19937 mt(rand_dev());
    std::uniform_int_distribution<int> dist(imin, imax);
    return dist(mt);
}

std::string GeneticAlgorithm::Population::rand_str(std::size_t ph_size) {
    std::string res;
    for(size_t i = 0; i < ph_size; i++) {
        char c = GeneticAlgorithm::rand_char();
        res += c;
    }
    return res;
}
void GeneticAlgorithm::Population::init_genes() {
    for(size_t i = 0; i < pop_count; i++) {
        auto d = new DNA{};
        d->set_phrase(GeneticAlgorithm::Population::rand_str(GeneticAlgorithm::phrase_length));
        GeneticAlgorithm::Population::genes.push_back(d);
    }
}

// Elementary way to find fitness.
void GeneticAlgorithm::Population::calculate_fitness(DNA *d) {
    std::string curr_ph = d->get_phrase();
    std::size_t good_chars = 0;
    for(size_t i = 0; i < GeneticAlgorithm::phrase_length; i++) {
        if(curr_ph[i] == GeneticAlgorithm::target_phrase[i]) {
            good_chars++;
        }
    }
    d->set_fitness(good_chars * 1.0 / GeneticAlgorithm::phrase_length);
}

void GeneticAlgorithm::Population::calculate_fitness() {
    for(auto &g : GeneticAlgorithm::Population::genes) {
        GeneticAlgorithm::Population::calculate_fitness(g);
    }
}

DNA* GeneticAlgorithm::Population::get_best_fit() {
    auto d = *std::max_element(std::begin(GeneticAlgorithm::Population::genes),
            std::end(GeneticAlgorithm::Population::genes),
            [](const DNA *a, const DNA *b) {
        return a->get_fitness() < b->get_fitness();
    });
    Population::best_fit = d;
    return d;
}

// TODO: Apply mutation and new generation.
void GeneticAlgorithm::natural_selection() {
    GeneticAlgorithm::Population::mating_pool.clear();
    auto DNA1 = GeneticAlgorithm::Population::get_best_fit();
    const double max_fitness = DNA1->get_fitness();
    for(size_t i = 0; i < GeneticAlgorithm::pop_count; i++) {
        double curr_fitness = GeneticAlgorithm::Population::genes[i]->get_fitness() / max_fitness;
        int n = static_cast<int>(std::round(curr_fitness * 100.0));
        for(size_t j = 0; j < n; j++) {
            GeneticAlgorithm::Population::mating_pool.push_back(GeneticAlgorithm::Population::genes[i]);
        }
    }
}

void GeneticAlgorithm::new_generation() {
    GeneticAlgorithm::generations++;
    GeneticAlgorithm::Population::genes.clear();
    auto& mu = GeneticAlgorithm::Population::mating_pool;
    auto tD = GeneticAlgorithm::Population::mating_pool.size();
    for(size_t i = 0; i < GeneticAlgorithm::pop_count; i++) {
        int first_parent_idx = GeneticAlgorithm::rand_int_in_range(0, GeneticAlgorithm::Population::mating_pool.size() - 1);
        int second_parent_idx = GeneticAlgorithm::rand_int_in_range(0, GeneticAlgorithm::Population::mating_pool.size() - 1);

        auto first_parent  = GeneticAlgorithm::Population::mating_pool[first_parent_idx];
        auto second_parent = GeneticAlgorithm::Population::mating_pool[second_parent_idx];

        while(second_parent->get_phrase() == first_parent->get_phrase()) {
            second_parent_idx = GeneticAlgorithm::rand_int_in_range(0, GeneticAlgorithm::Population::mating_pool.size());
            second_parent = GeneticAlgorithm::Population::mating_pool[second_parent_idx];
        }
        auto child = GeneticAlgorithm::crossover(first_parent, second_parent);
        GeneticAlgorithm::mutate(child);
        GeneticAlgorithm::Population::genes.push_back(child);
    }

}

DNA *GeneticAlgorithm::crossover(const DNA *a, const DNA *b) {
    auto child = new DNA{};
    std::string res_phrase;
    std::string p1 = a->get_phrase();
    std::string p2 = b->get_phrase();
    std::string::size_type mid_point = GeneticAlgorithm::rand_int_in_range(0, GeneticAlgorithm::phrase_length);
    for(int i = 0; i < GeneticAlgorithm::phrase_length; i++) {
        if (i > mid_point) {
            res_phrase += p1[i];
        } else {
            res_phrase += p2[i];
        }
    }
    child->set_phrase(res_phrase);
    return child;
}

void GeneticAlgorithm::mutate(DNA *a) {
    std::string ph = a->get_phrase();
    for(char& c : ph) {
        if(GeneticAlgorithm::rand_double_in_range(0.0, 1.0) < GeneticAlgorithm::mutation_rate) {
            c = GeneticAlgorithm::rand_char();
        }
    }
    a->set_phrase(ph);
}

double GeneticAlgorithm::rand_double_in_range(double imin, double imax) {
    std::random_device rd;
    std::default_random_engine generator(rd()); // rd() provides a random seed
    std::uniform_real_distribution<double> distribution(imin, imax);

    return distribution(generator);
}

char GeneticAlgorithm::rand_char() {
    char c = GeneticAlgorithm::rand_int_in_range(63, 122);
    while(!isalpha(c) && !(c == 63 || c == 64)) {
        c = GeneticAlgorithm::rand_int_in_range(63, 122);
    }
    if (c == 63 || c == 64) c = ' ';
    return c;
}


#endif //GENETIC_ALGORITHM_GENETICALGORITHM_HPP
