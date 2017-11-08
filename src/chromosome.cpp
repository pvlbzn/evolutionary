#include <random>
#include <sstream>

#include "ga.hpp"


#define ASCII_MAX 122
#define ASCII_MIN 65


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

/**
 * Initialize new Chromosome with the string of the given length.
 *
 * @param strlen desired length of the random string
 * @return new Chromosome
 */
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
 * Compare two chromosomes.
 *
 * 1 > 2 == true
 *
 * Because 1 is "better" than 2.
 *
 * @param other reference to other chromosome to which current instance
 *              will be compared
 * @return comparison truth value
 */
bool Chromosome::operator>(const Chromosome &other) const
{
    return (cost < other.cost);
}


/**
 * Mutate one gene of a chromosome.
 *
 * @return mutated chromosome
 */
Chromosome Chromosome::mutate()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> str_dist(0, data.length()-1);
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
 *
 * @param ref reference to the reference (goal) string
 * @return cost of the chromosome
 */
int Chromosome::calculate_cost(const std::string &ref)
{
    int total = 0;

    for (int i = 0; i < data.length(); i++) {
        total += (+data[i] - +ref[i]) * (+data[i] - +ref[i]);
    }

    cost = total;

    return total;
}
