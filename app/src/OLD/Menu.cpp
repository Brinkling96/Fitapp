#include "Menu.hpp"

UnsupportedOperationException::UnsupportedOperationException(std::string inputCMD) : inputCMD{inputCMD} {};

const char * UnsupportedOperationException::what() const throw (){
    std::stringstream ss;
    ss << "Unsupported Operation \'" << inputCMD << "\'" << std::endl;
    return ss.str().c_str();
}

MenuResult::MenuResult(){};

NormalResult::NormalResult(MenuComponent* next, MenuComponent* prev): next{next}, prev{prev} {}

bool NormalResult::notNull(){
    return true;
}

MenuComponent* NormalResult::getResult(){
    return next;
}

MenuComponent* NormalResult::undo(){
    return prev;
}

ExitResult::ExitResult(MenuComponent* prev): prev{prev} {}

bool ExitResult::notNull(){
    return true;
}

MenuComponent* ExitResult::getResult(){
    exit(EXIT_SUCCESS);
}

MenuComponent* ExitResult::undo(){
    return prev;
}

bool NullResult::notNull(){
    return false;
}

MenuComponent* NullResult::getResult(){
    throw UnsupportedOperationException("Executing result on Null Result object");
}

MenuComponent* NullResult::undo(){
    throw UnsupportedOperationException("Executing result on Null Result object");
}


Menu::Menu(){
    this->inputFn = nullptr;
}

Menu::Menu(std::vector<MenuComponent*> components, User_Input_Strategy* inputFn) : components{components}, inputFn{inputFn} {};


MenuResult* Menu::executeForm(){
    std::string cmd = inputFn->getInput();
    return this->execute(cmd);
}

void Menu::display(){
    for(MenuComponent* m : components){
       m->display();
    }
}

MenuResult* Menu::execute(std::string inputCMD){
    for(MenuComponent* m : components){
        MenuResult* res = m->execute(inputCMD);
        if( res->notNull()){
            return res;
        }throw UnsupportedOperationException("Executing result on Null Result object");
    }
    throw UnsupportedOperationException(inputCMD);
}

MenuItem::MenuItem(std::string description)
            : description{description} 
            {};

void MenuItem::display(){
    std::cout << description << std::endl;
}

MenuCommand::MenuCommand(std::string description,std::string userCMD, MenuResult* result, User_Input_Strategy* inputFn) 
                : MenuItem {description},  
                userCMD{userCMD}, result{result} , inputFn{inputFn}
                {};

MenuResult* MenuCommand::executeForm(){
    std::string cmd = inputFn->getInput();
    return this->execute(cmd);
}

MenuResult* MenuCommand::execute(std::string inputCMD){
    if (inputCMD.compare(userCMD)){
        return result;
    }
    else {
        return new NullResult();
    }
}

MenuDescription::MenuDescription(std::string description) : MenuItem {description} {};

MenuResult* MenuDescription::executeForm(){
    throw UnsupportedOperationException("Executing Form on Menu Description object");
}

MenuResult* MenuDescription::execute(std::string inputCMD){
    return new NullResult();
}

Title::Title(){
    User_Input_Strategy* inputFn = new GetLine_Strategy();
    MenuDescription* name = new MenuDescription(std::string("FitApp Version ") + std::string("1.0.0")); //TODO get version from pramga or Cmake somehow
    this->components.push_back(name);
    MenuDescription* release= new MenuDescription(std::string("Release ") + Date(2022,2,28).toString()); //Get Commit date
    this->components.push_back(release);

    NormalResult* next = new NormalResult(new MainMenu(), this);
    MenuCommand* begin = new MenuCommand("Press Enter to begin!","",next, inputFn);
    this->components.push_back(begin);

    ExitResult* quit = new ExitResult(this);
    MenuCommand* exit= new MenuCommand("Press q to quit","q",quit, inputFn);
    this->components.push_back(exit);
    
    this->inputFn =inputFn;

}

MainMenu::MainMenu(){
    MenuDescription* banner = new MenuDescription(std::string("Main Menu ") + Date(2022,2,28).toString());
    this->components.push_back(banner);

    NormalResult* workout= new NormalResult(nullptr,this);
    MenuCommand* workoutCMD = new MenuCommand("1) Workout!", "1", workout, inputFn);
    this->components.push_back(workoutCMD);

    NormalResult* tutorial = new NormalResult(nullptr, this);
    MenuCommand* tutCMD = new MenuCommand("2) Tutorial","2",tutorial,inputFn);
    this->components.push_back(tutCMD);

    MenuDescription* numberDesc = new MenuDescription("Enter Number to proceed");
    this->components.push_back(numberDesc);

    NormalResult* goBack = new NormalResult(new Title(), this);
    MenuCommand* goBackCMD = new MenuCommand("Enter b to go back to title", "b", goBack,inputFn);
    this->components.push_back(goBackCMD);

    ExitResult* quit = new ExitResult(this);
    MenuCommand* exit = new MenuCommand("Press q to quit","q", quit,inputFn);
    this->components.push_back(exit);
}


