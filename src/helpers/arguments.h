#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <map>

class Arguments
{
	public:
		Arguments(int argc, char* argv[]);

		bool Parse();
		void PrintUsage();

		std::string getValue(std::string&&);
		int			getArgCount();

	private:
		std::map<std::string, std::string> _args;
		char**	_argv;
		int		_argc;
};
#endif
