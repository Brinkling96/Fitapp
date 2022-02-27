#pragma once

#include <pqxx/pqxx>
#include <array>
#include <sstream>
#include <iostream>

#include "User_Input_Strategy.hpp"
#include "SQL_Query.hpp"



class DB_connection{
    pqxx::connection* conn;

    public:
    DB_connection(std::array<const char*,5> inputs, User_Input_Strategy* inputFn, Output_Strategy* outputFn);
    ~DB_connection();
    bool execute(SQL_Query* query);

    

};

