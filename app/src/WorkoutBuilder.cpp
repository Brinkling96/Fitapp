#include "WorkoutBuilder.hpp"

//TODO ideas, make an workout builder helper object which coordinates the


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
    outputFn->output(   "Workout Builder Menu\n\n"    
                        "Enter Workout Name:");
    std::string name= inputFn->getInput();
    if (presets.find(name) != presets.end()){
        throw WorkoutBuilderException(  "Workouts with the same name are Not Supported\n"
                                            "Try adding repetition or set number to the name");
    }

    std::vector<Exercise> exerciseList;
    bool building = true;
    while(building){
        clear();
        printExercises();
        printSelected(name,exerciseList);
        std::string output = inputFn->getInput();
        
        std::pair<bool,Exercise*> pairOut = match_Output_To_Exercise(output);
        building = pairOut.first;
        if (pairOut.second != nullptr){
            Exercise e = *(pairOut.second);
            exerciseList.push_back(e);
        }

    }
    Workout newWorkout(exerciseList);
    presets[name] = newWorkout;
    return newWorkout;
}


std::pair<bool,Exercise*> Workout_Builder::match_Output_To_Exercise(std::string output){
    long unsigned int selection;
    bool stoul_Conversion = true;
    try{
        selection = std::stoul(output);//used for Else if
    } catch (std::invalid_argument const &e){
        stoul_Conversion = false;
    }
    if(std::string("N").compare(output) == 0){
        //throw std::runtime_error("Unsupported Operation. This function needs refactoring to not add to menu");
        try{
            Exercise* e = build_Exercise();
            return std::pair(true,e);
        } catch (WorkoutBuilderException const &e){
            outputFn->output(std::string(e.what()));
            inputFn->getInput();
        } catch (std::invalid_argument const &e){
            outputFn->output(std::string(e.what()));
            inputFn->getInput();
        } catch (std::out_of_range const &e){
            outputFn->output(std::string(e.what()));
            inputFn->getInput();
        }
        return std::pair(true,nullptr);
    }
    else if( (stoul_Conversion) && (selection < exercises.size()) ){
        return std::pair(true,&(exercises.at(selection)));
    }
    else if(std::string("D").compare(output) == 0){
        return std::pair(false,nullptr);
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

    for(Exercise& e : this->exercises){
        if (name.compare(e.getName()) == 0){
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
    return &(this->exercises.at(exercises.size()-1));
}

void Workout_Builder::printExercises(){
        std::stringstream ss;
        ss <<   "Workout Builder Menu\n\n" 
                "Exercises: \n";
        for(long unsigned int i = 0; i < exercises.size(); i++){
            ss << i << ") " << exercises.at(i).getName() << "\n";
        }

        ss <<   "\n"
                "Enter <number> to select Exercise\n"
                "Enter D to finish Workout\n"
                "Enter N to create new Exercise\n";
        outputFn->output(ss.str());
    }
    
    void Workout_Builder::printSelected(std::string name, std::vector<Exercise> elist){
        std::stringstream ss;
        ss <<   "Workout Name: " << name << "\n" 
                "Selected Exercises: ";
        if (elist.size() == 0){
            ss << "None, ";
        }
        for(Exercise &e: elist){
            ss << e.getName()<< ", ";
        }
        ss.seekp(-2,ss.cur);
        ss << ".";
        outputFn->output(ss.str());
    }