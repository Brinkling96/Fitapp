#pragma once
#include <exception>
#include <stdexcept>
#include <string>

class Menu_Chain_Exception: public std::exception{
    std::string errMsg;
    public:
    Menu_Chain_Exception(std::string errMsg);
    const char * what() const throw ();
};