#pragma once
#include <sstream>

#include "Menu_State.hpp"
#include "Date.hpp"

class TitleMenu : public Menu_State{
    public:
    TitleMenu(User_Input_Strategy* inputFn, Output_Strategy* outputFn);
    ~TitleMenu();
    private:
    Menu_State* match_Output_To_Next_Menu(std::string output) override;
    void printMenu() override; 
};

class QuitMenu: public Menu_State{
    public:
    QuitMenu(User_Input_Strategy* inputFn, Output_Strategy* outputFn);
    ~QuitMenu();
    private:
    Menu_State* match_Output_To_Next_Menu(std::string output) override;
    void printMenu() override;
};

class MainMenu : public Menu_State{
    public:
    MainMenu(User_Input_Strategy* inputFn, Output_Strategy* outputFn);
    ~MainMenu();
    private:
    Menu_State* match_Output_To_Next_Menu(std::string output) override;
    void printMenu() override; 
};

class WorkoutMenu : public Menu_State{
    public:
    WorkoutMenu(User_Input_Strategy* inputFn, Output_Strategy* outputFn);
    ~WorkoutMenu();
    private:
    Menu_State* match_Output_To_Next_Menu(std::string output) override;
    void printMenu() override; 
};

