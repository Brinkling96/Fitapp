#include <catch2/catch.hpp>

#include <string>

#include "../src/Menu_Chain.hpp"


TEST_CASE("Does Basic Chain work?", "[Menu_Chain]"){
    
    Menu_Chain* bottom = new String_Option_Chain_Link(std::string("c"), 3);
    Menu_Chain* mid = new String_Option_Chain_Link(bottom,std::string("b"),2);
    Menu_Chain* top = new String_Option_Chain_Link(mid,std::string("a"),1);

    REQUIRE(top->select(std::string("a")) == 1);

    REQUIRE(top->select(std::string("b")) == 2);

    REQUIRE(top->select(std::string("c")) == 3);



}