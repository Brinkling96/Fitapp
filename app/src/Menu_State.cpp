#include "Menu_State.hpp"

MenuStateException::MenuStateException(std::string errorMessage): errorMessage{errorMessage} {};

const char * MenuStateException::what() const throw (){
    return errorMessage.c_str();
}


Menu_State::Menu_State(User_Input_Strategy* inputFn, Output_Strategy* outputFn) : inputFn{inputFn},outputFn{outputFn} {};

Menu_State::~Menu_State(){}

Menu_State* Menu_State::runMenu(){
    Menu_State* menu = this;
    while(menu == this){
        clear();
        printMenu();
        std::string output = inputFn->getInput();
        menu = match_Output_To_Next_Menu(output);
    }
    return menu;
}

