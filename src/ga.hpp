#include <string>
#include <vector>


using std::string;
using std::vector;


class Chromosome
{
private:
    string   data;
    uint32_t cost;
public:
    Chromosome();

    Chromosome operator+(const Chromosome &other);

    void mutate();
    void calculate_cost();
};


class Population
{
private:
    const uint32_t     ncitizens;
    const uint32_t     score;

    vector<Chromosome> citizens;
public:
    Population(string goal, uint32_t size);
    ~Population()
    {
        citizens.clear();
    }

    void performance();
    void kill();
    void crossover();
    void mutate();
    bool is_fit();
};
