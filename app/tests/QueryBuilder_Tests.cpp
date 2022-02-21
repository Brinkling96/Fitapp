#include <catch2/catch.hpp>

#include "../src/SQL_Query.hpp"



struct TestWorkout{
    WorkoutData* data;

    TestWorkout(){
        SetData* set1 = new SetData(3);
        set1->rep_times.push_back(1);
        set1->rep_times.push_back(2);
        set1->rep_times.push_back(3);

        SetData* set2 = new SetData(2);
        set2->rep_times.push_back(14);
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



        data = new WorkoutData(2);
        data->exercises.push_back(e1);
        data->exercises.push_back(e2);
    }

    ~TestWorkout(){
        delete data;
    }
};


TEST_CASE("Build Insert Workout","[Query_Builder]"){
    TestWorkout t;

    int* s_id = new int();
    *s_id= 0;

    SQL_Query* q = new InsertWorkout(Date(2022,1,14),t.data, {{"test0",0},{"test1",1}},  s_id );


    std::string output = q->query;


    std::string expected = "INSERT INTO Workout VALUES (\'2022-1-14\',{0,1});\nINSERT INTO repetition VALUES ( 1,1,0,1),\n( 1,2,0,2),\n( 1,3,0,3),\n( 2,1,0,14),\n( 2,2,0,15),\n( 3,1,1,26),\n( 3,2,1,27),\n( 3,3,1,28),\n( 4,1,1,39),\n( 4,2,1,310);\n";

    REQUIRE(output.compare(expected) == 0);

}



