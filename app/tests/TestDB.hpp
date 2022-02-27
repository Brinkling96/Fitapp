#pragma once

#include <array>

#include "../src/SQL_Query.hpp"
#include "../src/DB_connection.hpp"
#include "../src/User_Input_Strategy.hpp"


struct TestDB{

    DB_connection* conn;
    
    TestDB();
    ~TestDB();
    
    private:
    void createTestTables();

    void insertData();
};
