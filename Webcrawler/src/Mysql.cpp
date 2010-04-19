#include "Mysql.h"
#include "ssql_structs.h"
using namespace RudyTheCrawler;

mysqlpp::Connection Mysql::_connection = mysqlpp::Connection(false);

void Mysql::connect(char* db, char* server, char* user, char* pass)
{
	if (!Mysql::_connection.connect(db, server, user, pass)) {
		std::cout << Mysql::_connection.error();
		throw "Connecting to DB failed!";
	}

}

int Mysql::insert_link(std::string link, std::string parent, bool broken)
{
	std::cout << "INSERT: " << link <<":" << parent << ":" << broken << std::endl;
	try {
		mylink row(link.c_str(), parent.c_str(), broken);
		mysqlpp::Query query = Mysql::_connection.query();
		query.insert(row);
		query.execute();

		//std::cout << query << std::endl;
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		std::cerr << "Query error: " << er.what() << std::endl;
		return -1;
	}
	catch (const mysqlpp::BadConversion& er) {  
		// Handle bad conversions
		std::cerr << "Conversion error: " << er.what() << std::endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << std::endl;
		return -1;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		std::cerr << "Error: " << er.what() << std::endl;
		return -1;
	}
	return 0;
}
