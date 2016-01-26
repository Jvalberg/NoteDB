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
#include "arguments.h" 
#include "../config.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <algorithm>

void readContent(std::ifstream& file, std::vector<std::string>& content){
	content.clear();
	std::string line;
	while(getline(file, line)){
		content.push_back(line);
	}
}

std::vector<std::string> parseTags(const std::string& tagStr){
	std::vector<std::string> ret;

	typedef std::string::const_iterator str_it;
	str_it current = tagStr.begin();
	while(current != tagStr.end()){
		str_it next_end = std::find(current, tagStr.end(), ',');
		ret.push_back(std::string(current, next_end));

		if(next_end != tagStr.end())	
			current = next_end + 1; // skip the ,
		else
			current = next_end;
	}
	return ret;
}

std::vector<std::string> getTags(const std::string& line){
	std::vector<std::string> ret;

	typedef std::string::const_iterator str_it;
	str_it current = line.begin();
	while(current != line.end()){
		current = std::find(current, line.end(), '#');
		str_it next_end = std::find(current, line.end(), ' ');
		if(current != line.end())	{
			std::string tag(current + 1, next_end);
			ret.push_back(tag);
		}
		if(next_end != line.end())	
			current = next_end + 1; // skip the ,
		else
			current = next_end;
	}

	return ret;
}

bool containsTags(const std::vector<std::string>& tags, const std::vector<std::string> content){
	for (std::vector<std::string>::const_iterator it = content.begin();  
			it < content.end(); ++it) {
		std::vector<std::string> contentTags = getTags(*it);	
		for(auto it = tags.begin(); it != tags.end(); ++it){ 
			for(auto xt = contentTags.begin(); xt != contentTags.end(); ++xt){ 
				if(xt->compare(*it) == 0){
					return true;
				}
			}
		}
	}
	return false;
}
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

	Config config;	
	struct passwd *pwd = getpwuid(getuid());
	std::string homepath = pwd->pw_dir;
	if (!config.Read(homepath + "/.notedb/notedb.conf"))
	{
		std::cerr << "Could not find config." << std::endl;
		return -1;
	}

	std::cout << " ==================== NoteSeer =================== " << std::endl;
	std::string blobLocation(homepath + "/.notedb/blobs");
	if (config.paramExists("raw_data_location"))
		blobLocation = config.getValue("raw_data_location");

	namespace fs = boost::filesystem;
	fs::path blob_path { blobLocation };
	std::vector<std::string> tags = parseTags(args.getValue("t"));
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
					std::vector<std::string> blobContent;
					readContent(blobfile, blobContent);
					if (containsTags(tags, blobContent) || args.getValue("t") == "*"){
						std::cout << std::endl;
						std::cout << dir_iter->path().filename() << std::endl;
						for(auto it = blobContent.begin(); it != blobContent.end(); ++it)
							std::cout << *it << std::endl;
						std::cout << std::endl;
					}
				}
				else 
					std::cout << "Error: " << strerror(errno) << std::endl;
			}

		}
	}

	return 0;
}
