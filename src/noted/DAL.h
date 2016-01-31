#ifndef DAL_H
#define DAL_H

/*
 * Data Access Layer
 */
#include <string>
#include <vector>

#include "note.h"

class DAL
{
public:
	virtual ~DAL() {}
	virtual bool initialize(const std::string& init_str) = 0;
	virtual bool isInitialized() const = 0;

	virtual bool persistNote(const Note& note) = 0;
	virtual std::vector<Note> getAllNotes() = 0;

private:
	/* data */
};

#endif
