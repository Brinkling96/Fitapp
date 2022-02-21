#include <sstream>

#include "SQL_Query.hpp"

InsertWorkout::InsertWorkout(const Date& date, WorkoutData* data, const std::unordered_map<std::string,int>& exerciseMap, int* s_id){
    
    std::stringstream ss;
    ss << "INSERT INTO " << "Workout " << "VALUES "
    << "(\'" << date.toString() <<"\',"<<"{";
    for (ExerciseData* e: data->exercises){
        const int e_id = exerciseMap.at(e->name);
        ss << e_id << ",";
    }
    ss.seekp(-1,ss.cur);
    ss << "});\n";
    ss << "INSERT INTO " << "repetition " << "VALUES ";
    for (ExerciseData* e: data->exercises){
        auto& sets = e->sets;
        const int e_id = exerciseMap.at(e->name);
        for (SetData* set : sets){
            (*s_id)++;
            const std::vector<unsigned int>& rep_times= set->rep_times;
            int i =1;
            for (unsigned int rep : rep_times){
                ss << "( "<< *s_id << "," << i++ << "," << e_id << "," << rep << "),\n";
            }
        }
    }
    ss.seekp(-2,ss.cur);
    ss << ";\n";
    query= ss.str();
}


Date Query_Factory::getDate(){
    return Date();
}

Query_Factory::Query_Factory(DB_connection* conn){
    SQL_Query q(    "SELECT *\n"
                    "FROM exercise;");
    conn->execute(&q);
    for(auto row : q.result){
        this->exerciseMap[row[1].as<std::string>()]=row[0].as<int>();
    }

    SQL_Query q(    "SELECT s.sid\n"
                    "FROM sets\n"
                    "ORDER BY s.sid DESC;");
    conn->execute(&q);
    this->set_id = new int(q.result.at(0).at(0));
}

SQL_Query* Query_Factory::InsertQuery(WorkoutData* data){
    return new InsertWorkout(getDate(),data,exerciseMap,set_id);