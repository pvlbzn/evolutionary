#include <random>
#include <sstream>

#include "ga.hpp"


// tmp value
std::string reference_str = "Genetical Algorithm";
const int ASCII_MIN = 32;
const int ASCII_MAX = 122;


/**
 * Make random string of the length `len` in ASCII interval from
 * `min` to `max`.
 *
 * @param  min minimum ASCII character
 * @param  max maximum ASCII character
 * @param  len desired length
 * @return     randomly generated string
 */
std::string make_random_str(int min, int max, int len)
{
    std::stringstream ss;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(ASCII_MIN, ASCII_MAX);

    for (int i = 0; i < len; i++)
        ss << (char) dist(mt);

    return ss.str();
}


/**
 * Chromosome constructor with randomly generated data.
 */
Chromosome::Chromosome()
{
    data = make_random_str(ASCII_MIN, ASCII_MAX, 0);
    cost = -1;
}


Chromosome::Chromosome(int strlen)
{
    data = make_random_str(ASCII_MIN, ASCII_MAX, strlen);
    cost = -1;
}


/**
 * Crossover two chromosomes by adding them together.
 *
 * Left part from current chromosome, right part from `other` chromosome.
 *
 * @param other other chromosome
 * @return  product of crossover of two chromosomes
 */
Chromosome Chromosome::operator+(const Chromosome &other)
{
    std::string ndata;

    int len = data.length();

    ndata += data.substr(0, (len / 2));
    ndata += other.get_data().substr((len / 2), len);

    return Chromosome(ndata, -1);
}


/**
 * Mutate one gene of a chromosome.
 */
Chromosome Chromosome::mutate()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> str_dist(0, data.length());
    std::uniform_int_distribution<int> char_dist(ASCII_MIN, ASCII_MAX);

    std::string d = data;
    d[str_dist(mt) - 1] = char_dist(mt);

    return Chromosome(d, -1);
}


/**
 * Cost function.
 *
 * Function calculates chromosome cost and returns it. `cost` field
 * of the instance also mutated.
 */
int Chromosome::calculate_cost(const std::string &ref)
{
    int score = cost = 0;

    for (int i = 0; i < data.length(); i++)
        score += ((int) data[i]) - ((int) ref[i]);

    return cost = score >= 0 ? score : -score;
}
