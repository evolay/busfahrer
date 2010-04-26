#pragma once
#include <mysql++/mysql++.h>
#include <string>

namespace RudyTheCrawler
{

	class Mysql {

		public:
			static mysqlpp::Connection 						_connection;
			
			void connect(char* db, char* server, char* user, char* pass);
			static void insert_link(std::string link, std::string parent, bool broken);

	};

};
