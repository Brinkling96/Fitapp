#include "Menu_Chain.hpp"

Menu_Chain_Exception::Menu_Chain_Exception(std::string errMsg) : errMsg{errMsg} {};

const char * Menu_Chain_Exception::what() const throw (){
    return errMsg.c_str();
}

Menu_Chain::Menu_Chain(){
    this->next_Chain = new Null_Chain_Link();
}

Menu_Chain::Menu_Chain(Menu_Chain* next_Chain): next_Chain{next_Chain} {};

Menu_Chain::~Menu_Chain(){
    delete next_Chain;
}


Null_Chain_Link::Null_Chain_Link() : Menu_Chain(nullptr) {};

Null_Chain_Link::~Null_Chain_Link(){};


void Null_Chain_Link::setNext(Menu_Chain* next_Chain){
    throw Menu_Chain_Exception("Null Chain link does not allow next chain sets.");
}

unsigned int Null_Chain_Link::select(std::string select){
    throw Menu_Chain_Exception("Null Chain, cannot execute select");
}

String_Option_Chain_Link::String_Option_Chain_Link(std::string option, unsigned int result) : option{option}, result{result} {};

String_Option_Chain_Link::String_Option_Chain_Link(Menu_Chain* next_Chain, std::string option, unsigned int result) : Menu_Chain(next_Chain), option{option}, result{result} {};

String_Option_Chain_Link::~String_Option_Chain_Link(){
    delete this->next_Chain;
}

void String_Option_Chain_Link::setNext(Menu_Chain* next_Chain){
    this->next_Chain= next_Chain;
}

void String_Option_Chain_Link::setResult(unsigned int result){
    this->result = result;
}


unsigned int String_Option_Chain_Link::select(std::string select){
    if(option.compare(select) == 0){
        return result;
    }
    else {
        return this->next_Chain->select(select);
    }
}
