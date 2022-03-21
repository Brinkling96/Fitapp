#include "WorkoutBuilder.hpp"

WorkoutBuilderException::WorkoutBuilderException(std::string errorMessage): errorMessage{errorMessage} {};

const char * WorkoutBuilderException::what() const throw (){
    return errorMessage.c_str();
}


Workout_Builder::Container_Index_Option_Chain_Link::Container_Index_Option_Chain_Link(
    std::string prompt, std::vector<Exercise>* container
    )
    : prompt{prompt}, container{container} {};
        

Workout_Builder::Container_Index_Option_Chain_Link::Container_Index_Option_Chain_Link(
    Menu_Chain<OutputMatch>* next_Chain, std::string prompt, std::vector<Exercise>* container
    )
    : Menu_Chain<OutputMatch>(next_Chain), prompt{prompt}, container{container} {}

Workout_Builder::Workout_Builder::Container_Index_Option_Chain_Link::~Container_Index_Option_Chain_Link() {delete next_Chain;};

void Workout_Builder::Container_Index_Option_Chain_Link::setNext(Menu_Chain<OutputMatch>* next_Chain) 
    {this->next_Chain = next_Chain;};

Workout_Builder::OutputMatch Workout_Builder::Container_Index_Option_Chain_Link::select(std::string select) {
    try{
        long unsigned int selection = std::stoul(select);
        if ( selection < container->size() ){
            OutputMatch out = {true,&(container->at(selection))};
            return out; 
        }
    } catch (std::invalid_argument const &e){
        //conversion failed, checking next chain;
    }
    
    return this->next_Chain->select(select);

    
}

std::string Workout_Builder::Container_Index_Option_Chain_Link::toString_Chain(){
    return prompt + this->next_Chain->toString_Chain();
}



Workout_Builder::Workout_Builder
    (std::vector<Exercise> exercises, std::unordered_map<std::string, Workout> presets, 
    User_Input_Strategy* inputFn, Output_Strategy* outputFn
    )
    : exercises{exercises},presets{presets},inputFn{inputFn},outputFn{outputFn} 
{


    OutputMatch end_Option = {false, nullptr};
    Menu_Chain<OutputMatch>* endBuild = new String_Option_Chain_Link<OutputMatch>(std::string("Enter D to finish building the Workout\n"),std::string("D"), end_Option);

    OutputMatch new_Option = {true, nullptr};
    Menu_Chain<OutputMatch>* newExercise = new String_Option_Chain_Link<OutputMatch>(endBuild,std::string("Enter N to create new Exercise\n"),std::string("N"), new_Option);

    this->options_Chain= new Container_Index_Option_Chain_Link(newExercise,std::string("Enter <number> to select Exercise\n"),&(this->exercises));

};

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
        throw WorkoutBuilderException(      "Workouts with the same name are Not Supported\n"
                                            "Try adding repetition or set number to the name");
    }

    std::vector<Exercise> exerciseList;
    bool building = true;
    while(building){
        clear();
        std::stringstream ss;
        ss << stringify_Exercises();
        ss << "\n";
        ss << options_Chain->toString_Chain();
        ss << "\n";
        ss << stringify_Selected_Exercises(name,exerciseList);

        outputFn->output(ss.str());

        std::string output = inputFn->getInput();
        
        OutputMatch user_sel = match_Output_To_Exercise(output);
        building = user_sel.moreExercises;
        if (user_sel.sel_Exercises == nullptr && building){
            try{
                Exercise e = *(build_Exercise());
                exerciseList.push_back(e);
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
        } else if (user_sel.sel_Exercises != nullptr && building ) {
            exerciseList.push_back(*(user_sel.sel_Exercises));
        }
    }
    Workout newWorkout(exerciseList);
    presets[name] = newWorkout;
    return newWorkout;
}


Workout_Builder::OutputMatch Workout_Builder::match_Output_To_Exercise(std::string user_input){
    try{
        return options_Chain->select(user_input);
    } catch (Menu_Chain_Exception const &e){
        outputFn->output(std::string("Option not found\n"));
        inputFn->getInput();
        OutputMatch out = {true,nullptr};
        return out;
    }
}

/*
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
*/

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

std::string Workout_Builder::stringify_Exercises(){
    std::stringstream ss;
    ss <<   "Workout Builder Menu\n\n" 
            "Exercises: \n";
    for(long unsigned int i = 0; i < exercises.size(); i++){
        ss << i << ") " << exercises.at(i).getName() << "\n";
    }

    return ss.str();
}
    
std::string Workout_Builder::stringify_Selected_Exercises(std::string name, std::vector<Exercise> elist){
    std::stringstream ss;
    ss <<   "Workout Name: " << name << "\n" 
            "Selected Exercises: ";
    if (elist.size() == 0){
        ss << "None, ";
    } else {
        for(long unsigned int i = 0; i < elist.size(); i++){
            ss << elist.at(i).getName() << ", ";
        }
    }
    ss.seekp(-2,ss.cur);
    ss << ".";
    return ss.str();
}
