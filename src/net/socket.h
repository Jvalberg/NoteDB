#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>

class Socket
{
public:
	/*
	 * Creates an empty socket, not already connected.
	 */
	Socket ();

	/*
	 * Creates a socket based on an already open socket.
	 */
	Socket(int socket_fd);
	~Socket();

	bool disconnect();
	bool connectTo(const std::string& host, const std::string& port);

	int sendData(const void* buffer, int len);
	int recvData(void* buffer, int len);

	bool isFaulty();
	bool isConnected();
	
	std::string getError();

private:
	void setError(std::string error);

	struct addrinfo* _addressInfo;
	int _socket_fd;

	std::string _ip;
	std::string _port;
	std::string _errorStr;
	bool		_connected;
	bool		_error;
};

#endif
