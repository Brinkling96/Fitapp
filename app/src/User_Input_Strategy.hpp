#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include <libssh/libssh.h>
#include <libssh/libsshpp.hpp>

#include "Routine.hpp"

//Encapsulated function to skip user input during test, while collecting it in Production.
class User_Input_Strategy{
    public:
    virtual std::string getInput() = 0;
    virtual ~User_Input_Strategy() = 0;
};

class GetLine_Strategy : public User_Input_Strategy{
    public:
    std::string getInput() override;
    ~GetLine_Strategy();
};

class Static_Input_Strategy : public User_Input_Strategy{
    int ms_to_wait;
    public:
    std::string getInput() override;
    ~Static_Input_Strategy();
};


class Auto_Input_Strategy : public User_Input_Strategy{
    std::string input;
    public:
    Auto_Input_Strategy(std::string input);
    std::string getInput() override;
    ~Auto_Input_Strategy();
};

class GetPass_Strategy : public User_Input_Strategy{
    public:
    std::string getInput() override;
    ~GetPass_Strategy();
};

class Output_Strategy{
    public:
    virtual void output(std::string msg) = 0;
    virtual ~Output_Strategy() = 0;
};

class Null_Output_Strategy : public Output_Strategy{
    public:
    void output(std::string msg) override;
    ~Null_Output_Strategy();
};

class Msg_Output_Strategy : public Output_Strategy{
    public:
    void output(std::string msg) override;
    ~Msg_Output_Strategy();
};

