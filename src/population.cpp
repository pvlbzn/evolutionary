#include <random>
#include <sstream>
#include <algorithm>
#include <iostream>


#include "ga.hpp"


/**
 * Generate population.
 *
 * Population has a `size` and a `goal`.
 */
Population::Population(std::string g, int s)
{
    goal = g;
    ncitizens = s;
    score = -1;

    // Populate with random citizens
    for (int i = 0; i < s; i++)
        citizens.push_back(Chromosome(g.size()));
}


/**
 * Calculate population's performance.
 */
int Population::performance()
{
    score = 0;

    for (auto &chromosome : citizens)
        score += chromosome.calculate_cost(goal);

    return score;
}

/**
 * Perform ascending order sort of citizens.
 */
void Population::sort()
{
    return std::sort(
        citizens.begin(),
        citizens.end(),
        [](Chromosome const &l, Chromosome const &r) {
            return l.get_cost() < r.get_cost();
    });
}

/**
 *
 */
void Population::kill()
{
    if (score == -1) performance();

    // Find a mean cost of the citizens
    // Everything in range of 0..mean is considered good,
    // the rest goes into hands of the natural selection.
    int mean = score / citizens.size();

    // 0, 1, 2, 3 etc
    sort();

    int inflection_point = 0;
    for (int i = 0; i < citizens.size(); i++) {
        if (citizens[i].get_cost() > mean) {
            inflection_point = i;
            break;
        }
    }

    std::vector<Chromosome>::const_iterator first = citizens.begin();
    std::vector<Chromosome>::const_iterator last  = citizens.begin() + inflection_point;
    std::vector<Chromosome> n(first, last);

    citizens.clear();

    citizens = n;
}

/**
 * Crossover 1/4 most strongest chromosomes together.
 */
std::vector<Chromosome> Population::crossover()
{
    sort();

    int fraction = citizens.size() / 4;
    std::vector<Chromosome> mates(citizens.begin(), citizens.begin() + fraction);
    std::vector<Chromosome> breed;

    // Say there are 8 mates
    // 0 1 2 3 4 5 6 7
    // o o o o o o o o
    // Mate 0:1, 2:3, 3:5, 6:7
    // or n = 1, n+2
    for (int i = 1; i < mates.size(); i += 2)
        breed.push_back(mates[i-1] + mates[i]);

    return breed;
}

/**
 *
 */
void mutate()
{
    ;
}

/**
 *
 */
bool is_fit()
{
    return false;
}
