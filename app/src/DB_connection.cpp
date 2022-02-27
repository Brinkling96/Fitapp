#include "DB_connection.hpp"

DB_connection::DB_connection(std::array<const char*,5> inputs, User_Input_Strategy* inputFn, Output_Strategy* outputFn){
    std::stringstream ss;
    std::string pass = inputFn->getInput();
    ss << "postgresql://" << inputs[3];
    ss << ":" << pass << "@" << inputs[1] << ":" << inputs[2] << "/" << inputs[4];
    outputFn->output(ss.str());
    conn = new pqxx::connection(ss.str().c_str());
}

DB_connection::~DB_connection(){
    delete conn;
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

