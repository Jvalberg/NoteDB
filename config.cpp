#include "config.h"
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>

namespace config 
{
	std::string getDefaultPath()
	{
		struct passwd *pwd = getpwuid(getuid());
		return std::string(pwd->pw_dir) + "/.notedb/notedb.conf";
	}
}

bool Config::Read(const std::string& path)
{
	_path = path;
	return read();
}

bool Config::Read(std::string&& path)
{
	_path = path;
	return read();
}

bool Config::read()
{
	std::ifstream fstream(_path);	
	if(!fstream.is_open())
		return false;

	std::string line;
	while ( getline(fstream, line))
	{
		std::string::const_iterator it = std::find(line.begin(), line.end(), ' ');
		if ( it != line.end()) 
		{
			std::string param(line.cbegin(), it);
			std::string value(++it, line.cend());
			_parameters[param] = value;
		}
	}
	return true;
}
std::string Config::getValue(std::string&& param)
{
	return _parameters[param];
}

bool Config::paramExists(std::string&& param)
{
	std::map<std::string, std::string>::iterator it = _parameters.find(param);
	return it != _parameters.end();
}

