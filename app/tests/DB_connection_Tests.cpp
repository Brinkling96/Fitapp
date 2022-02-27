#include <catch2/catch.hpp>
#include <iostream>
#include <memory>
#include <pqxx/pqxx>
#include <array>
#include <algorithm>

#include "../src/DB_connection.hpp"
#include "../src/SQL_Query.hpp"
#include "TestDB.hpp"



//TODO refactor with new testdb


//stupid fixture
static TestDB testdb;

TEST_CASE("Does Connection work?", "[DB_connection]"){
    SQL_Query q("SELECT 1;");
    testdb.conn->execute(&q);
    int x = q.result.at(0)[0].as<int>();
    REQUIRE(x == 1);
}

TEST_CASE("Can Connection read?", "[DB_connection]"){
    SQL_Query q("SELECT * FROM pg_catalog.pg_tables");
    testdb.conn->execute(&q);

    REQUIRE(strcmp(q.result.column_name(0),"schemaname") == 0);
    REQUIRE(strcmp(q.result.column_name(1),"tablename") == 0);

}


//Purpose of this class is to call destructor on test exit


TEST_CASE("Can Connection write?", "[DB_connection]"){

    try{
        SQL_Query q("INSERT INTO test VALUES (1,\'sean\',\'2021-1-14\');");
        testdb.conn->execute(&q);

        q = SQL_Query("SELECT * FROM test;");
        testdb.conn->execute(&q);

        REQUIRE(q.result.at(0)[0].as<int>() == 1);
        REQUIRE(strcmp("sean",q.result.at(0)[1].c_str()) == 0);
        REQUIRE(strcmp("2021-01-14",q.result.at(0)[2].c_str()) == 0);

    } catch (pqxx::sql_error const &e){
        std::cerr << "SQL error: " <<e.what() <<std::endl;
        std::cerr << "Query was: " <<e.query() <<std::endl;
        REQUIRE(false);
    }

    catch(std::exception const &e){
        std::cerr << "Error: " <<e.what() << std::endl;
        REQUIRE(false);
    }

}





