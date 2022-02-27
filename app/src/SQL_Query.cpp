#include "SQL_Query.hpp"

Query_Factory::Query_Factory(std::unordered_map<std::string,int>* exerciseMap, int set_id) : exerciseMap{(*exerciseMap)},set_id{set_id} {
}


void Query_Factory::parseExerciseData(std::stringstream& ss, ExerciseData* e, const Date* date) {
    auto& sets = e->sets;
    int e_id = exerciseMap[e->name];
    for (SetData* set : sets){
            parseSetData(ss,set,date,e_id);
    }
}


void Query_Factory::parseSetData(std::stringstream& ss, SetData* s, const Date* date, const int& e_id){
    this->set_id++;
    int rep_count =1;
    const std::vector<unsigned int>& rep_times= s->rep_times;
    for (unsigned int rep_time : rep_times){
        ss << "(\'" << date->toString() <<"\'," << e_id << "," << this->set_id << "," << rep_count++ << "," <<  rep_time << "),\n";
    }
}


SQL_Query* Query_Factory::InsertWorkoutData(WorkoutData* data){
    std::stringstream ss;
    ss << "INSERT INTO sets VALUES ";

    for (ExerciseData* e: data->exercises){
       parseExerciseData(ss,e,data->date);
    }
    ss.seekp(-2,ss.cur);
    ss << ";\n";
    return new SQL_Query(ss.str());
}