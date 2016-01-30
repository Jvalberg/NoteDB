#ifndef LISTENER_H
#define LISTENER_H

#include <string>
#include "socket.h"

class Listener
{
public:
	Listener (const std::string& port);
	~Listener ();

	bool start();
	bool isRunning();
	bool stop();

	Socket* acceptClient();

	bool isFaulty();
	void reset();
	std::string getFault();

private:
	void setError(std::string error);

	const int _maxConnectionQueue;
	struct addrinfo* _addressInfo;
	int _socket_fd;

	std::string _port;
	std::string _errorStr;
	bool		_running;
	bool		_error;
};

#endif
