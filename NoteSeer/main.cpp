#include <iostream>
#include <errno.h>
#include <string.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <string>
#include "arguments.h" 

/*
 * USE NCURSES??? To create interactive GUI
 */
int main(int argc, char *argv[])
{
	Arguments args(argc, argv);
	if (!args.Parse()) 
	{
		args.PrintUsage();
		return -1;
	}
	std::cout << " ==================== NoteSeer =================== " << std::endl;
	std::string blobLocation("/home/jocke/.notedb/blobs");

	namespace fs = boost::filesystem;
	fs::path blob_path { blobLocation };

	if(fs::exists(blob_path))
	{
		fs::directory_iterator end_iter;
		for( fs::directory_iterator dir_iter(blob_path); dir_iter != end_iter; ++dir_iter)
		{
			if(fs::is_regular_file(dir_iter->status()))
			{
				std::string path = dir_iter->path().c_str();
				std::ifstream blobfile(path);
				if ( blobfile.is_open())
				{
					std::cout << std::endl;
					std::cout << dir_iter->path().filename() << std::endl;
					std::string line;
					while ( getline(blobfile, line))
					{
						std::cout << line << std::endl;
					}
					std::cout << std::endl;
				}
				else 
					std::cout << "Error: " << strerror(errno) << std::endl;
			}

		}
	}

	return 0;
}
