#include <catch2/catch.hpp>

#include "../src/SQL_Query.hpp"
#include "../src/Date.hpp"
#include "../src/Routine.hpp"



struct TestWorkout{
    WorkoutData* data;

    TestWorkout(){
        SetData* set1 = new SetData(3);
        set1->rep_times.push_back(1);
        set1->rep_times.push_back(2);
        set1->rep_times.push_back(3);

        SetData* set2 = new SetData(2);
        set2->rep_times.push_back(14)
;
        set2->rep_times.push_back(15);

        ExerciseData* e1 = new ExerciseData(std::string("test0"),2);
        e1->sets.push_back(set1);
        e1->sets.push_back(set2);

        SetData* set3 = new SetData(3);
        set3->rep_times.push_back(26);
        set3->rep_times.push_back(27);
        set3->rep_times.push_back(28);

        SetData* set4 = new SetData(2);
        set4->rep_times.push_back(39);
        set4->rep_times.push_back(310);

        ExerciseData* e2 = new ExerciseData(std::string("test1"),2);
        e2->sets.push_back(set3);
        e2->sets.push_back(set4);



        data = new WorkoutData(new Date(2022,1,14),2);
        data->exercises.push_back(e1);
        data->exercises.push_back(e2);
    }

    ~TestWorkout(){
        delete data;
    }
};


TEST_CASE("Build Insert Workout","[Query_Builder]"){
    TestWorkout t;
    std::unordered_map<std::string,int> exerciseMap = {{"test0",0},{"test1",1}};
    Query_Factory f(&exerciseMap, 0);


    SQL_Query* q = f.InsertWorkoutData(t.data);

    std::string output = q->query;

    //date,eid,sid,rid,ms
    std::string expected = "INSERT INTO sets VALUES (\'2022-1-14\',0,1,1,1),\n(\'2022-1-14\',0,1,2,2),\n(\'2022-1-14\',0,1,3,3),\n(\'2022-1-14\',0,2,1,14),\n(\'2022-1-14\',0,2,2,15),\n(\'2022-1-14\',1,3,1,26),\n(\'2022-1-14\',1,3,2,27),\n(\'2022-1-14\',1,3,3,28),\n(\'2022-1-14\',1,4,1,39),\n(\'2022-1-14\',1,4,2,310);\n";

    REQUIRE(output.compare(expected) == 0);

    delete q;

}




