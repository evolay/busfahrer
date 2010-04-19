#pragma once
#include <mysql++/mysql++.h>

namespace RudyTheCrawler
{

	class Mysql {

		public:
			mysqlpp::Connection 						_connection;
			
			mysqlpp::Query query();
			void connect(char* db, char* server, char* user, char* pass);

	};

};
