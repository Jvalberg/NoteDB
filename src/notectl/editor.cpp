#include "editor.h"
#include <boost/filesystem.hpp>
#include <sstream>
#include <sys/wait.h>

std::string getNote(const std::string& editor, const std::string& file_location){
		std::string programPath = "/bin/" + editor;

		/* RUN THE TEXT EDITOR AND WAIT FOR USER TO FINISH */
		pid_t pid = fork();
		if (pid < 0)
		{
			return "";
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
			execl(programPath.c_str(), editor.c_str(), file_location.c_str(), (char)0x0);
			return "";
		}
		else 
		{
			/* PARENT PROCESS - THE HANDLER OF THE RESULTING NOTE */
			int status = 20;
			while (!WIFEXITED(status)) 
			{
				waitpid(pid, &status, 0);
			}

			std::stringstream note_stream;
			std::ifstream note_file(file_location); 
			if(note_file.is_open()){

				std::string line;
				while( getline(note_file, line))
					note_stream << line;
			}
			 
			return note_stream.str();
		}
	return "";
}
