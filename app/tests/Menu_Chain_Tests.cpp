#include <catch2/catch.hpp>

#include <string>

#include "../src/Menu_Chain.hpp"

struct TestStruct{
    int test_int;
    bool test_bool;
};

TEST_CASE("Does Basic Chain work?", "[Menu_Chain]"){


    TestStruct bot_res = {3,true};
    Menu_Chain<TestStruct>* bottom = new String_Option_Chain_Link<TestStruct>(std::string("Enter c to get 3\n"),std::string("c"), bot_res);

    TestStruct mid_res = {2,false};
    Menu_Chain<TestStruct>* mid = new String_Option_Chain_Link<TestStruct>(bottom,std::string("Enter b to get 2\n"),std::string("b"), mid_res);

    TestStruct top_res = {1, true};
    Menu_Chain<TestStruct>* top = new String_Option_Chain_Link<TestStruct>(mid,std::string("Enter a to get 1\n"),std::string("a"),top_res);

    std::string menu = top->toString_Chain();
    REQUIRE(menu.compare(std::string("Enter a to get 1\nEnter b to get 2\nEnter c to get 3\n")) == 0);

    TestStruct a_res =  top->select(std::string("a"));
    REQUIRE(a_res.test_int == 1);
    REQUIRE(a_res.test_bool);

    TestStruct b_res =  top->select(std::string("b"));
    REQUIRE(b_res.test_int == 2);
    REQUIRE(b_res.test_bool == false);

    TestStruct c_res = top->select(std::string("c"));
    REQUIRE(c_res.test_int == 3);
    REQUIRE(c_res.test_bool);
}