#include "arguments.h"
#include <iostream>
#include <string.h>

Arguments::Arguments(int argc, char* argv[])
	: _argc(argc), _argv(argv)
{
}


bool Arguments::Parse()
{
	if (_argc != 2)
		return false;

	std::string valid_arg("-r");
	if (valid_arg.compare(_argv[1]) != 0)
	{
		return false;
	}

	_args["r"] = "";
	return true;
}

void Arguments::PrintUsage()
{
	std::cout << " =============== NoteSeer =============="<< std::endl;
	std::cout << " NoteSeer is a CLI for the NoteDB."<< std::endl;
	std::cout << " Usage: NoteSeer [options] "<< std::endl;
	std::cout << "   -r   Use the raw database of blobs."<< std::endl;
}
