#include <random>
#include <sstream>

#include <iostream>

#include "ga.hpp"


// tmp value
std::string input_string = "Genetical Algorithm";
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


Chromosome::Chromosome()
{
    data = make_random_str(ASCII_MIN, ASCII_MAX, input_string.length());
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
Chromosome Chromosome::operator+(Chromosome &other)
{
    std::string ndata;

    int len = data.length();

    ndata += data.substr(0, (len / 2));
    ndata += other.get_data().substr((len / 2), len);

    return Chromosome(ndata, -1);
}

