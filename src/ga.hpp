#include <string>
#include <vector>


using std::string;
using std::vector;


class Chromosome
{
private:
    string  data;
    int     cost;
public:
    Chromosome();
    Chromosome(int strlen);
    Chromosome(string d, int c) :data {d}, cost {c} {}

    Chromosome operator + (const Chromosome &other);
    bool       operator > (const Chromosome &other) const;

    Chromosome mutate();
    Chromosome crossover(const Chromosome &other);
    int calculate_cost(const std::string &ref);

    string get_data() const { return data; }
    int    get_cost() const { return cost; }
};


class Population
{
private:
    int ncitizens;
    int score;

    vector<Chromosome> citizens;

    string goal;
public:
    Population(string g, int s);
    ~Population()
    {
        citizens.clear();
    }

    int  performance();
    void sort();
    void kill();
    void repopulate();
    std::vector<Chromosome> crossover();
    void mutate();
    bool is_fit();

    string  get_status();
    string& get_goal() { return goal; }
    vector<Chromosome>& get_citizens() { return citizens; }
};
