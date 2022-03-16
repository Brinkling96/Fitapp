#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

class Menu_Chain_Exception: public std::exception{
    std::string errMsg;
    public:
    Menu_Chain_Exception(std::string errMsg);
    const char * what() const throw ();
};

class Menu_Chain{
    protected:
    Menu_Chain* next_Chain;

    public: 
    Menu_Chain();
    Menu_Chain(Menu_Chain* next_Chain);
    virtual ~Menu_Chain();

    virtual void setNext(Menu_Chain* next_Chain) = 0;
    virtual unsigned int select(std::string select) = 0; //TODO this is ugly
};


class Null_Chain_Link : public Menu_Chain{
    public:
    Null_Chain_Link();
    ~Null_Chain_Link();

    void setNext(Menu_Chain* next_Chain) override;
    unsigned int select(std::string select) override;
};

class String_Option_Chain_Link : public Menu_Chain{
    std::string option;
    unsigned int result;

    public:
    String_Option_Chain_Link(std::string option, unsigned int result);
    String_Option_Chain_Link(Menu_Chain* next_Chain, std::string option, unsigned int result);
    ~String_Option_Chain_Link();

    void setNext(Menu_Chain* next_Chain) override;
    void setResult(unsigned int result);
    unsigned int select(std::string select) override;

};

