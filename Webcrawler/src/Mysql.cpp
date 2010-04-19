#include "Mysql.h"
#include "ssql_structs.h"
#include <sstream>
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

	std::ostringstream oss;
	oss << "INSERT INTO mylink (url,parent_url,broken) VALUES ('" << link << "','" << parent << "'," <<broken <<")";

	std::string insert = oss.str();
	std::cout << insert << std::endl;
	mysqlpp::Query query = Mysql::_connection.query(insert.c_str());
	query.execute();
}
