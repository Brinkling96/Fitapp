#!/bin/bash

docker network create -d bridge FitAppNet

docker-compose up -d

docker build -t fitapp_cppdev:1.1 --network=FitAppNet ./app 

docker run -dt --name=fipapp_CPPDEV --mount src="$(pwd)"/app,target=/usr/src/app,type=bind fitapp_cppdev:1.1