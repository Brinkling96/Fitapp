#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>


#include "User_Input_Strategy.hpp"

class MenuComponent;

class UnsupportedOperationException: public std::exception{
    std::string inputCMD;
    public:
    UnsupportedOperationException(std::string inputCMD);
    const char * what() const throw ();
};

class MenuResult{
    
    public:
    MenuResult();
    virtual bool notNull()=0;
    virtual MenuComponent* getResult()=0;
    virtual MenuComponent* undo()=0;
};

class NormalResult : public MenuResult{
    MenuComponent* next;
    MenuComponent* prev;
    public:
    NormalResult(MenuComponent* next, MenuComponent* prev);
    bool notNull() override;
    MenuComponent* getResult() override;
    MenuComponent* undo() override;
};

class ExitResult : public MenuResult{
    MenuComponent* prev;
    public:
    ExitResult(MenuComponent* prev);
    bool notNull() override;
    MenuComponent* getResult() override;
    MenuComponent* undo() override;
};

class NullResult : public MenuResult{
    public:
    bool notNull() override;
    MenuComponent* getResult() override;
    MenuComponent* undo() override;
};



class MenuComponent{
    public:
    virtual MenuResult* executeForm() = 0;

    protected:
    virtual void display()=0;
    virtual MenuResult* execute(std::string inputCMD)=0;

    friend class Menu;
    
};

class Menu : public MenuComponent {
    protected:
    std::vector<MenuComponent*> components;
    User_Input_Strategy* inputFn;
    Menu();

    public:

    Menu(std::vector<MenuComponent*> components, User_Input_Strategy* inputFn);
    MenuResult* executeForm() override;


    private:
    void display() override;
    MenuResult* execute(std::string inputCMD) override;
};

class MenuItem : public MenuComponent {
    protected:
    std::string description;
    void display() override;
    virtual MenuResult* execute(std::string inputCMD)=0;
    
    public:
    MenuItem(std::string description);
    virtual MenuResult* executeForm()=0;
    
    
};

class MenuCommand : public MenuItem {
    private:
    MenuResult* result;
    std::string userCMD;
    User_Input_Strategy* inputFn;

    public:
    MenuCommand(std::string description, std::string userCMD, MenuResult* result, User_Input_Strategy* inputFn);
    MenuResult* executeForm() override;
    private:
    MenuResult* execute(std::string inputCMD) override;
};

class MenuDescription : public MenuItem {
    public:
    MenuDescription(std::string description);
    MenuResult* executeForm() override;
    
    private:
    MenuResult* execute(std::string inputCMD) override;
};


class Title: public Menu {
    public:
    Title();
};

class MainMenu : public Menu {
    public:
    MainMenu();
};

/*
class WorkoutMenu: public Menu{
    MenuResult* menuStack;
    public:
    WorkoutMenu(MenuResult* menuStack);
};
*/