#include "socket.h"
#include <sys/types.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

Socket::Socket() 
	: _addressInfo(nullptr),  _socket_fd(-1), _ip(""), _port(""), _errorStr(""), 
	_connected(false), _error(false)
{
}

Socket::Socket(int socket_fd)
	: _addressInfo(nullptr),  _socket_fd(socket_fd), _ip(""), _port(""), _errorStr(""), 
	_connected(true), _error(false)
{
	//TODO: Extract IP and addr from their addr 
}

Socket::~Socket() {
	disconnect();
}

bool Socket::disconnect(){
	if(this->isConnected())
	{
		close(_socket_fd);
		if(_addressInfo != nullptr)
		{
			freeaddrinfo(_addressInfo);
		}
		_error = false;
		_errorStr = "";
		_connected = false;
	}
	return true;
}

bool Socket::connectTo(const std::string& host, const std::string& port){
	if(this->isConnected()){
		setError("Already existing connection up.");
		return false;
	}

	this->disconnect();	// Contains the cleanup code i want to run.....

	int status;
	struct addrinfo hints;

	memset(&hints, 0, sizeof hints);	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if( (status = getaddrinfo(host.c_str(), port.c_str(), &hints, &_addressInfo)) != 0){
		const std::string sender("getaddrinfo: ");
		this->setError(sender + gai_strerror(status));
		return false;
	}

	if( (_socket_fd = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol)) == -1){
		const std::string sender("socket: ");
		this->setError(sender + strerror(errno));
		return false;
	}

	if(connect(_socket_fd, _addressInfo->ai_addr, _addressInfo->ai_addrlen) != 0){
		const std::string sender("connect: ");
		this->setError(sender + strerror(errno));
		return false;
	}

	this->_connected = true;

	return true;
}

void Socket::setError(std::string error) {
	_error = true;
	_errorStr = error;
}

int Socket::sendData(const void* buffer, int len){
	if(!this->isConnected()){
		this->setError("Cannot send buffer. Not connected.");
		return -1;
	}
	int sent = send(_socket_fd, buffer, len, 0);
	if(sent == -1)
		this->setError(strerror(errno)); 
	return sent;
}

int Socket::recvData(void* buffer, int len){
	if(!this->isConnected()){
		this->setError("Cannot recieve data. Not connected.");
		return -1;
	}
	int recieved = recv(_socket_fd, buffer, len, 0);
	if(recieved == -1)
		this->setError(strerror(errno)); 
	return recieved;
}

bool Socket::isFaulty(){
	return _error;
}

bool Socket::isConnected(){
	return _connected;
}

std::string Socket::getError(){
	return _errorStr;
}

