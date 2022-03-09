#include "WorkoutBuilder.hpp"

WorkoutBuilderException::WorkoutBuilderException(std::string errorMessage): errorMessage{errorMessage} {};

const char * WorkoutBuilderException::what() const throw (){
    return errorMessage.c_str();
}


Workout_Builder::Workout_Builder(std::vector<Exercise> exercises, std::unordered_map<std::string, Workout> presets, User_Input_Strategy* inputFn, Output_Strategy* outputFn)
                                : exercises{exercises},presets{presets},inputFn{inputFn},outputFn{outputFn} {};

Workout_Builder::~Workout_Builder(){};

Workout Workout_Builder::workout_From_Preset(std::string name){
    Workout w = presets[name];
    return w;
}

Workout Workout_Builder::build_Workout(){
    clear();
    outputFn->output("Enter Workout Name:");
    std::string name= inputFn->getInput();
    if (presets.find(name) == presets.end()){
        throw WorkoutBuilderException(  "Workouts with the same name are Not Supported\n"
                                            "Try adding repetition or set number to the name");
    }

    std::vector<Exercise> exerciseList;
    bool building = true;
    while(building){
        clear();
        printExercises();
        printSelected();
        std::string output = inputFn->getInput();
        
        auto pairOut = match_Output_To_Option(output);
        building = pair.first;
        if (pair.second != nullptr){
            Exercise e = *(pair.second);
            exerciseList.push_back(e);
        }

    }
    Workout newWorkout(exerciseList);
    presets[name] = newWorkout;
    return newWorkout;
}


std::pair<bool,Exercise*> Workout_Builder::match_Output_To_Exercise(std::string output){
    int selection = std::stoi(output);//used for Else if
    if(std::string("N").compare(output) == 0){
        try{
            Exercise* e = build_Exercise();
            return std::pair(true,build_Exercise());
        } catch (WorkoutBuilderExeception const &e){
            ouputFn->output(std::string(e.what()));
        } catch (std::invalid_argument const &e){
            ouputFn->output(std::string(e.what()));
        } catch (std::out_of_range const &e){
            ouputFn->output(std::string(e.what()));
        }
        return std::pair(true,nullptr);
    }
    else if( selection>=0 && selection<exercise.size() ){
        return std:pair(true,&(exercise.at(selection)));
    }
    else if(std::string("D").compare(output) == 0){
        return std::pair(false,nullptr)
    }
    else{
        outputFn->output(std::string("Option not found\n"));
        inputFn->getInput();
        return std::pair(true,nullptr);
    }
}

Exercise* Workout_Builder::build_Exercise(){
    clear();
    outputFn->output("Enter Exercise Name:");
    std::string name= inputFn->getInput();

    for(const Exercise& e : this->exercises){
        if (name.compare(e.name) == 0){
            throw WorkoutBuilderException(  "Exercises with the same name are Not Supported\n"
                                            "Try adding repetition or set number to the name");
        }
    }
    outputFn->output("Enter Exercises sets:");
    unsigned short sets = static_cast<unsigned short>(std::stoul(inputFn->getInput()));


    outputFn->output("Enter Exercises reps:");
    unsigned short reps = static_cast<unsigned short>(std::stoul(inputFn->getInput()));

    Exercise e(inputFn,outputFn, name,sets,reps);
    this->exercises.push_back(e);
    return &(this->exercises.at(exercise.size()-1));
}