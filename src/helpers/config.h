#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
namespace config 
{
	std::string getDefaultPath();
}

class Config {
	public:
		Config() = default;
		bool Read(const std::string&);
		bool Read(std::string&&);

		std::string getValue(std::string&&);
		bool paramExists(std::string&&);
	private:
		bool read();
		std::map<std::string, std::string> _parameters;
		std::string _path;
};

#endif
