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


WorkoutData::WorkoutData(const Date* date, int num_exercises){
    exercises.reserve(num_exercises);
    this->date = date;
}

WorkoutData::~WorkoutData(){
    for (auto e: exercises){
        delete e;
    }
    delete date;
}


Exercise::Exercise(User_Input_Strategy* inputFn, Output_Strategy* outputFn, std::string name, unsigned short sets, unsigned short reps)
 : inputFn{inputFn},outputFn{outputFn},name{name},sets{sets},reps{reps} {};

Exercise::~Exercise(){
    delete inputFn;
    delete outputFn;
}

ExerciseData* Exercise::DoExercise(){
    printStartExerciseMessage();
    ExerciseData* exerciseData = new ExerciseData(name, reps);
    for(int setNum =1; setNum <= sets; setNum++){
        SetData* set = DoSet(setNum);
        exerciseData->sets.push_back(set);
    }
    return exerciseData;
}


void Exercise::printStartExerciseMessage(){
    std::stringstream ss;
    ss << "Get ready to do " << name << "s with " << sets << " sets of " << reps << " repetitions" << std::endl;
    outputFn->output(ss.str());
    inputFn->getInput();
}

SetData* Exercise::DoSet(int setNum){
    printStartSetMessage(setNum);
    SetData* set= new SetData(reps); 
    for(int repNum=1; repNum <= reps; repNum++){ 
        printRepMessage(repNum);
        unsigned int repTime = getRepTime();
        set->rep_times.push_back(repTime);
    }
    printSetEndMessage();
    return set;
    
}

void Exercise::printStartSetMessage(int setNum){
    std::stringstream ss; 
    ss << "Set " << setNum <<", press enter to begin" <<std::endl; //1
    outputFn->output(ss.str()); 
    inputFn->getInput(); 
}

void Exercise::printRepMessage(int repNum){
    std::stringstream ss; 
    ss<< "Rep "<< repNum << std::endl;
    outputFn->output(ss.str());
}


unsigned int Exercise::getRepTime(){
    auto start = std::chrono::high_resolution_clock::now();//3
    inputFn->getInput(); //3
    auto stop = std::chrono::high_resolution_clock::now();//3
    return ((unsigned int) std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count());//2
}

void Exercise::printSetEndMessage(){
    std::stringstream ss;
    ss << "Set Complete! Take a quick break then press enter to proceed" << std::endl;
    outputFn->output(ss.str()); 
    inputFn->getInput();
}


Workout::Workout(std::vector<Exercise> routine): routine{routine}{
}

WorkoutData* Workout::DoRoutine(){       
    WorkoutData* WorkoutTime = new WorkoutData(new Date(),routine.size());  
    for(Exercise e: routine){
        WorkoutTime->exercises.push_back(e.DoExercise());
    }
    return WorkoutTime;
}
