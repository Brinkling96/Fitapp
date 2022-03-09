#include "Coordinator.hpp"


static std::array<const char*,5> inputs = {"I am the exe name","testDB","5433","sean","testdb"};


Coordinator::Coordinator(User_Input_Strategy* normal_inputFn, User_Input_Strategy* password_inputFn, Output_Strategy* outputFn): 
                        conn{inputs, password_inputFn,outputFn},
                        normal_inputFn{normal_inputFn}, password_inputFn{password_inputFn}, outputFn{outputFn} 
                        {}


void Coordinator::Run(){
    Menu_State* state = new TitleMenu(this->normal_inputFn,this->outputFn);
    for(int i =0; i < 10; i++){
        try{
            Menu_State* temp = state->runMenu();
            delete state;
            state = temp;
        } catch (MenuStateException const &e){
            int res = strcmp("This is a QuitMenu Object. The Coordinator should be exiting now...",e.what());
            if(res != 0){   
                throw e;
            } else {
                break;
            }
        }
    }
    delete state;
    return;
}



