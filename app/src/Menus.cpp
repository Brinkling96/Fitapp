#include "Menus.hpp"

TitleMenu::TitleMenu(User_Input_Strategy* inputFn, Output_Strategy* outputFn) : Menu_State{inputFn,outputFn} {};

TitleMenu::~TitleMenu(){}

Menu_State* TitleMenu::match_Output_To_Next_Menu(std::string output){
    if(std::string("").compare(output) == 0){
        return new MainMenu(this->inputFn, this->outputFn);
    }
    else if(std::string("q").compare(output) == 0){
        return new QuitMenu(this->inputFn, this->outputFn);
    }
    else{
        outputFn->output(std::string("Option not found\n"));
        inputFn->getInput();
        return this;
    }
}

void TitleMenu::printMenu(){
    std::stringstream ss;
    ss << "+--------------------------------+" << std::endl;
    ss << "|    FitApp Version 1.0.0        |" << std::endl;
    ss << "|     Release: " << Date(2022,2,28).toString() <<"|"<<std::endl;
    ss << "+--------------------------------+" <<std::endl;
    ss << std::endl;
    ss << "Press Enter to Begin!" << std::endl;
    ss << "Press q to quit" << std::endl;

    outputFn->output(ss.str());
}


QuitMenu::QuitMenu(User_Input_Strategy* inputFn, Output_Strategy* outputFn) : Menu_State{inputFn,outputFn} {};

QuitMenu::~QuitMenu(){};

//TODO maybe this is
Menu_State* QuitMenu::match_Output_To_Next_Menu(std::string output){
    throw MenuStateException("This is a QuitMenu Object. The Coordinator should be exiting now...");
}

void QuitMenu::printMenu(){
    throw MenuStateException("This is a QuitMenu Object. The Coordinator should be exiting now...");
}


MainMenu::MainMenu(User_Input_Strategy* inputFn, Output_Strategy* outputFn) : Menu_State{inputFn,outputFn} {};

MainMenu::~MainMenu(){};

Menu_State* MainMenu::match_Output_To_Next_Menu(std::string output){
    if(std::string("1").compare(output) == 0){
        return new WorkoutMenu(this->inputFn, this->outputFn);
    }
    else if(std::string("2").compare(output) == 0){
        throw MenuStateException("Unsupported Menu.");
    }
    else if(std::string("q").compare(output) == 0){
        return new QuitMenu(this->inputFn, this->outputFn);
    }
    else if(std::string("b").compare(output) == 0){
        return new TitleMenu(this->inputFn, this->outputFn);
    }
    else{
        outputFn->output(std::string("Option not found\n"));
        inputFn->getInput();
        return this;
    }
}

void MainMenu::printMenu(){
    std::stringstream ss;
    ss << "Main Menu " << Date().toString() << std::endl;
    ss << "1) Workout!" << std::endl;
    ss << "2) Tutorial" <<std::endl;
    ss << std::endl;
    ss << "Enter <number> to proceed" << std::endl;
    ss << "Press q to quit" << std::endl;
    ss << "Press b to go back to title" << std::endl;

    outputFn->output(ss.str());
}


WorkoutMenu::WorkoutMenu(User_Input_Strategy* inputFn, Output_Strategy* outputFn) : Menu_State{inputFn,outputFn} {};

WorkoutMenu::~WorkoutMenu(){};

Menu_State* WorkoutMenu::match_Output_To_Next_Menu(std::string output){
    if(std::string("1").compare(output) == 0){
        throw MenuStateException("Unsupported Menu.");
    }
    else if(std::string("2").compare(output) == 0){
        throw MenuStateException("Unsupported Menu.");
    }
    else if(std::string("3").compare(output) == 0){
        throw MenuStateException("Unsupported Menu.");
    }
    else if(std::string("q").compare(output) == 0){
        return new QuitMenu(this->inputFn, this->outputFn);
    }
    else if(std::string("b").compare(output) == 0){
        return new MainMenu(this->inputFn, this->outputFn);
    }
    else{
        outputFn->output(std::string("Option not found\n"));
        inputFn->getInput();
        return this;
    }
}

void WorkoutMenu::printMenu(){
    std::stringstream ss;
    ss << "Workout " << Date().toString() << std::endl;
    ss << "1) Workout from Preset" << std::endl;
    ss << "2) Create Workout Preset" <<std::endl;
    ss << "3) Edit Preset and Exercise" <<std::endl;
    ss << std::endl;
    ss << "Enter <number> to proceed" << std::endl;
    ss << "Press q to quit" << std::endl;
    ss << "Press b to go back to MainMenu" << std::endl;

    outputFn->output(ss.str());
}

