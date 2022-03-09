#include <strings.h>


#include "User_Input_Strategy.hpp"
#include "DB_connection.hpp"
#include "Menus.hpp"



class Coordinator{
    DB_connection conn;
    User_Input_Strategy* normal_inputFn;
    User_Input_Strategy* password_inputFn;
    Output_Strategy* outputFn;

    public:
    Coordinator(User_Input_Strategy* normal_inputFn, User_Input_Strategy* password_inputFn, Output_Strategy* outputFn);
    void Run();
};