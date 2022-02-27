#include "User_Input_Strategy.hpp"


User_Input_Strategy::~User_Input_Strategy(){}

GetLine_Strategy::~GetLine_Strategy(){}

std::string GetLine_Strategy::getInput(){
    std::string in;
    std::getline(std::cin,in);
    return in;
}

Static_Input_Strategy::~Static_Input_Strategy(){}

std::string Static_Input_Strategy::getInput(){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms_to_wait));
    return "Null";
}

Auto_Input_Strategy::~Auto_Input_Strategy(){}

Auto_Input_Strategy::Auto_Input_Strategy(std::string input){
    this->input = input;
}


std::string Auto_Input_Strategy::getInput(){
    return input;
}

GetPass_Strategy::~GetPass_Strategy(){}

std::string GetPass_Strategy::getInput(){
    int rc = 1;
    size_t size = 20;
    char mPass[size];

    while(rc != 0){
        std::memset(mPass, '\0', size);
        rc = ssh_getpass("Database Password : ", mPass, sizeof(size),0,0);
    }
    return std::string(mPass);
}

Output_Strategy::~Output_Strategy(){}

Null_Output_Strategy::~Null_Output_Strategy(){}

void Null_Output_Strategy::output(std::string msg){
    return;
}

Msg_Output_Strategy::~Msg_Output_Strategy(){}

void Msg_Output_Strategy::output(std::string msg){
    std::cout << msg << std::endl;
}