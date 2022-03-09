#pragma once


#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <exception>
#include <utility>
#include <sstream>

#include "User_Input_Strategy.hpp"
#include "Routine.hpp"
#include "clear.hpp"


class WorkoutBuilderException: public std::exception{
    
    std::string errorMessage;
    public:
    WorkoutBuilderException(std::string errorMessage);
    const char * what() const throw ();
};

class Workout_Builder{
    std::vector<Exercise> exercises;
    std::unordered_map<std::string,Workout> presets;
    User_Input_Strategy* inputFn;
    Output_Strategy* outputFn;

    public:
    Workout_Builder(std::vector<Exercise> exercises, std::unordered_map<std::string, Workout> presets, User_Input_Strategy* inputFn, Output_Strategy* outputFn);
    ~Workout_Builder();
    Workout workout_From_Preset(std::string name);
    Workout build_Workout();

    private:
    std::pair<bool,Exercise*> match_output_to_Exercise(std::string output);
    Exercise* build_Exercise();

    void printExercises(){
        std::stringstream ss;
        for(int i = 0; i < exercises.size(); i++){
            ss << i << ") " << exercises.at(i).getName() << "\n";
        }
        outputFn->output(ss.str());
    }
    
    void printSelected(){
        std::stringstream ss;
        ss << "\nSelected Exercises: ";
        for(Exercise &e: exercises){
            ss << e.getName()<< ", ";
        }
        ss.seekp(-2,ss.cur);
        ss << ".\n";
    }


};