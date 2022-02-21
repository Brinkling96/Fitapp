#!/bin/bash

docker network create -d bridge FitAppNet

docker-compose up -d

docker build -t fitapp_cppdev:1.1  ./app 

docker run -dt --name=fitapp_CPPDEV --network=FitAppNet --mount src="$(pwd)"/app,target=/usr/src/app,type=bind fitapp_cppdev:1.1