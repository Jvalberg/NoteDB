#include <iostream>
#include <errno.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <algorithm>

#include <sstream>
#include <ctime>
#include <sys/wait.h>

#include "../helpers/arguments.h" 
#include "../helpers/config.h"
#include "../net/socket.h"
#include "../net/message.h"
#include "editor.h"


int main(int argc, char *argv[]){
	Arguments args(argc, argv);
	if (!args.Parse()) 
		return -1;


	Config config;	
	// TODO: Allow relative paths.... Boost library 
	struct passwd *pwd = getpwuid(getuid());
	std::string homepath = pwd->pw_dir;
	if (!config.Read(homepath + "/.notedb/notedb.conf") )
	{
		std::cerr << "Could not find config at: ~/.notedb/scribbler/scribbler.conf" << std::endl;
		return -1;
	}

	if(!config.paramExists("daemon_port")){
		std::cerr << "Deaemon_port not specifeid in config." << std::endl;
		return -1;
	}
	if(!config.paramExists("editor") || !config.paramExists("tmp_file_location")){
		std::cerr << "Editor and tmp_file_location must be specified in conf." << std::endl;
		return -1;
	}
	
	// 0 args = opens external editor and get note.
	if(args.getArgs().size() == 0) {
		std::string note = getNote(config.getValue("editor"), config.getValue("tmp_file_location"));
		if(note == "")
			return 1;
		args.getArgs()["-a"] = note;
	}
	
	using namespace notedb::net;
	Socket socket;	
	if(socket.connectTo("127.0.0.1", config.getValue("daemon_port"))){
		std::vector<Parameter> params;		
		for(auto it = args.getArgs().begin(); it != args.getArgs().end(); ++it){
			params.push_back(Parameter(it->first, it->second));	
		}
		std::cout << "Sending message" << std::endl;
		RequestMessage message(params);
		send_request(message, socket);

		ResponseMessage response(recv_response(socket));
		if(response.getCode() == F_RESP_SUCCESS) {
			std::cout << response.getData() << std::endl;
		} 
		else if(response.getCode() == F_RESP_FAILED) {
			std::cerr << "Error: " << response.getData() << std::endl;
		}

		socket.disconnect();
	} else {
		if (socket.isFaulty())
			std::cerr << "Failed to connect to daemon. Start it." << std::endl;
		return -1;
	}

	return 1;
}
