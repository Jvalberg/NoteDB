#include "addnote.h"
#include "note.h"
#include "FileDAL.h"
#include "sqlDAL.h"

#include "../helpers/logger.h"

#include <ctime>
#include <memory>
#include <sstream>

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
 
bool addNote(const std::string& note, const std::string& blobStorage){
	std::unique_ptr<DAL> dal( new SQLDAL() );

	dal->initialize("127.0.0.1/notedb|root|cepett");
	if(!dal->isInitialized()) {
		logger::LOG(logger::ERROR) << "AddNote: Failed initializing DAL." << std::endl;	
		return false;
	}

	Note n(note, getCurrentDateTime());
	if(!dal->persistNote(n)) 
	{
		logger::LOG(logger::ERROR) << "AddNote: Failed storing note." << std::endl;
		return false;
	}

	return true;
}
