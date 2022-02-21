#include "DB_connection.hpp"
#include "SQL_Query.hpp"

int No_Pass::getPassword(char* mPass, int size){
    memset(mPass,'\0',size);
    strcpy(mPass,"sean");
    return 0;
}

int User_Input_Pass::getPassword(char* mPass, int size){
    memset(mPass, '\0', size);
    return ssh_getpass("Database Password : ", mPass, sizeof(size),0,0);
}

DB_connection::DB_connection(std::array<char*,5> inputs, Password_Strategy* pass_Strat){
    std::stringstream ss;
    char mPass[20]; //TODO
    int rc = pass_Strat->getPassword(mPass,20);
    if (rc == 0){
        ss << "postgresql://" << inputs[3];
        ss << ":" << mPass << "@" << inputs[1] << ":" << inputs[2] << "/" << inputs[4];
    }
    std::cout << ss.str() << std::endl;
    conn = new pqxx::connection(ss.str().c_str());
}

bool DB_connection::execute(SQL_Query* query){
    try{
        pqxx::work txn(*conn);
        query->result= txn.exec(query->query);
        txn.commit();
    } catch (pqxx::sql_error const &e){
        std::cerr << "SQL error: " <<e.what() <<std::endl;
        std::cerr << "Query was: " <<e.query() <<std::endl;
        return false;
    }
    catch(std::exception const &e){
        std::cerr << "Error: " <<e.what() << std::endl;
        return false;
    }
    return true;
}


