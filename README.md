# Fitapp
Workout tracker using Docker, Postgres and Cpp

#Dependencies
Docker version 20.10.12 : https://docs.docker.com/engine/install/
Docker-compose 1.29.2 : https://docs.docker.com/compose/install/
Git version 2.25.1

#Installation guide
After downloading the Dependancies, clone the latest main branch.

run chmod +x ./setup_dev.sh

This simple script sets up the docker containers and enters the user into the CPP development container.

run ./setup_dev.sh

After entering the container, we need to compile the code and test its functionality

run chmod +x ./compileAndTest.sh

This script builds the project using cmake and make, and runs the written tests.

run ./compileAndTest.sh

All test should pass!

More coming soon.


