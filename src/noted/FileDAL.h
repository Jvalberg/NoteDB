#ifndef FILEDAL_H
#define FILEDAL_H

#include "DAL.h"
#include "note.h"

class FileDAL : public DAL
{
public:

	FileDAL();
	virtual ~FileDAL() {}

	bool initialize(const std::string& init_str);
	bool isInitialized() const;

	bool persistNote(const Note& note);
	std::vector<Note> getAllNotes();

private:
	std::string _directory;
	bool _initialized;

	std::string _getUniqueFilename();
	bool _file_exists(const std::string& filename);

};

#endif
