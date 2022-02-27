#include <catch2/catch.hpp>
#include <string.h>
#include <vector>

#include "../src/Routine.hpp"



/*
TEST_CASE("Build Workout","[Workout]"){
    Exercise squat("Full Body Squat", 5, 10);
    //Exercise pushup("Assisted Push up", 5, 10);
    //Exercise superman("Superman", 5, 10);
    //Exercise crunches("Crunches", 5, 20);

    std::vector<Exercise> n;
    n.push_back(squat);
    //n.push_back(pushup);
   // n.push_back(superman);
    //n.push_back(crunches);

    Workout normal(n);
    
    WorkoutData* data = normal.DoRoutine();

    auto x = data->exercises.at(0)->sets.at(0)->rep_times.at(0);

    delete data;

    REQUIRE(true);
}
*/
