project(FitApp)
cmake_minimum_required(VERSION 3.16.0)

#add_executable(${PROJECT_NAME} tests/connector_Example.cpp)

#target_compile_options(FitApp PRIVATE -c -Wall -g)
#target_link_options(FitApp PRIVATE -lpq -lpqxx -lssh)


set(srcFiles src/clear.cpp src/Coordinator.cpp src/Date.cpp src/DB_connection.cpp src/Menu_Chain_Exception.cpp src/Menu_State.cpp src/Menus.cpp src/Routine.cpp src/SQL_Query.cpp src/User_Input_Strategy.cpp src/WorkoutBuilder.cpp)

set(testFiles tests/testRunner.cpp tests/Coordinator_Tests.cpp tests/Database_Tests.cpp tests/Date_Tests.cpp tests/DB_connection_Tests.cpp tests/Menu_Chain_Tests.cpp tests/QueryBuilder_Tests.cpp tests/routine_Tests.cpp tests/TestDB.cpp tests/WorkoutBuilder_Tests.cpp)

#file(GLOB srcFiles CONFIGURE_DEPENDS "src/*.cpp")
#file(GLOB testFiles CONFIGURE_DEPENDS "tests/*.cpp")

add_executable(Tests ${testFiles} ${srcFiles})
target_compile_options(Tests PRIVATE -c -Wall -g)
target_link_libraries(Tests PRIVATE -lpq -lpqxx -lssh)