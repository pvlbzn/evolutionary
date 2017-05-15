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
}
