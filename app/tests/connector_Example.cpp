#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>
#include <pqxx/pqxx>

#include "DB_connection.hpp"






int main(int argc, char* argv[])
{
    std::array<int, 5> wCol = {4,15,18,8,12};
    return 0;
  
/*
    try {
        std::unique_ptr<pqxx::connection> conn = connectToDB(argc,argv);
        pqxx::work txn(*conn);
        pqxx::result res{txn.exec("select id, name from player")};
        
        if ( ! res.empty() ){
            int totCol = res.columns();
            std::cout << "+----+"<<std::endl;

            std::cout<< "|"; 
            for (int i = 0; i < totCol; i++){
                std::cout << res.column_name(i) << "|";
            }

            std::cout<<std::endl;
            std::cout <<"+-----+" <<std::endl;

            for (const auto& row: res) {
                std::cout<<row[0].as<int>()<<std::endl;
            }
            std::cout <<"+-----+" <<std::endl;
        }
        txn.commit();
    }
    catch (pqxx::sql_error const &e){
        std::cerr << "SQL error: " <<e.what() <<std::endl;
        std::cerr << "Query was: " <<e.query() <<std::endl;
        return 2;
    }

    catch(std::exception const &e){
        std::cerr << "Error: " <<e.what() << std::endl;
        return 1;
    }


    return 0;
    */
}