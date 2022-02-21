#include "Routine.hpp"

SetData::SetData(int reps){
    rep_times.reserve(reps);
}

ExerciseData::ExerciseData(std::string name, int num_sets){
    this->name = name;
    sets.reserve(num_sets);
}

ExerciseData::~ExerciseData(){
    for(auto set: sets){
        delete set;
    }
}

WorkoutData::WorkoutData(int num_exercises){
    exercises.reserve(num_exercises);
}

WorkoutData::~WorkoutData(){
    for (auto e: exercises){
        delete e;
    }
}


Exercise::Exercise(std::string name, unsigned short sets, unsigned short reps) : name{name},sets{sets},reps{reps} {};

ExerciseData* Exercise::DoExercise(){
    std::cout << "Get ready to do " << name << "s with " << sets << " sets of " << reps << " repetitions" << std::endl;
    std::cin.get();
    ExerciseData* exerciseData = new ExerciseData(name, reps);
    for(int i =1; i <= sets; i++){
        std::cout << "Set " << i <<", press enter to begin" <<std::endl;
        std::cin.get();
        SetData* set= new SetData(reps);
        for(int j=1; j <= reps; j++){
            std::cout<< "Rep "<< j << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            std::cin.get();
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
            set->rep_times.push_back(duration.count());
        }
        
        exerciseData->sets.push_back(set);
        std::cout<<"Set over! Hit Enter then take a quick break" <<std::endl;
        std::cin.get();
    }
    return exerciseData;
}

std::string Exercise::getName(){
    return name;
} 


Routine::Routine(std::vector<Exercise> routine): routine{routine}{
}

WorkoutData* Routine::DoRoutine(){       
    WorkoutData* WorkoutTime = new WorkoutData(routine.size());  
    for(Exercise e: routine){
        WorkoutTime->exercises.push_back(e.DoExercise());
    }
    return WorkoutTime;
}
