#include <string>
#include <unordered_map>
#include <pqxx/pqxx>


class DB_connection;
class Date;
struct WorkoutData;
struct ExerciseData;
struct SetData;

struct SQL_Query{
    
    std::string query;
    pqxx::result result;

    public:
    SQL_Query(std::string query) : query{query} {};
    protected:
    SQL_Query(){};
};






class Query_Factory{ //TODO: Become an Obs to update members?
    std::unordered_map<std::string,int> exerciseMap;
    int set_id;

    public:
    Query_Factory(std::unordered_map<std::string,int>* exerciseMap, int set_id);
    SQL_Query* InsertWorkoutData(WorkoutData* data);

    private:
    void parseExerciseData(std::stringstream& ss,ExerciseData* e, const Date* date);

    void parseSetData(std::stringstream& ss,SetData* s, const Date* date, const int& e_id );
};

