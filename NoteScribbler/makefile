all: compile install

install: 
	sudo sh install.sh 

compile:
	g++ --std=c++11 main.cpp -o NoteScribbler

clean:
	rm -rf ~/.notedb
