FROM gcc:latest

COPY . /usr/src/FitApp

WORKDIR /usr/src/FitApp

RUN apt update ; \
apt install; \
apt install libpq-dev \
libpqxx-dev \
libssh-dev  \
gdb \
sudo \
cmake \
catch2 \
git -y; 
#sudo passwd root 'sean';

