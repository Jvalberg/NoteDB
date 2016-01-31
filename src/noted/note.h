#ifndef NOTE_H
#define NOTE_H

#include <string> 

class Note
{
public:
	Note (const std::string& content, const std::string& timestamp);
	virtual ~Note ();

	const std::string& getContent() const;
	const std::string& getTimestamp() const;

private: 
	std::string _content;
	std::string _timestamp;
};

#endif
