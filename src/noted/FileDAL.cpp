#include "FileDAL.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include "../helpers/logger.h"

FileDAL::FileDAL() 
	: DAL(), _directory(), _initialized(false)
{}

bool FileDAL::initialize(const std::string& init_str) {
	_directory = init_str;
	// create the directory if it doesnt exist yet
	boost::filesystem::path blob_path(_directory);
	if (!boost::filesystem::exists(_directory))
		boost::filesystem::create_directories(_directory);
	_initialized = true;

	logger::LOG(logger::TRACE) << "FileDAL: Initialized using directory: " << _directory << std::endl;
	return true;
}

bool FileDAL::isInitialized() const {
	return _initialized;
}

bool FileDAL::persistNote(const Note& note) {
	if(!_initialized) 
		throw std::runtime_error("FileDAL not initialized.");	

	std::string blobfile = _directory + "/" + this->_getUniqueFilename();
	/* What are the odds this happens twice? Should fix in future */
	if(this->_file_exists(blobfile))
		blobfile = _directory + "/" + this->_getUniqueFilename();

	if(this->_file_exists(blobfile))
		return false; // I give up with trying to find that unique name, fuck everything, fuck loops
	std::ofstream storedBlob(blobfile);
	if(!storedBlob.is_open())
	{
		logger::LOG(logger::ERROR) << "FileDAL: Could not store note. Error: " << strerror(errno) << std::endl;
		return false;
	}

	storedBlob << note.getTimestamp() << std::endl;
	storedBlob << note.getContent();

	storedBlob.close();
	logger::LOG(logger::TRACE) << "FileDAL: Stored note at: " << blobfile << std::endl;
	return true;
}

std::vector<Note> FileDAL::getAllNotes() {
	if(!_initialized) 
		throw std::runtime_error("FileDAL not initialized.");	
	
	std::vector<Note> notes;

	namespace fs = boost::filesystem;
	fs::path blob_path { _directory };
	
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
					std::string timestamp;
					getline(blobfile, timestamp);

					std::string content;
					std::string line;
					while(getline(blobfile, line)) {
						content += line;
					}
					notes.push_back(Note(content, timestamp));
					blobfile.close();
				}
				else 
					logger::LOG(logger::ERROR) << "FileDAL: Could not open file: " << std::endl;
			}
		}
	}
	return notes;
}

std::string FileDAL::_getUniqueFilename() {
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

bool FileDAL::_file_exists(const std::string& filename)
{
	std::ifstream f(filename);
	return f.good();	
}
