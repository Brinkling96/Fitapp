#!/bin/bash

net=FitAppNet
image=fitapp_cppdev:1.1
container=fitapp_CPPDEV

docker network create -d bridge $net

docker-compose up -d

docker build -t $image  ./app 

docker run -dt --name=$container --network=$net --mount src="$(pwd)"/app,target=/usr/src/FitApp,type=bind $image

docker exec -ti $container bash

