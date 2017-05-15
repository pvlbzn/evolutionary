#include <random>
#include <sstream>

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
    std::mt19937 gen;
    std::uniform_int_distribution<int> rng(ASCII_MIN, ASCII_MAX);

    for (int i = 0; i < len; i++)
        ss << rng(gen);

    return ss.str();
}


Chromosome::Chromosome()
{
    data = make_random_str(ASCII_MIN, ASCII_MAX, input_string.length());
    cost = -1;
}

// Chromosome operator+(const Chromosome &other)
// {
//     ;
// }

