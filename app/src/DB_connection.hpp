#include <iostream>
#include <array>

#include <memory>
#include <pqxx/pqxx>

#include <libssh/libssh.h>
#include <libssh/libsshpp.hpp>


#include "SQL_Query.hpp"


class Password_Strategy{
    public:
    virtual int getPassword(char* mPass, int size) = 0;
};

class No_Pass : public Password_Strategy{
    public:
    int getPassword(char* mPass, int size) override;
};

class User_Input_Pass : public Password_Strategy{
    public:
    int getPassword(char* mPass, int size) override;
};

class DB_connection{
    pqxx::connection* conn;

    public:
    DB_connection(std::array<char*,5> inputs, Password_Strategy* pass_Strat);

    bool execute(SQL_Query* query);
    

};

