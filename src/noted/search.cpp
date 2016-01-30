#include "search.h" 
#include <boost/filesystem.hpp>
#include <vector>
#include <sstream>

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

std::string searchTags(const std::string& tagsStr, const std::string& blobLocation) {

	std::stringstream out;

	namespace fs = boost::filesystem;
	fs::path blob_path { blobLocation };
	std::vector<std::string> tags = parseTags(tagsStr);
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
					if (containsTags(tags, blobContent) || tagsStr == "*"){
						out << std::endl;
						out << dir_iter->path().filename() << std::endl;
					 	for(auto it = blobContent.begin(); it != blobContent.end(); ++it)
							out << *it << std::endl;
						out << std::endl;
					}
				}
				else 
					out << "Error: " << strerror(errno) << std::endl;
			}

		}
	}
	return out.str();
} 
