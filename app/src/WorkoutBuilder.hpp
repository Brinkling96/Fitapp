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
#include "Menu_Chain.hpp"

class WorkoutBuilderException: public std::exception{
    
    std::string errorMessage;
    public:
    WorkoutBuilderException(std::string errorMessage);
    const char * what() const throw ();
};





class Workout_Builder{

    struct OutputMatch{
        bool moreExercises;
        Exercise* sel_Exercises;
    };

    class Container_Index_Option_Chain_Link : public Menu_Chain<OutputMatch>{
        std::string prompt;
        std::vector<Exercise>* container;

        public:
        Container_Index_Option_Chain_Link(std::string prompt, std::vector<Exercise>* container);
        Container_Index_Option_Chain_Link(Menu_Chain<OutputMatch>* next_Chain, std::string prompt, std::vector<Exercise>* container);
        ~Container_Index_Option_Chain_Link();

        void setNext(Menu_Chain<OutputMatch>* next_Chain) override;
        OutputMatch select(std::string select) override;
        std::string toString_Chain() override;

    };

    std::vector<Exercise> exercises;
    std::unordered_map<std::string,Workout> presets;

    Menu_Chain<OutputMatch>* options_Chain;
    
    User_Input_Strategy* inputFn;
    Output_Strategy* outputFn;

    public:
    Workout_Builder(std::vector<Exercise> exercises, std::unordered_map<std::string, Workout> presets, User_Input_Strategy* inputFn, Output_Strategy* outputFn);
    ~Workout_Builder();
    Workout workout_From_Preset(std::string name);
    Workout build_Workout();

    private:
    OutputMatch match_Output_To_Exercise(std::string output);
    Exercise* build_Exercise();
    std::string stringify_Exercises();
    std::string stringify_Selected_Exercises(std::string name, std::vector<Exercise> elist);
};
