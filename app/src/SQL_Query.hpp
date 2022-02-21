#include <string>
#include <unordered_map>
#include <pqxx/pqxx>

#include "Date.hpp"
#include "Routine.hpp"



struct SQL_Query{
    
    std::string query;
    pqxx::result result;

    public:
    SQL_Query(std::string query) : query{query} {};
    protected:
    SQL_Query(){};
};


struct InsertWorkout: public SQL_Query{    
    InsertWorkout(const Date& date, WorkoutData* data, const std::unordered_map<std::string,int>& exerciseMap, int* s_id);
    friend class Query_Factory;
};



class Query_Factory{ //TODO: Become an Obs to update members?
    private:
    std::unordered_map<std::string,int> exerciseMap;
    int* set_id;
    
    Date getDate();

    public:

    Query_Factory(DB_connection* conn);
    SQL_Query* InsertQuery(WorkoutData* data);
};

