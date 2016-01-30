#include <iostream>
#include "../helpers/config.h" 

// Socket libraries
#include "../net/listener.h"
#include "../net/socket.h"
#include "clientmanager.h"

#include "../helpers/logger.h"

int main()
{
	logger::setConsoleOutput();
	logger::LOG(logger::INFO) << "Starting daemon." << std::endl;

	Config config;
	if (!config.Read(config::getDefaultPath())) 
	{
		logger::LOG(logger::FATAL) << "Could not locate config file at: " << config::getDefaultPath() << std::endl;
		return -1;
	}
	std::string error = config.selfCheck();
	if(error != "")
	{
		logger::LOG(logger::FATAL) <<  error << std::endl;
		return -1;
	} 

	std::string logpath = config.getValue("log") + "/noted.log";
	if(!logger::setFileOutput(logpath))
		logger::LOG(logger::ERROR) << "Failed to use logfile: " << logpath << std::endl;

	logger::clearLines(2);

	std::string blobStorage(config.getValue("raw_data_location"));	 
	std::string workingDirectory(config.getValue("daemon_dir"));
	std::string port(config.getValue("daemon_port"));
	
	Listener listener(port);
	
	logger::LOG(logger::TRACE) << "Starting listener." << std::endl;
	if(listener.start()){
		 
		logger::LOG(logger::TRACE) << "Listener started." << std::endl;
		 
		while(listener.isRunning()) {
			logger::LOG(logger::TRACE) << "Waiting for client connection..." << std::endl;
			Socket* client = listener.acceptClient();
			logger::LOG(logger::TRACE) << "Accepted client." << std::endl;
			if(client != nullptr){
				logger::LOG(logger::TRACE) << "Handling client..." << std::endl;
				handleClient(config, client);
				delete client;
			}
		}
	} else {
		logger::LOG(logger::FATAL) << "Failed to start listener." << listener.getFault() << std::endl;
	}

	logger::LOG(logger::TRACE) << "Stopping daemon." << std::endl;
	return 0;
}
