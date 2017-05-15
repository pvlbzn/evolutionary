#define CATCH_CONFIG_MAIN

#include "../includes/catch.hpp"
#include "../ga.hpp"



TEST_CASE( "Chromosome should correspond to specification", "[Chromosome]" )
{
    SECTION("Create chromosome", "[Chromosome]") {
        auto c = new Chromosome();

        REQUIRE( c->get_data().length() != 0 );
        REQUIRE( c->get_cost() == -1 );
    }

    SECTION("Create chromosome with a given data", "[Chromosome]") {
        auto c = new Chromosome("some data", -1);

        REQUIRE( c->get_data() == "some data" );
        REQUIRE( c->get_cost() == -1 );
    }

    SECTION("Chromosomes should be different", "[Chromosome]") {
        auto c1 = new Chromosome();
        auto c2 = new Chromosome();

        REQUIRE( c1->get_data() != c2->get_data() );
    }
}
