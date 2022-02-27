#include "TestDB.hpp"

static std::array<const char*,5> inputs = {"I am the exe name","testDB","5433","sean","testdb"};


TestDB::TestDB(){
    //create conn to testdb
    User_Input_Strategy* inputFn = new Auto_Input_Strategy(std::string("sean")); 
    Output_Strategy* outputFn = new Null_Output_Strategy();
    this->conn = new DB_connection(inputs,inputFn,outputFn);
    delete inputFn;
    delete outputFn;
    //Put data into test db
    createTestTables();
    insertData();
}
TestDB::~TestDB(){
    SQL_Query q(    "DROP TABLE IF EXISTS sets;\n"
                    "DROP TABLE IF EXISTS exercise;\n"
                    "DROP TABLE IF EXISTS test;\n");
    conn->execute(&q);
    delete conn;
}

void TestDB::createTestTables(){
    //populate db with test data
    SQL_Query q(    "DROP TABLE IF EXISTS sets;\n"
                    "DROP TABLE IF EXISTS exercise;\n"
                    "DROP TABLE IF EXISTS test;\n"

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
                    ");\n"

                    
                    "CREATE TABLE test( id int, name varchar(25), date Date);"
                );
    conn->execute(&q);

}
void TestDB::insertData(){
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

