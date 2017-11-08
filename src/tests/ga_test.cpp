#define CATCH_CONFIG_MAIN

#include "../includes/catch.hpp"
#include "../ga.hpp"



TEST_CASE( "Chromosome should correspond to specification", "[Chromosome::Chromosome]" )
{
    SECTION("Create chromosome", "[Chromosome]") {
        auto c = Chromosome(5);

        REQUIRE( c.get_data().length() == 5 );
        REQUIRE( c.get_cost() == -1 );
    }

    SECTION("Create chromosome with a given data", "[Chromosome::Chromosome]") {
        auto c = Chromosome("some data", -1);

        REQUIRE( c.get_data() == "some data" );
        REQUIRE( c.get_cost() == -1 );
    }

    SECTION("Chromosomes should be different", "[Chromosome::Chromosome]") {
        auto c1 = Chromosome(50);
        auto c2 = Chromosome(50);

        REQUIRE( c1.get_data() != c2.get_data() );
    }

    SECTION("Chromosomes should crossover", "[Chromosome::operator+]") {
        auto c1 = Chromosome(50);
        auto c2 = Chromosome(50);

        int len = c1.get_data().length();

        auto left_half  = c1.get_data().substr(0, (len / 2));
        auto right_half = c2.get_data().substr((len / 2), len);

        auto c3 = c1 + c2;

        REQUIRE( c3.get_data() == (left_half + right_half) );
    }

    SECTION("Chromosomes should be comparable", "[Chromosome::operator>]") {
        auto c1 = Chromosome("aab", -1);
        auto c2 = Chromosome("bbb", -1);

        c1.calculate_cost("aaa");   // 1
        c2.calculate_cost("aaa");   // 3

        REQUIRE( c1 > c2 );
    }

    SECTION("Chromosomes should mutate", "[Chromosome::mutate]") {
        auto c1 = Chromosome(50);
        auto c1_mutated = c1.mutate();

        // Mutated data is differ from parent
        REQUIRE( c1.get_data() != c1_mutated.get_data() );

        int diff = 0;

        for (int i = 0; i < c1.get_data().length(); i++)
            if (c1.get_data()[i] != c1_mutated.get_data()[i])
                diff += 1;

        // Mutated exactly one gene from parent
        REQUIRE( diff == 1 );
    }

    SECTION("Chromosomes should be measured", "[Chromosome::calculate_cost]") {
        auto c1 = Chromosome("aaa", -1);

        // |a - b| = 1
        c1.calculate_cost("aab");

        REQUIRE( c1.get_cost() == 1 );

        c1.calculate_cost("bbb");

        REQUIRE( c1.get_cost() == 3 );

        // Cost also should be returned correctly
        REQUIRE( c1.calculate_cost("bbb") == 3 );

        auto c2 = Chromosome("isIna", -1);
        c2.calculate_cost("Hello");
        REQUIRE( c2.get_cost() == 2710 );
    }
}


TEST_CASE( "Population should correspond to specification", "[Population]" )
{
    SECTION("Population should be constructed properly", "[Population::Population]") {
        auto p = Population("goal", 50);

        REQUIRE( p.get_citizens().size() == 50 );
        REQUIRE( p.get_goal() == "goal" );
    }

    SECTION("Performance should be calculated correctly", "[Population::performance]") {
        auto p = Population("aaa", 0);
        auto c1 = Chromosome("bbb", -1);
        auto c2 = Chromosome("bbb", -1);

        p.get_citizens().push_back(c1);
        p.get_citizens().push_back(c2);

        REQUIRE( p.get_citizens().size() == 2 );
        REQUIRE( p.performance() == 6 );
    }

    SECTION("Population should be sorted properly", "[Population::sort]") {
        auto p = Population("aaa", 0);

        auto c1 = Chromosome("aab", -1);
        auto c2 = Chromosome("bbb", -1);

        p.get_citizens().push_back(c1);
        p.get_citizens().push_back(c2);

        p.sort();

        REQUIRE( p.get_citizens()[0].get_data() == "aab");
        REQUIRE( p.get_citizens()[1].get_data() == "bbb");
    }

    SECTION("Population should be killed properly", "[Population::kill]") {
        auto p = Population("aaa", 0);

        auto c1 = Chromosome("aab", -1); // 1
        auto c2 = Chromosome("abb", -1); // 2
        auto c3 = Chromosome("bbb", -1); // 3

        p.get_citizens().push_back(c3);
        p.get_citizens().push_back(c1);
        p.get_citizens().push_back(c2);

        // Mean: (1+2+3)/3 = 2
        p.kill();

        // "bbb" chromosome should be lost
        REQUIRE( p.get_citizens().size() == 2);
        REQUIRE( p.get_citizens()[0].get_data() == "aab");
        REQUIRE( p.get_citizens()[1].get_data() == "abb");
    }

    SECTION("Population crossover", "[Population::crossover]") {
        auto p = Population("aaaa", 0);

        auto c1 = Chromosome("aaab", -1); // 1
        auto c2 = Chromosome("aabb", -1); // 2
        auto c3 = Chromosome("abbb", -1); // 3
        auto c4 = Chromosome("abbc", -1); // 4
        auto c5 = Chromosome("abcc", -1); // 5
        auto c6 = Chromosome("accc", -1); // 6
        auto c7 = Chromosome("accd", -1); // 7
        auto c8 = Chromosome("acdd", -1); // 8

        p.get_citizens().push_back(c1);
        p.get_citizens().push_back(c2);
        p.get_citizens().push_back(c3);
        p.get_citizens().push_back(c4);
        p.get_citizens().push_back(c5);
        p.get_citizens().push_back(c6);
        p.get_citizens().push_back(c7);
        p.get_citizens().push_back(c8);

        auto breed = p.crossover();

        REQUIRE( breed.size() == 1 );
        REQUIRE( breed[0].get_data() == "aabb" );
    }

    SECTION("Citizen should mutate", "[Population::mutate]") {
        auto p = Population("aaaa", 0);

        auto c1 = Chromosome("aaab", -1); // 1

        p.get_citizens().push_back(c1);

        p.mutate();

        REQUIRE( p.get_citizens()[0].get_data() != "aaab" );
    }

    SECTION("Fitness should be detected properly", "[Population::is_fit]") {
        auto p = Population("aaaa", 0);

        auto c1 = Chromosome("aaab", -1); // 1
        p.get_citizens().push_back(c1);

        REQUIRE( !p.is_fit() );

        auto c2 = Chromosome("aaaa", -1);
        p.get_citizens().push_back(c2);

        p.performance();

        REQUIRE( p.is_fit() );
    }
}
