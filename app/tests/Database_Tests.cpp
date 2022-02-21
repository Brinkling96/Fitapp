#include <catch2/catch.hpp>

#include "../src/DB_connection.hpp"
#include "../src/SQL_Query.hpp"

//This Test requires that a testdb exists

static std::array<char*,5> inputs = {"I am the exe name","testDB","5433","sean","testdb"};

struct TestDB{
    DB_connection* conn;

    TestDB(){
        //create conn to testdb
        No_Pass strategy;
        this->conn = new DB_connection(inputs,&strategy);
        //Put data into test db
        createTestTables();
        insertData();
    }

    ~TestDB(){
        SQL_Query q(    "DROP TABLE IF EXISTS sets;\n"
                        "DROP TABLE IF EXISTS exercise;\n");
        conn->execute(&q);
        delete conn;
    }
    
    private:

    void createTestTables(){
        //populate db with test data
        SQL_Query q(    "DROP TABLE IF EXISTS sets;\n"
                        "DROP TABLE IF EXISTS exercise;\n"

                        "CREATE TABLE exercise (\n"
	                    "eid serial PRIMARY KEY,\n"
	                    "name varchar(100) NOT NULL,\n"
	                    "sets int NOT NULL,\n"
	                    "reps int NOT NULL,\n"
	                    "UNIQUE(name,sets,reps)\n"
                        ");\n"

                        
                        "CREATE TABLE sets(\n"
                        "date date,\n"
                        "eid int,\n"
                        "sid int,\n"
                        "rid smallint,\n"
                        "ms int,\n"
                        "PRIMARY KEY (sid,rid),\n"
                        "CONSTRAINT fk_exercise\n"
                        	"FOREIGN KEY(eid)\n"
                        	"REFERENCES Exercise(eid)\n"
                        	"ON DELETE RESTRICT\n"
                        ");"
                        
                        
                        );
        conn->execute(&q);

    }

    void insertData(){
        SQL_Query q(    "INSERT INTO exercise VALUES\n"
                        "(DEFAULT,'Full Body Squat',5,10),\n"
                        "(DEFAULT,'Supported Push up',5,10),\n"
                        "(DEFAULT,'Superman',5,10),\n"
                        "(DEFAULT,'Crunches',5,20);\n"

                        "INSERT INTO sets VALUES\n"
                        "('2022-1-14',1,1,1,300),\n"
                        "('2022-1-14',1,1,2,301),\n"
                        "('2022-1-14',1,1,3,306),\n"
                        "('2022-1-14',1,1,4,310),\n"
                        "('2022-1-14',1,1,5,305),\n"
                        "('2022-1-14',2,2,1,460),\n"
                        "('2022-1-14',2,2,2,463),\n"
                        "('2022-1-14',2,2,3,464),\n"
                        "('2022-1-14',2,2,4,461),\n"
                        "('2022-1-14',2,2,5,466),\n"
                        "('2022-1-14',3,3,1,666),\n"
                        "('2022-1-14',3,3,2,668),\n"
                        "('2022-1-14',3,3,3,663),\n"
                        "('2022-1-14',4,4,1,235),\n"
                        "('2022-1-14',4,4,2,231),\n"
                        "('2022-1-14',4,4,3,235),\n"
                        "('2022-1-14',4,4,4,238),\n"
                        "('2022-1-14',4,4,5,232),\n"
                        "('2022-1-15',1,5,1,307),\n"
                        "('2022-1-15',1,5,2,306),\n"
                        "('2022-1-15',1,5,3,310),\n"
                        "('2022-1-15',2,6,1,464),\n"
                        "('2022-1-15',2,6,2,464),\n"
                        "('2022-1-15',2,6,3,469),\n"
                        "('2022-1-15',3,7,1,662),\n"
                        "('2022-1-15',3,7,2,669),\n"
                        "('2022-1-15',3,7,3,667),\n"
                        "('2022-1-15',4,8,1,237),\n"
                        "('2022-1-15',4,8,2,238),\n"
                        "('2022-1-15',4,8,3,235),\n"
                        "('2022-1-15',4,8,4,231),\n"
                        "('2022-1-15',4,8,5,236);\n");
        conn->execute(&q);
    }
};

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

