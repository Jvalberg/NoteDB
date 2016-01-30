#include "clientmanager.h"
#include <iostream>
#include "../net/message.h"
#include "addnote.h"
#include "search.h"

#include "../helpers/logger.h"


void handleClient(const Config& config, Socket* client){
	std::string blobStorage(config.getValue("raw_data_location"));
	using namespace notedb::net;
	RequestMessage message(recv_request(*client));
	if(message.getParams().size() != 1){ // Only one command at a time atm.
		logger::LOG(logger::ERROR) << "Received to many/few commands. Command count: " << message.getParams().size() << std::endl;
		ResponseMessage response(F_RESP_FAILED, "Can only perform one command (a/t).");
		logger::LOG(logger::TRACE) << "Sending back failed response." << std::endl;
		send_response(response, *client);
	}
	else if(message.getParams().front().getFlag() == "-a"){
		std::string result;
		logger::LOG(logger::TRACE) << "Add new note command." << std::endl;
		if(addNote(message.getParams().front().getData(), blobStorage))
		{
			result = "Successfully stored note.";
			ResponseMessage response(F_RESP_SUCCESS, result);
			logger::LOG(logger::TRACE) << "Succesfully stored note. Responding with success." << std::endl;
			send_response(response, *client);
		}
		else
		{
			result = "Failed to store note.";
			logger::LOG(logger::ERROR) << "Failed to store note. Responding with failure" << std::endl;
			ResponseMessage response(F_RESP_FAILED, result);
			send_response(response, *client);
		}

	}
	else if(message.getParams().front().getFlag() == "-t"){
		logger::LOG(logger::TRACE) << "Search for tags command. tags: '" << message.getParams().front().getData() << "'." << std::endl;
		std::string result = searchTags(message.getParams().front().getData(), blobStorage);
		ResponseMessage response(F_RESP_SUCCESS, result);
		send_response(response, *client);
	}
	else {
		logger::LOG(logger::ERROR) << "Command not recognized. Command: " << message.getParams().front().getFlag() << "Responding with failure." << std::endl;
		ResponseMessage response(F_RESP_FAILED, "Command not recognized. use -a or -t.");
		send_response(response, *client);
	}
}
