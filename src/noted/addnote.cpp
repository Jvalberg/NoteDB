#include "addnote.h"

#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

std::string getUniqueFilename()
{
	std::string ret;

	std::ifstream randomUUID("/proc/sys/kernel/random/uuid", std::ios::in);
	if (!randomUUID.is_open()) 
	{
		return "-1";
	}

	getline(randomUUID, ret);
	randomUUID.close();

	return ret;
}

std::string getCurrentDateTime()
{
	std::time_t curr= std::time(0);
	struct tm* now = std::localtime( &curr );
	std::stringstream s;
	s << now->tm_mday << "/" << 
		( now->tm_mon + 1) << "/" << 
		( now->tm_year - 100 ) << "-" <<
		now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
	return s.str();
}

bool file_exists(const std::string& filename)
{
	std::ifstream f(filename);
	return f.good();	
}

bool addNote(const std::string& note, const std::string& blobStorage){
	std::cout << "Storing note." << std::endl;
	/* User has finished editing, check if note should be saved. */

	// create the directory if it doesnt exist yet
	boost::filesystem::path blob_path(blobStorage);
	if (!boost::filesystem::exists(blob_path))
		boost::filesystem::create_directories(blob_path);

	std::string blobfile = blobStorage + "/" + getUniqueFilename();
	/* What are the odds this happens twice? Should fix in future */
	if(file_exists(blobfile))
		blobfile = blobStorage + "/" + getUniqueFilename();

	std::ofstream storedBlob(blobfile);
	if(!storedBlob.is_open())
	{
		std::cerr << "Error: " << strerror(errno);
		std::cerr << "Could not store the note. EVERYHING IS LOST." << std::endl;
		return false;
	}

	storedBlob << getCurrentDateTime() << std::endl;
	storedBlob << note;

	storedBlob.close();
	return true;
}
