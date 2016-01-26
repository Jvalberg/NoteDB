#include <iostream>
#include "../helpers/config.h" 

int main()
{
	std::cout << "NoteMastermind starting..." << std::endl;
	// TODO:
	// Use socket and network later, there is a lot to learn about it.
	// Only use files now instead!
	// boost::asio::io_service io_service;	
	// boost::asio::ip::tcp::socket socket(io_service);
	
	Config config;
	if (!config.Read(config::getDefaultPath())) 
	{
		std::cerr << "Could not locate config file at: " << config::getDefaultPath() << std::endl;
		return -1;
	}

	if(!config.paramExists("mastermind_dir")) 
	{
		std::cerr << "No mastermind_dir variable found in config.\nAborting..." << std::endl;
		return -1;
	}
	std::string workingDirectory(config.getValue("mastermind_dir"));
	
	

	
	std::cout << "NoteMastermind stopping..." << std::endl;
	return 0;
}
