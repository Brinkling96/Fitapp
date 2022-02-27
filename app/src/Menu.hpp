#include <vector>
#include <string>
#include <sstream>

#include "User_Input_Strategy.hpp"

class MenuResult{
    public:
    virtual bool notNull()=0;
    virtual MenuComponent* executeResult()=0;
    virtual MenuComponent* undo()=0;
}

class TitleResult{
    
}

class NullResult : public MenuResult{
    bool notNull() override;
    MenuComponent* executeResult() override;
    MenuComponent* undo() override;
}


class UnsupportedOperationException: public std::exception{
    std::string inputCMD;
    public:
    UnsupportedOperationException(std::string inputCMD);
    const char * what() const throw ();
};



class MenuComponent{
    public:
    virtual MenuResult executeForm() = 0;

    private:
    virtual MenuResult execute(std::string inputCMD)=0;
    
};

class Menu : public MenuComponent {
    private:

    std::vector<MenuComponent> components;
    User_Input_Strategy* inputFn;
    
    public:

    Menu(std::vector<MenuComponent> components);
    MenuResult executeForm() override;


    private:

    MenuResult execute(std::string inputCMD) override;
};

class MenuItem : public MenuComponent {
    public:
    virtual MenuResult executeForm()=0;
    
    private:
    virtual MenuResult execute(std::string inputCMD)=0;
};

class MenuCommand : public MenuItem {
    private:
    std::string user_input_command;
    MenuResult result;

    public:
    MenuCommand(std::string user_input_command, MenuResult result);
    MenuResult executeForm() override;
    private:
    MenuResult execute(std::string inputCMD) override;
}

class MenuDescription : public MenuItem {
    private:
    std::string description;

    public:
    MenuDescription(std::string description);
    MenuResult executeForm() override;
    
    private:
    MenuResult execute(std::string inputCMD) override;
}


class Title: public Menu {
    public:
    Title();
}

class MainMenu : public Menu {
    MenuResult* menuStack;
    public:
    MainMenu(MenuResult* menuStack);
}

class WorkoutMenu: public Menu{
    MenuResult* menuStack;
    public:
    WorkoutMenu(MenuResult* menuStack);
}
