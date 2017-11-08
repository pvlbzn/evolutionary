#include <random>
#include <sstream>
#include <algorithm>

#include "ga.hpp"


/**
 * Generate population.
 *
 * Population has a `size` and a `goal`.
 *
 * @param g goal string, reference
 * @param s size of population
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
 *
 * Performance of each chromosome is calculated, the sum of individual
 * chromosomes is the total score.
 *
 * @return performance score
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
 * Perform natural selection against population.
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

    // citizens.clear();

    citizens = n;
}

/**
 * Crossover 1/3 most strongest chromosomes together.
 *
 * @return vector of newly created chromosomes
 */
std::vector<Chromosome> Population::crossover()
{
    sort();

    int fraction = citizens.size() / 3;
    std::vector<Chromosome> mates(citizens.begin(), citizens.begin() + fraction);

    // Say there are 8 mates
    // 0 1 2 3 4 5 6 7
    // o o o o o o o o
    // Mate 0:1, 2:3, 3:5, 6:7
    // or n = 1, n+2
    for (int i = 1; i < mates.size(); i += 2) {
        auto n = mates[i - 1] + mates[i];
        n.calculate_cost(goal);
        citizens.push_back(n);
    }

    sort();

    for (int i = 1; i < mates.size(); i += 2)
        citizens.pop_back();
}

/**
 * Mutate random citizen.
 */
void Population::mutate()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_citizen(0, citizens.size() - 1);

    // int n = dist_citizen(mt);
    // citizens[n] = citizens[n].mutate();
    for (int i = 0; i < citizens.size(); i++)
        citizens[i] = citizens[i].mutate();
}

/**
 * Check whether population reached the goal or not.
 *
 * @return truth value of fitness
 */
bool Population::is_fit()
{
    for (auto const &citizen : citizens)
        if (citizen.get_cost() == 0 and citizen.get_data() == goal)
            return true;

    return false;
}


std::string Population::get_status()
{
    std::stringstream ss;
    // Population score
    ss << "score: \t" << score << '\n';
    for (auto &c : citizens)
        ss << "data: \t" << c.get_data() << "\t cost: \t" << c.get_cost() << "\n";

    return ss.str();
}
