#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <chrono>




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
    std::vector<ExerciseData*> exercises;

    WorkoutData(int num_exercises);
    ~WorkoutData();

};

class Exercise{
    private:
    std::string name;
    unsigned short sets;
    unsigned short reps;
    
    public:

    Exercise(std::string name, unsigned short sets, unsigned short reps);
    
    ExerciseData* DoExercise();

    std::string getName();
};





class Routine{
    private:
    std::vector<Exercise> routine;

    public:
    Routine(std::vector<Exercise> routine);

    WorkoutData* DoRoutine();

};