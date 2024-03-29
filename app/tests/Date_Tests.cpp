#include <catch2/catch.hpp>
#include <string.h>

#include "../src/Date.hpp"


TEST_CASE("Normal Date check", "[Date]"){
    
    try{
        Date* date = new Date(2021,1,14);
        REQUIRE(true);
    }catch(std::exception const &e){
        REQUIRE(false);
    }

    try{
        Date* date = new Date(2021,10,31);
        REQUIRE(true);
    }catch(std::exception const &e){
        REQUIRE(false);
    }

    try{
        Date* date = new Date(2021,11,31);
        REQUIRE(false);
    }catch(std::exception const &e){
        REQUIRE(true);
    }

}


TEST_CASE("Day out of bounds check", "[Date]"){
    try{
        Date* date = new Date(2021,1,60);
        REQUIRE(false);
    }catch(std::exception const &e){
        REQUIRE(true);
    }
}


TEST_CASE("Month out of bounds check", "[Date]"){
    
    try{
        auto date = new Date(2021,0,14);
        REQUIRE(false);
    }catch(std::exception const &e){
        REQUIRE(true);
    }

}

TEST_CASE("Year out of bounds check", "[Date]"){
    
    try{
        auto date = new Date(2221,1,14);
        REQUIRE(false);
    }catch(std::exception const &e){
        REQUIRE(true);
    }

}


TEST_CASE("Leap year check", "[Date]"){
    
    try{
        auto date = new Date(2020,2,29);
        REQUIRE(true);
    }catch(std::exception const &e){
        REQUIRE(false);
    }

    try{
        auto date = new Date(2021,2,29);
        REQUIRE(false);
    }catch(std::exception const &e){
        REQUIRE(true);
    }

}

TEST_CASE("Date to String check","Date"){
    Date* date = new Date(2021,1,14);

    const char* ds = date->toString().c_str();

    REQUIRE(strcmp("2021-1-14",ds) == 0);
}
