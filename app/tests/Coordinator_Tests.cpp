#include "TestDB.hpp"


static TestDB testDB;

TEST_CASE("Coordinate a Workout", "[Coordinator]"){

    Test_Strategy s;

    Coordinator c(s);
    
    c.workout();


}