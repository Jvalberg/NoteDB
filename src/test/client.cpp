#include <iostream>
#include <string.h>
#include <exception>

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

int main(){

	std::cout << "Running testclient." << std::endl;
	
	using namespace sql;
	Driver* driver;
	Connection* con;

	try {

		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306/notedb", "root", "cepett");
		Statement* stmt = con->createStatement();
		ResultSet* result;

		bool success = stmt->execute("SELECT * FROM notes");
		if(success) {
			result = stmt->getResultSet();
			std::cout << "Printing results. " << std::endl;
			while(result->next()) {
				std::cout << result->getString("content"); 
			}
		} else {
			std::cout << "Could not execute statement." << std::endl;
		}
		con->close();

	} catch(std::exception e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
