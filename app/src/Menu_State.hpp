#pragma once

#include <exception>
#include <string>

#include "User_Input_Strategy.hpp"
#include "clear.hpp"
#include "Menu_Chain.hpp"


class MenuStateException: public std::exception{
    
    std::string errorMessage;
    public:
    MenuStateException(std::string errorMessage);
    const char * what() const throw ();
};

class Menu_State{
    protected:
    User_Input_Strategy* inputFn;
    Output_Strategy* outputFn;
    

    public:
    Menu_State(User_Input_Strategy* inputFn, Output_Strategy* outputFn);
    virtual ~Menu_State();
    Menu_State* runMenu();

    private:
    virtual Menu_State* match_Output_To_Next_Menu(std::string output) =0;
    virtual void printMenu() = 0;
};
