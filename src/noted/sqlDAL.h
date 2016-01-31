#ifndef SQLDAL_H
#define SQLDAL_H

#include "DAL.h"
#include <string>

class SQLDAL : public DAL
{
public:
	SQLDAL();
	virtual ~SQLDAL () {}
	
	virtual bool initialize(const std::string& init_str);
	virtual bool isInitialized() const;

	virtual bool persistNote(const Note& note);
	virtual std::vector<Note> getAllNotes();

private:
	std::string _host;
	std::string _username;
	std::string _pass;
	bool _initialized;
};

#endif 
