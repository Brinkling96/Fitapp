#include "Menu_Chain_Exception.hpp"

Menu_Chain_Exception::Menu_Chain_Exception(std::string errMsg) : errMsg{errMsg} {};

const char * Menu_Chain_Exception::what() const throw (){
    return errMsg.c_str();
}
