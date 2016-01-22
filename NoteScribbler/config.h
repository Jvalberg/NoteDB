#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

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
