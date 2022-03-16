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
    std::pair<bool,Exercise*> match_Output_To_Exercise(std::string output);
    Exercise* build_Exercise();
    void printExercises();
    void printSelected(std::string name, std::vector<Exercise> elist);
};