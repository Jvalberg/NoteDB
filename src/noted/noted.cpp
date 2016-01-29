#include <iostream>
#include "../helpers/config.h" 

// Socket libraries
#include "../net/listener.h"
#include "../net/socket.h"
#include "../net/message.h"
#include "addnote.h"
#include "search.h"

int main()
{
	std::cout << "Note Daemon starting..." << std::endl;

	Config config;
	if (!config.Read(config::getDefaultPath())) 
	{
		std::cerr << "Could not locate config file at: " << config::getDefaultPath() << std::endl;
		return -1;
	}
	if(!config.paramExists("daemon_dir")) 
	{
		std::cerr << "No daemon_dir variable found in config.\nAborting..." << std::endl;
		return -1;
	}
	if(!config.paramExists("daemon_port"))
	{
		std::cerr << "No daemon_port variable found." << std::endl;
		return -1;
	}
	std::string blobStorage(config.getValue("raw_data_location"));	 
	std::string workingDirectory(config.getValue("daemon_dir"));
	std::string port(config.getValue("daemon_port"));
	
	Listener listener(port);
	std::cout << "Starting listener..." << std::endl;

	if(listener.start()){
		std::cout << "Listener started. Listening on port: " << port << std::endl;
		while(listener.isRunning()) {
			Socket* client = listener.acceptClient();
			std::cout << "Accepted client" << std::endl;

			if(client == nullptr) {
				if(listener.isFaulty()){
					std::cerr << listener.getFault() << std::endl;
					listener.reset(); // removes error status, retries.
				}
			} else {
				using namespace notedb::net;
				RequestMessage message(recv_request(*client));
				if(message.getParams().size() != 1){ // Only one command at a time atm.
					ResponseMessage response(F_RESP_FAILED, "Can only perform one command (a/t).");
					send_response(response, *client);
				}
				else if(message.getParams().front().getFlag() == "-a"){
					std::string result;
					if(addNote(message.getParams().front().getData(), blobStorage))
						result = "Successfully stored note.";
					else
						result = "Failed to store note.";

					ResponseMessage response(F_RESP_SUCCESS, result);
					send_response(response, *client);
				}
				else if(message.getParams().front().getFlag() == "-t"){
					std::string result = searchTags(message.getParams().front().getData(), blobStorage);
					ResponseMessage response(F_RESP_SUCCESS, result);
					send_response(response, *client);
				}
				else {
					std::cout << "Flag: '" << message.getParams().front().getFlag() << "'" << std::endl;
					ResponseMessage response(F_RESP_FAILED, "Command not recognized. use -a or -t.");
					send_response(response, *client);
				}

				client->disconnect();
				std::cout << "Disconnected client, and removing." << std::endl;
				delete client;
			}
		}
	} else {
		std::cerr << "Failed to start listener." << std::endl;
		if(listener.isFaulty())
			std::cerr << "Fault: " << listener.getFault() << std::endl;
	}

	std::cout << "NoteDaemon stopping..." << std::endl;
	return 0;
}
