#include "note.h"


Note::Note (const std::string& content, const std::string& timestamp) 
	: _content(content), _timestamp(timestamp) 
{}

Note::~Note () 
{}

const std::string& Note::getContent() const {
	return _content;
}

const std::string& Note::getTimestamp() const {
	return _timestamp;
}
