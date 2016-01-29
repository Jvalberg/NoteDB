#include "message.h"
#include <string.h>
#include <exception>

using namespace notedb::net;

const byte notedb::net::F_RESP_SUCCESS	= 0x01;
const byte notedb::net::F_RESP_FAILED	= 0x02;
const byte notedb::net::F_RESP_BADMESG	= 0x03;

Parameter::Parameter(const Parameter& p)
	: _flag(p._flag), _data(p._data)
{
}

Parameter::Parameter (const std::string& flag, const std::string& data) 
	: _flag(flag), _data(data)
{}


Parameter& Parameter::operator=(const Parameter& other){
	if(this != &other){
		this->_flag = other._flag;
		this->_data = other._data;
	}
	return *this;
}

const std::string& Parameter::getFlag() const {
	return this->_flag;
}

const std::string& Parameter::getData() const {
	return this->_data; 
}

void Parameter::print() const{ 
}

RequestMessage::RequestMessage (const std::vector<Parameter>& params)
	: _params(params) 
{} 

const std::vector<Parameter>& RequestMessage::getParams() const {
	return _params;
}

ResponseMessage::ResponseMessage(byte code, const std::string& data)
	: _data(data), _code(code) 
{}

byte ResponseMessage::getCode() const { 
	return _code;
}

const std::string& ResponseMessage::getData() const {
	return _data;
} 

bool notedb::net::send_request(const RequestMessage& message, Socket& socket){
	int paramCount = message.getParams().size(); 

	if(paramCount == 0)
	{
		return false;
	}

	int sent = socket.sendData(&paramCount, sizeof(int));
	for(int i = 0; i < paramCount; ++i)
	{
		const Parameter* it(&message.getParams().at(i));

		size_t fsize = it->getFlag().size() + 1;
		char *fbuff = new char[fsize]; 
		it->getFlag().copy(fbuff, fsize);
		fbuff[fsize-1] = '\0';

		size_t size = it->getData().size() + 1;
		char* buff = new char[size];
		it->getData().copy(buff, size);
		buff[size-1] = '\0';

		socket.sendData(&fsize, sizeof(size_t));
		socket.sendData(fbuff, fsize);
		socket.sendData(&size, sizeof(size_t));
		socket.sendData(buff, size);
		delete[] buff; 
		delete[] fbuff;
	}

	return true;
}


RequestMessage notedb::net::recv_request(Socket& socket){
	int count = 0;
	socket.recvData(&count, sizeof(int));

	std::vector<Parameter> params;
	for(long i = 0; i < count; ++i){
		size_t fsize;
		size_t size;
		std::string flag;
		std::string value;

		socket.recvData(&fsize, sizeof(size_t)); 
		char* fbuff = new char[fsize];
		socket.recvData(fbuff, fsize);
		fbuff[fsize-1] = '\0';
		flag = fbuff;
		delete[] fbuff;

		socket.recvData(&size, sizeof(size_t));
		if(size > 0){
			char* buff = new char[size]; 
			socket.recvData(buff, size);
			buff[size-1] = '\0';
			value = buff; 
			delete[] buff;
		}
		params.push_back(Parameter(flag, value));
	}

	return RequestMessage(params);
}


bool notedb::net::send_response(const ResponseMessage& message, Socket& socket){
	byte code = message.getCode();	
	size_t size = message.getData().size() + 1;
	char* buff = new char[size];
	std::copy(message.getData().begin(), message.getData().end(), buff);
	buff[size-1] = '\0';
	socket.sendData(&code, sizeof(byte));
	socket.sendData(&size, sizeof(size_t));
	socket.sendData(buff, size);

	delete[] buff;
	return true;
}

ResponseMessage notedb::net::recv_response(Socket& socket){
	byte code;
	size_t size;
	socket.recvData(&code, sizeof(byte));
	socket.recvData(&size, sizeof(size_t));
	char* buff = new char[size];
	socket.recvData(buff, size);
	buff[size-1] = '\0';
	std::string value(buff);
	delete[] buff;
	return ResponseMessage(code, value);
}
