all: compile install

install: 
	echo "Instlling..." && sudo sh install.sh && echo "Done."

compile:
	g++ --std=c++11 main.cpp -o NoteWriter

clean:
	rm -rf ~/.notedb
