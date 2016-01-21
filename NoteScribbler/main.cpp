#include <iostream>
#include <sstream>
#include <ctime>
#include <sys/wait.h>
#include <fstream>

#include <unistd.h>

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
	std::string program("vim");
	std::string programPath = "/bin/" + program;
	std::string file_location("/tmp/NoteDB/note-blob.dat");
	std::string blobStorage("/home/jocke/.notedb/blobs");

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
		std::fstream f(file_location, std::ios::in);
		if(f)
		{
			f.close();
			f.open(file_location, std::ios::out | std::ios::trunc);
		}

		execl(programPath.c_str(), program.c_str(), file_location.c_str(), (char)0x0);
		std::cerr << "execl() failed!";
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

		/* User has finished editing, check if note should be saved. */
		
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
