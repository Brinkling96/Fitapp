#include <catch2/catch.hpp>
#include <string.h>
#include <vector>
#include <unordered_map>

#include "../src/Routine.hpp"
#include "../src/WorkoutBuilder.hpp"


TEST_CASE("Build_Workout","[WorkoutBuilder]"){
    Exercise squat(new GetLine_Strategy(), new Msg_Output_Strategy(),"Full Body Squat", 5, 10);
    Exercise pushup(new GetLine_Strategy(), new Msg_Output_Strategy(),"Assisted Push up", 5, 10);
    Exercise superman(new GetLine_Strategy(), new Msg_Output_Strategy(),"Superman", 5, 10);
    Exercise crunches(new GetLine_Strategy(), new Msg_Output_Strategy(),"Crunches", 5, 20);

    std::vector<Exercise> elist;

    elist.push_back(squat);
    elist.push_back(pushup);
    elist.push_back(superman);
    elist.push_back(crunches);

    std::unordered_map<std::string, Workout> presets;

    Workout w(elist);

    std::string key = std::string("Default");
    presets[key] = w;

    Workout_Builder workout_builder(elist,presets, new GetLine_Strategy(), new Msg_Output_Strategy());


    Workout test = workout_builder.build_Workout();

    REQUIRE(true);

}