#include <iostream>
#include <string.h>

#include "../net/socket.h"

#include "../net/message.h"

int main(){

	std::cout << "Running client!" << std::endl;
	using namespace notedb::net; 

	Socket socket;

	if(socket.connectTo("127.0.0.1", "6490")){
		std::cout << "Connected to host." << std::endl;

		Parameter param("jocke", "mitt value");
		std::vector<Parameter> parameters;
		parameters.push_back(param);
		RequestMessage message(parameters);
		message.getParams().at(0).print();

		send_request(message, socket);
		ResponseMessage response(recv_response(socket));

		if(response.getCode() == notedb::net::F_RESP_SUCCESS)
			std::cout << "SUCCESS: " << response.getData() << std::endl;

		socket.disconnect();
	} else {
		std::cout << "Failed to connect to server: " << socket.getError() << std::endl;
	}

	return 0;
}
