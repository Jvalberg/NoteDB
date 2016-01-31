#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include "socket.h"
#include <memory>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

namespace notedb{
	namespace net{
		typedef char byte;
		extern const byte F_RESP_SUCCESS;
		extern const byte F_RESP_FAILED;
		extern const byte F_RESP_BADMESG;
		
		// Might not be long enough.
		typedef unsigned long long mlen_t;

		class Parameter
		{
			public:
				Parameter(const Parameter& p);
				Parameter (const std::string& flag, const std::string& data);

				Parameter& operator=(const Parameter& other);

				const std::string& getData() const;
				const std::string& getFlag() const;

				void print() const;

			private:
				std::string _flag;
				std::string _data;	
		};

		class RequestMessage
		{
			public:
				RequestMessage (const std::vector<Parameter>& params);
				const std::vector<Parameter>& getParams() const;

			private:
				std::vector<Parameter> _params;
		};

		class ResponseMessage
		{
			public:
				ResponseMessage(byte code, const std::string& data);

				byte getCode() const;
				const std::string& getData() const;

			private:
				/* data */
				std::string _data;
				byte _code;
		};

		bool send_request(const RequestMessage& message, Socket& socket);
		RequestMessage* recv_request(Socket& socket);

		bool send_response(const ResponseMessage& message, Socket& socket);
		ResponseMessage* recv_response(Socket& socket);
	}
}

#endif
