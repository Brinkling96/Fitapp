#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <chrono>

#include "Date.hpp"
#include "User_Input_Strategy.hpp"


//Structs which collect workout data to later be processed by other classes.
struct SetData{
    std::vector<unsigned int> rep_times;

    SetData(int reps);
};

struct ExerciseData{
    std::string name;
    std::vector<SetData*> sets; 

    ExerciseData(std::string name, int num_sets);

    ~ExerciseData();

};

struct WorkoutData{
    const Date* date;
    std::vector<ExerciseData*> exercises;

    WorkoutData(const Date* date, int num_exercises);
    ~WorkoutData();

};







class User_Input_Strategy;
class Output_Strategy;

//In a sense, these classses build WorkoutData structs to later get processed by other classes.
class Exercise{
    private:
    User_Input_Strategy* inputFn;
    Output_Strategy* outputFn;

    std::string name;
    unsigned short sets;
    unsigned short reps;
    
    
    public:
    Exercise(User_Input_Strategy* inputFn, Output_Strategy* outputFn,std::string name, unsigned short sets, unsigned short reps);
    ~Exercise();
    ExerciseData* DoExercise();
    
    private:
    SetData* DoSet(int setNum);

    void printStartExerciseMessage();
    void printStartSetMessage(int setNum);
    void printRepMessage(int repNum);
    unsigned int getRepTime();
    void printSetEndMessage();


};

class Workout{
    private:
    std::vector<Exercise> routine;
    User_Input_Strategy* strategy; 

    public:
    Workout(std::vector<Exercise> routine);

    WorkoutData* DoRoutine();

};