#include "search.h" 
#include <boost/filesystem.hpp>
#include <vector>
#include <sstream>

#include <memory>
#include "FileDAL.h"
#include "sqlDAL.h"
#include "../helpers/logger.h"

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

bool containsTags(const std::vector<std::string>& tags, const std::string& content){
	std::vector<std::string> contentTags = getTags(content);	
	for(auto it = tags.begin(); it != tags.end(); ++it){ 
		for(auto xt = contentTags.begin(); xt != contentTags.end(); ++xt){ 
			if(xt->compare(*it) == 0){
				return true;
			}
		}
	}
	return false;
}

std::string searchTags(const std::string& tagsStr, const std::string& blobLocation) {
	std::unique_ptr<DAL> dal( new SQLDAL() );
	dal->initialize("127.0.0.1/notedb|root|cepett");
	if(!dal->isInitialized()) {
		logger::LOG(logger::ERROR) << "SearchTags: Failed to initialize DAL." << std::endl;	
		return "";
	}

	std::stringstream out;
	std::vector<Note> notes = dal->getAllNotes();
	std::vector<std::string> tags = parseTags(tagsStr);
	logger::LOG(logger::TRACE) << "Search for tags '" << tagsStr << "' in " << notes.size() << " notes" << std::endl;
	for(std::vector<Note>::iterator it = notes.begin(); 
			it != notes.end(); ++it) {
		if(containsTags(tags, it->getContent())) {
			out << std::endl;
			out << it->getTimestamp() << std::endl;
			out << it->getContent() << std::endl;
			out << std::endl;
		}
	}

	return out.str();
} 
