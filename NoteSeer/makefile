all: compile install

install:
	sudo sh install.sh

compile: 
	g++ --std=c++11 -lboost_system -lboost_filesystem main.cpp arguments.cpp -o NoteSeer 
