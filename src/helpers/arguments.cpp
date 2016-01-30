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
	int current = 1;
	while(current < _argc){
		std::string flag(_argv[current]);	

		if(current + 1 < _argc)
		{
			++current;
			std::string next(_argv[current]);
			if(next.front() == '-')
			{
				_args[flag] = "";
				_args[next] = "";
			}
			else 
			{
				_args[flag] = next;
			}
		}
		else {
			_args[flag] = "";
		}
		++current;
	}
	return true;
}

std::map<std::string, std::string>& Arguments::getArgs() {
	return _args;
}
