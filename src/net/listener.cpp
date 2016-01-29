#include "listener.h"

#include <memory>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>


Listener::Listener(const std::string& port)
	 : _maxConnectionQueue(5), _addressInfo(nullptr), _port(port), _errorStr(""), _running(false),  _error(false)
{}

Listener::~Listener() {
	this->stop();
}

bool Listener::start() {
	int status;
	struct addrinfo hints;
	_error = false;
	_errorStr = "";
	
	memset(&hints, 0, sizeof hints); // Make sure hints is empty.
	hints.ai_socktype = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if( (status = getaddrinfo(NULL, _port.c_str(), &hints, &_addressInfo)) != 0){
		this->setError(gai_strerror(status));
		return false;
	}

	_socket_fd = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
	if(_socket_fd == -1){
		this->setError(strerror(errno));
		freeaddrinfo(_addressInfo);
		return false;
	}

	if(bind(_socket_fd, _addressInfo->ai_addr, _addressInfo->ai_addrlen) == -1){
		this->setError(strerror(errno));
		freeaddrinfo(_addressInfo);
		return false;
	}

	if(listen(_socket_fd, _maxConnectionQueue) == -1){ 
		this->setError(strerror(errno));
		freeaddrinfo(_addressInfo);
		return false;
	}

	_running = true;

	return true;
}

void Listener::setError(std::string error) {
	_error = true;
	_errorStr = error;
}

bool Listener::isRunning() {
	return _running;
}

bool Listener::stop() {
	if(this->isRunning())
	{
		close(_socket_fd);
		_socket_fd = -1;
		freeaddrinfo(_addressInfo);

		reset();

		_running = false;
	}
	return true;
}

Socket* Listener::acceptClient(){
	if(!this->isRunning())
		return nullptr;

	struct sockaddr their_addr;

	socklen_t addr_size = sizeof(struct sockaddr_storage);
	int fd = accept(_socket_fd, &their_addr, &addr_size);
	if(fd == -1) {
		setError(strerror(errno));
		return nullptr;
	}

	return new Socket(fd);
}

bool Listener::isFaulty() {
	return _error;
}

void Listener::reset() {
	_error = false;
	_errorStr = "";
}

std::string Listener::getFault(){
	return _errorStr;
}
