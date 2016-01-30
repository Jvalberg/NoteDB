#include "logger.h"
#include <exception>
#include <iostream>
#include <string>
#include <sstream>

#include <fstream>
#include <ctime>

static std::ostream* _OUT = nullptr;

std::string getTime()
{
	std::time_t curr= std::time(0);
	struct tm* now = std::localtime( &curr );
	std::stringstream s;
	s << now->tm_mday << "/" << 
		( now->tm_mon + 1) << "/" << 
		( now->tm_year - 100 ) << "-" <<
		now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	return s.str();
}

std::ostream& logger::LOG(logger::LEVEL level){ 
	std::string prefix;
	prefix = "[" + getTime();

	switch(level){

		case logger::LEVEL::INFO :
			prefix += "] [INFO]: ";
			break;
		case logger::LEVEL::DEBUG :
			prefix += "] [DEBUG]: ";
			break;
		case logger::LEVEL::TRACE :
			prefix += "] [TRACE]: ";
			break;
		case logger::LEVEL::ERROR :
			prefix += "] [ERROR]: ";
			break;
		case logger::LEVEL::FATAL :
			prefix += "] [FATAL]: ";
			break;
	}

	if(_OUT != nullptr)
	{
		return *_OUT << prefix;
	}

	return std::cout << prefix;
}
bool logger::setFileOutput(const std::string& filepath) {
	std::ofstream* fstream = new std::ofstream;
	fstream->open(filepath, std::ios::app);
	if(!fstream->is_open()) {
		delete fstream;
		_OUT = nullptr;
		return false;
	}
	_OUT = fstream;
	return true;
}

bool logger::setConsoleOutput() {
	if(_OUT != nullptr) {
		delete _OUT;
		_OUT = nullptr;
	}
	return true;
}

bool logger::clearLines(int numberLines) { 
	for (int i = 0; i < numberLines; ++i) {
		*_OUT << std::endl;
	}
	return true;
}
