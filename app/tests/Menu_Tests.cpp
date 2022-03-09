#include <catch2/catch.hpp>
#include "../src/Menu.hpp"


TEST_CASE("Build Menu","[Menu]"){

    
    Title title; // should need to add no User input strategy.

    MenuResult* res = title.executeForm();

    MenuComponent* next = res->getResult();

    res = next->executeForm();

    REQUIRE(true);
}