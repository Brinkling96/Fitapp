#include "Menu.hpp"


bool NullResult::notNull(){
    return false;
}

MenuComponent* NullResult::executeResult(){
    throw UnsupportedOperationException("Executing result on Null Result object");
}

MenuComponent* NullResult::undo(){
    throw UnsupportedOperationException("Executing result on Null Result object");
}


const char * UnsupportedOperationException::what() const throw (){
    std::stringstream ss;
    ss << "Unsupported Operation \'" << inputCMD << "\'" << std::endl;
    return ss.str().c_str();
}


MenuResult Menu::executeForm(){
    std::string cmd = inputFn->getInput();
    return this->execute(cmd);
}

MenuResult Menu::execute(std::string inputCMD){
    for(MenuComponent m : components){
        MenuResult res = m.execute(inputCMD);
        if( res.notNull()){
            return res;
        }throw UnsupportedOperationException("Executing result on Null Result object");
    }
    throw UnsupportedOperationException(cmd);
}

MenuCommand::MenuCommand(std::string user_input_command, MenuResult result) : user_input_command{user_input_command}, result{result} {};

MenuResult MenuCommand::executeForm(){
    std::string cmd = inputFn->getInput();
    return this->execute(cmd);
}

MenuResult MenuCommand::execute(std::string inputCMD){
    if (inputCMD.compare(User_input_command)){
        return result;
    }
    else {
        NullResult null;
        return null;
    }
}

MenuDescription::MenuDescription(std::string description) : description{description} {};

MenuResult MenuDescription::executeForm(){
    throw UnsupportedOperationException("Executing Form on Menu Description object");
}

MenuResult execute(std::string inputCMD){
    NullResult null;
    return null;
}

Title::Title(){
    MenuDescription name(std::string("FitApp Version ") + std::string("1.0.0")); //TODO get version from pramga or Cmake somehow
    MenuDescription release(std::string("Release ") + Date(2022,2,28).toString()); //Get Commit date

    MenuResult next;
    next.
    MenuCommand begin("Enter");

}


