#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <chrono>

class Date;


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


class Exercise_Stragety{
    public:
    virtual ExerciseData* DoExercise() = 0;
};

class User_Input_Stragety : public Exercise_Stragety{
    public:
    ExerciseData* DoExercise() override;
};

class Static_Stragety : public Exercise_Stragety{
    ExerciseData* data;
    public:
    Static_Stragety(ExerciseData* data);
    ExerciseData* DoExercise() override;
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