#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>

namespace logger {
	enum LEVEL{ TRACE, DEBUG, INFO, FATAL, ERROR };

	std::ostream& LOG(LEVEL level);
	bool setFileOutput(const std::string& filepath);
	bool setConsoleOutput();
	bool clearLines(int numberLines);
}

#endif
