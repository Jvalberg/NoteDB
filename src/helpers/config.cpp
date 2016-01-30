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
const std::string& Config::getValue(const std::string& param) const
{
	return this->_parameters.at(param);
}

bool Config::paramExists(std::string&& param) const
{
	std::map<std::string, std::string>::const_iterator it = this->_parameters.find(param);
	return it != this->_parameters.cend();
}

std::string Config::selfCheck() {
	std::string error(""); 	

	if(!this->paramExists("editor"))
		error += "'editor' variable not found.\n";		
	if(!this->paramExists("tmp_file_location"))
		error += "'tmp_file_location' variable not found.\n";		
	if(!this->paramExists("raw_data_location"))
		error += "'raw_data_location' variable not found.\n";		
	if(!this->paramExists("daemon_port"))
		error += "'daemon_port' variable not found.\n";		
	if(!this->paramExists("daemon_dir"))
		error += "'daemon_dir' variable not found.\n";		
	
	return error;
} 
