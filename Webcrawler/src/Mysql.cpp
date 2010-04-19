#include "Mysql.h"

using namespace RudyTheCrawler;

void Mysql::connect(char* db, char* server, char* user, char* pass)
{
	_connection = mysqlpp::Connection(false);
	if (!_connection.connect(db, server, user, pass)) {
		std::cout << _connection.error();
		throw "Connecting to DB failed!";
	}

}

mysqlpp::Query Mysql::query()
{
	return _connection.query();
}
