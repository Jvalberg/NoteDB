#include <iostream>
#include <sstream>
#include <ctime>
#include <sys/wait.h>
#include <fstream>

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

// BOOST - required for file system handling
#include <boost/filesystem.hpp>

#include "../config.h"
std::string getUniqueFilename()
{
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

bool file_exists(const std::string& filename)
{
	std::ifstream f(filename);
	return f.good();	
}

int main()
{
	Config config;	
	// TODO: Allow relative paths.... Boost library 
	struct passwd *pwd = getpwuid(getuid());
	std::string homepath = pwd->pw_dir;
	if (!config.Read(homepath + "/.notedb/notedb.conf") )
	{
		std::cerr << "Could not find config at: ~/.notedb/scribbler/scribbler.conf" << std::endl;
		return -1;
	}

	std::string program("vim");
	if (config.paramExists("editor"))
		program = config.getValue("editor");

	std::string programPath = "/bin/" + program;

	std::string file_location("/tmp/NoteDB/note-blob.dat");
	if(config.paramExists("tmp_file_location"))
		file_location = config.getValue("tmp_file_location");

	std::string blobStorage("/home/jocke/.notedb/blobs");
	if(config.paramExists("raw_data_location"))
		blobStorage = config.getValue("raw_data_location");

	/* RUN THE TEXT EDITOR AND WAIT FOR USER TO FINISH */
	pid_t pid = fork();
	if (pid < 0)
	{
		std::cerr << "Fork() failed/n";
		exit(1);
	}
	else if(pid == 0) 
	{
		/* CHILD PROCESS - THE TEXT EDITOR */
		/* Clear contents of the note blob */
		boost::filesystem::path dir(file_location);
		if(!boost::filesystem::exists(dir.remove_filename()))
			boost::filesystem::create_directories(dir);

		std::fstream f(file_location, std::fstream::in | std::fstream::out | std::fstream::trunc);
		f.close();
		execl(programPath.c_str(), program.c_str(), file_location.c_str(), (char)0x0);
		std::cerr << "execl() failed!";
		std::cerr << strerror(errno) << std::endl;
		exit(1);
	}
	else 
	{
		/* PARENT PROCESS - THE HANDLER OF THE RESULTING NOTE */
		int status = 20;
		while (!WIFEXITED(status)) 
		{
			waitpid(pid, &status, 0);
		}

		std::cout << "Storing note." << std::endl;
		/* User has finished editing, check if note should be saved. */

		// create the directory if it doesnt exist yet
		boost::filesystem::path blob_path(blobStorage);
		if (!boost::filesystem::exists(blob_path))
			boost::filesystem::create_directories(blob_path);

		std::ifstream note_blob;
		note_blob.open(file_location);
		if(!note_blob.is_open())
		{
			/* Error, recoverable, lost note... */
			std::cerr << "Could not locate the note. Sorry, everything is lost." << std::endl;
			return -1;
		}
		// Only store non-empty files
		if(note_blob.peek() != std::ifstream::traits_type::eof())
		{
			std::string blobfile = blobStorage + "/" + getUniqueFilename();
			/* What are the odds this happens twice? Should fix in future */
			if(file_exists(blobfile))
				blobfile = blobStorage + "/" + getUniqueFilename();

			std::ofstream storedBlob(blobfile);
			if(!storedBlob.is_open())
			{
				std::cerr << "Error: " << strerror(errno);
				std::cerr << "Could not store the note. EVERYHING IS LOST." << std::endl;
				return -1;
			}

			storedBlob << getCurrentDateTime() << std::endl;

			std::string line;
			while (getline(note_blob, line)) 
			{
				storedBlob << line << std::endl;
			}
		}
	}
}
