#include <random>
#include <sstream>
#include <algorithm>


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
    std::sort(
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
    ;
}

/**
 *
 */
void crossover()
{
    ;
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
    ;
}
