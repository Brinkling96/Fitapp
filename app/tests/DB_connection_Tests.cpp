#include <catch2/catch.hpp>
#include <memory>
#include <pqxx/pqxx>
#include <array>
#include <algorithm>

#include "../src/DB_connection.hpp"
#include "../src/SQL_Query.hpp"



std::array<char*,5> inputs = {"I am the exe name","postgresql","5432","sean","Fit"};

//stupid fixture
No_Pass strategy;
static DB_connection conn(inputs, &strategy);

TEST_CASE("Does Connection work?", "[DB_connection]"){
    SQL_Query q("SELECT 1;");
    conn.execute(&q);
    int x = q.result.at(0)[0].as<int>();
    REQUIRE(x == 1);
}

TEST_CASE("Can Connection read?", "[DB_connection]"){
    SQL_Query q("SELECT * FROM pg_catalog.pg_tables");
    conn.execute(&q);

    REQUIRE(strcmp(q.result.column_name(0),"schemaname") == 0);
    REQUIRE(strcmp(q.result.column_name(1),"tablename") == 0);

}


//Purpose of this class is to call destructor on test exit
class TestTable{
    public:
        TestTable(){
            SQL_Query q("CREATE TABLE test( id int, name varchar(25), date Date);");
            conn.execute(&q);
        }
        ~TestTable(){
            SQL_Query q("DROP TABLE test");
            conn.execute(&q);
        }
};

TEST_CASE("Can Connection write?", "[DB_connection]"){

    TestTable t;
    try{
        SQL_Query q("INSERT INTO test VALUES (1,\'sean\',\'2021-1-14\');");
        conn.execute(&q);

        q = SQL_Query("SELECT * FROM test;");
        conn.execute(&q);

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





