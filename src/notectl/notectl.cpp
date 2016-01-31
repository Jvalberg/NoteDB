#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <algorithm>

#include "../helpers/arguments.h" 
#include "../helpers/config.h"
#include "../net/socket.h"
#include "../net/message.h"
#include "editor.h"

#include "../helpers/logger.h"

int main(int argc, char *argv[]){

	logger::setConsoleOutput();

	Arguments args(argc, argv);
	if (!args.Parse()) 
		return -1;

	Config config;	
	struct passwd *pwd = getpwuid(getuid());
	std::string homepath = pwd->pw_dir;
	std::string path = homepath + "/.notedb/notedb.conf";
	if (!config.Read(path) )
	{
		logger::LOG(logger::FATAL) << "Could not locate notedb config at path: " << path << std::endl;
		return -1;
	}
	std::string error = config.selfCheck();
	if(error != "") {
		logger::LOG(logger::FATAL) << error << std::endl;
		return -1;
	}

	std::string logfile = config.getValue("log") + "/notectl.log";
	if(!logger::setFileOutput(logfile))
		logger::LOG(logger::ERROR) << "Could not use log file at path: " << logfile << std::endl;

	logger::LOG(logger::INFO) << "Starting notectl." << std::endl;
	
	using namespace notedb::net;
	Socket socket;	
	if(socket.connectTo("127.0.0.1", config.getValue("daemon_port"))){
		
		// 0 args = opens external editor and get note.
		if(args.getArgs().size() == 0) {
			std::string note = getNote(config.getValue("editor"), config.getValue("tmp_file_location"));
			if(note == "")
			{
				std::cout << "No note detected. Aborting." << std::endl;
				logger::LOG(logger::INFO) << "No note detected. Aborting" << std::endl;
				socket.disconnect();
				return 1;
			}
			args.getArgs()["-a"] = note;
		}

		
		std::vector<Parameter> params;		
		for(auto it = args.getArgs().begin(); it != args.getArgs().end(); ++it){
			params.push_back(Parameter(it->first, it->second));	
		}
		RequestMessage message(params);
		send_request(message, socket);

		std::unique_ptr<ResponseMessage> response(recv_response(socket));
		if(response == nullptr) {
			std::cerr << "Error: Lost socket connection to other end." << std::endl;
			logger::LOG(logger::ERROR) << "Socket closed on the other end. Aborting." << std::endl;
			return -1;
		}
		if(response->getCode() == F_RESP_SUCCESS) {
			std::cout << response->getData() << std::endl;
		} 
		else if(response->getCode() == F_RESP_FAILED) {
			std::cerr << "Error: " << response->getData() << std::endl;
			logger::LOG(logger::ERROR) << "Error response: " << response->getData() << std::endl;
		}

		socket.disconnect();
	} else {
		std::cout << "Error connecting to daemon: " << socket.getError() << std::endl;
		logger::LOG(logger::ERROR) << "Error connecting to daemon: " << socket.getError() << std::endl;
		return -1;
	}

	logger::LOG(logger::INFO) << "Closing notectl." << std::endl;

	return 1;
}
