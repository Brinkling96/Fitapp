#include <catch2/catch.hpp>
#include <array>

#include "TestDB.hpp"
#include "../src/User_Input_Strategy.hpp"
#include "../src/DB_connection.hpp"
#include "../src/SQL_Query.hpp"



//This Test requires that a testdb exists

static TestDB testDB;

TEST_CASE("Total Amount of Reps for an exercise","[Database]"){

    SQL_Query q(    "SELECT COUNT(s.rid)\n"
                    "FROM sets as s, exercise as e\n"
                    "WHERE s.eid = e.eid AND e.name = \'Superman\';\n"
                    );
    testDB.conn->execute(&q);

    REQUIRE( q.result.at(0)[0].as<int>() == 6);
}

TEST_CASE("Average Workout Time","[Database]"){

    SQL_Query q(    "SELECT AVG(q.sum)\n"
                    "FROM (\n"
	                "   SELECT s.date, SUM(s.ms) as sum\n"
	                "   FROM sets as s\n"
	                "   GROUP BY s.date\n"
	                ") as q;\n"
                );
    testDB.conn->execute(&q);

    double output = q.result.at(0)[0].as<double>();

    REQUIRE( (output >= 6249 && output <= 6250) );

}

TEST_CASE("Average time per Exercise","[Database]"){

    SQL_Query q(    "SELECT AVG(q.sum)\n"
                    "FROM (\n"
	                "    SELECT s.sid, SUM(s.ms) as sum\n"
	                "    FROM sets as s, exercise as e\n"
	                "    WHERE e.name = 'Full Body Squat' AND s.eid = e.eid\n"
	                "    GROUP BY s.sid\n"
	                ") as q;\n"
                );
    testDB.conn->execute(&q);

    double output = q.result.at(0)[0].as<double>();

    REQUIRE( (output >= 1222 && output <= 1223));
}

TEST_CASE("Exercise data grouped by day","[Database]"){

    SQL_Query q(    "SELECT *\n"
                    "FROM sets as s, exercise as e\n"
                    "WHERE s.date = '2022-01-14' AND e.eid = s.sid AND e.name= 'Supported Push up';\n"
                );

    testDB.conn->execute(&q);

    REQUIRE( q.result.size() == 5 );
}

TEST_CASE("Exercise reps grouped by day","[Database]"){

    SQL_Query q(    "SELECT count(s.rid)\n" 
                    "FROM sets as s, exercise as e\n"
                    "WHERE s.eid = e.eid AND e.name = 'Superman' AND s.date = \'2022-01-14\';\n"
                );

    testDB.conn->execute(&q);
    REQUIRE( q.result.at(0)[0].as<int>() == 3);

}

TEST_CASE("Workout data given by day","[Database]"){
    
    SQL_Query q(    "SELECT e.name, s.sid, s.rid, s.ms\n" 
                    "FROM sets as s, exercise as e\n"
                    "WHERE s.date = \'2022-01-14\' AND e.eid = s.eid;\n"
                );
    testDB.conn->execute(&q);
    REQUIRE( q.result.size() == 18);
}


