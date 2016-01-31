#include "sqlDAL.h"
#include "../helpers/logger.h"
#include <algorithm>
#include <exception>

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

SQLDAL::SQLDAL() 
	: DAL(), _host(), _username(), _pass()
{}

bool SQLDAL::initialize(const std::string& init_str) { 
	auto current = init_str.begin();
	auto end = std::find(current, init_str.end(), '|');
	if(end == init_str.end()) {
		logger::LOG(logger::ERROR) << "SQLDAL: Wrong format on init string." << std::endl;
		return false;
	}
	_host = std::string(current, end);
	current = end + 1;

	end = std::find(current, init_str.end(), '|');
	if(end == init_str.end())
	{
		logger::LOG(logger::ERROR) << "SQLDAL: Wrong format on init string." << std::endl;
		return false;
	}
	_username = std::string(current, end);
	current = end + 1;

	_pass = std::string(current, init_str.end());

	_initialized = true;
	return true;
}

bool SQLDAL::isInitialized() const { 
	return _initialized;
}

bool SQLDAL::persistNote(const Note& note) { 
	if (!_initialized) 
		throw std::runtime_error("SQLDAL: Not initilized.");

	using namespace sql;
	Driver* driver;
	Connection* connection;
	Statement* stmt;
	try {
		driver = get_driver_instance();
		connection = driver->connect(_host, _username, _pass);
	} catch(std::exception e) {
		logger::LOG(logger::ERROR) << "SQLDAL: Could not connect to database: " << e.what() << std::endl;
		if(connection)
			delete connection;

		return false;
	}

		std::string sql_query = "INSERT INTO notes (Content, Timestamp) VALUES ('" + note.getContent() + "', timestamp'" + note.getTimestamp() + "')";
	try {
		stmt = connection->createStatement();
		stmt->execute(sql_query);
	} catch(std::exception e) {
		logger::LOG(logger::ERROR) << "SQLDAL: " << sql_query << std::endl;
	}

	if(connection)
		delete connection;
	if(stmt)
		delete stmt;


	return true;
}

std::vector<Note> SQLDAL::getAllNotes() { 
	if (!_initialized) 
		throw std::runtime_error("SQLDAL: Not initilized.");

	using namespace sql;
	Driver* driver;
	Connection* connection;
	Statement* stmt;
	ResultSet* result;
	std::vector<Note> ret;

	try {
		driver = get_driver_instance();
		connection = driver->connect(_host, _username, _pass);
	} catch(std::exception e) {
		logger::LOG(logger::ERROR) << "SQLDAL: Could not connect to database: " << e.what() << std::endl;
		if(connection)
			delete connection;
		return ret;
	}

	try {
		stmt = connection->createStatement();
		bool success = stmt->execute("SELECT * FROM notes");
		if(!success) {
			logger::LOG(logger::ERROR) << "Failed to insert into database." << std::endl;
		} else {
			result = stmt->getResultSet();
			while(result->next()) {
				std::string content = result->getString("Content");
				std::string timestamp = result->getString("Timestamp");
				ret.push_back(Note(content, timestamp));
			}
		}

	} catch(std::exception e) {
		logger::LOG(logger::ERROR) << "SQLDAL: " << e.what() << std::endl;
	}

	if(connection)
		delete connection;
	if(stmt)
		delete stmt;

	return ret;
}
