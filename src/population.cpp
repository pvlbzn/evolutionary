#include <random>
#include <sstream>


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

    // Populate with random citizens
    for (int i = 0; i < s; i++)
        citizens.push_back(Chromosome());
}

