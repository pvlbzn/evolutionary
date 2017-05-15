#include <string>
#include <vector>


using std::string;
using std::vector;


class Chromosome
{
private:
    string   data;
    int cost;
public:
    Chromosome();
    Chromosome(string d, int c) :data {d}, cost {c} {}

    Chromosome operator+(const Chromosome &other);

    Chromosome mutate();
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

    void performance();
    void kill();
    void crossover();
    void mutate();
    bool is_fit();

    string get_status();
    const string& get_goal() { return goal; }
    const vector<Chromosome>& get_citizens() { return citizens; }
};
