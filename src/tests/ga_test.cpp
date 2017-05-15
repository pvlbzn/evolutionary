#define CATCH_CONFIG_MAIN

#include "../includes/catch.hpp"
#include "../ga.hpp"



TEST_CASE( "Chromosome should correspond to specification", "[Chromosome]" )
{
    SECTION("Create chromosome", "[Chromosome]") {
        auto c = Chromosome();

        REQUIRE( c.get_data().length() != 0 );
        REQUIRE( c.get_cost() == -1 );
    }

    SECTION("Create chromosome with a given data", "[Chromosome]") {
        auto c = Chromosome("some data", -1);

        REQUIRE( c.get_data() == "some data" );
        REQUIRE( c.get_cost() == -1 );
    }

    SECTION("Chromosomes should be different", "[Chromosome]") {
        auto c1 = Chromosome();
        auto c2 = Chromosome();

        REQUIRE( c1.get_data() != c2.get_data() );
    }

    SECTION("Chromosomes should crossover", "[Chromosome]") {
        auto c1 = Chromosome();
        auto c2 = Chromosome();

        int len = c1.get_data().length();

        auto left_half = c1.get_data().substr(0, (len / 2));
        auto right_half = c2.get_data().substr((len / 2), len);

        auto c3 = c1 + c2;

        REQUIRE( c3.get_data() == (left_half + right_half) );
    }

    SECTION("Chromosomes should mutate", "[Chromosome]") {
        auto c1 = Chromosome();
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
}
