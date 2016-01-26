#include "arguments.h"
#include <iostream>
#include <string.h>
#include <vector>

Arguments::Arguments(int argc, char* argv[])
	: _argc(argc), _argv(argv)
{
}


bool Arguments::Parse()
{

	std::string valid_arg("-t");
	if (valid_arg.compare(_argv[1]) != 0)
	{
		return false;
	}

	std::string tags;
	if(_argc == 3){
		tags = _argv[2];
	}
	else if(_argc == 2){
		tags = "*";
	}
	else{
		return false;
	}

	_args["t"] = tags;
	return true;
}
std::string Arguments::getValue(std::string&& arg) {
	return _args[arg];
}

void Arguments::PrintUsage()
{
	std::cout << " =============== NoteSeer =============="<< std::endl;
	std::cout << " NoteSeer is a CLI for the NoteDB."<< std::endl;
	std::cout << " Usage: NoteSeer [options] "<< std::endl;
	std::cout << "   -t   Use the raw database of blobs."<< std::endl;
}
