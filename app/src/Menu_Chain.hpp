#pragma once
#include <string>
#include <vector>

#include "Menu_Chain_Exception.hpp"



template <typename T>
class Menu_Chain{
    protected:
    Menu_Chain<T>* next_Chain;

    public: 
    Menu_Chain();
    Menu_Chain(Menu_Chain* next_Chain);
    virtual ~Menu_Chain();

    virtual void setNext(Menu_Chain* next_Chain) = 0;
    virtual T select(std::string select) = 0; //TODO this is ugly
    virtual std::string toString_Chain() =0;
};

template <typename T>
class Null_Chain_Link : public Menu_Chain<T>{
    public:
    Null_Chain_Link();
    ~Null_Chain_Link();

    void setNext(Menu_Chain<T>* next_Chain) override;
    T select(std::string select) override;
    std::string toString_Chain() override;
};


template <typename T>
class String_Option_Chain_Link : public Menu_Chain<T>{
    std::string prompt;
    std::string option;
    T result;

    public:
    String_Option_Chain_Link(std::string prompt, std::string option, T result);
    String_Option_Chain_Link(Menu_Chain<T>* next_Chain, std::string prompt, std::string option, T result);
    ~String_Option_Chain_Link();

    void setNext(Menu_Chain<T>* next_Chain) override;
    void setResult(T result);
    T select(std::string select) override;
    std::string toString_Chain() override;


};


#include "Menu_Chain.tpp"

