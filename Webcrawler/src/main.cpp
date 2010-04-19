#include <iostream>
#include "Crawler.h"
#include <fstream>
#include "time.h"
#include "Mysql.h"
#include "ssql_structs.h"
Mysql mysql;

int main(char** argv, char** argc)
{	
	try {
		mysql.connect("webcrawler","localhost","root","");
	} catch(char const* e) { std::cout << e << std::endl; return 1;}

	try {
	mylink row("link", "parent", false);
	mysqlpp::Query query = mysql.query();
	query.insert(row);
	query.execute();

	std::cout << query << std::endl;
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

	return 1;

	time_t seconds;
	seconds = time(NULL);	
	Crawler* _crawler = new Crawler( "http://betty.multimediatechnology.at", 100 );

	int abort = 0;
	while( !_crawler->requestsFinished())
	{
		printf ("%f requests per second\n", (float)_crawler->getRequestCount() / (float)(time(NULL) - seconds));
	}

	//getting map & iterator
	std::map< std::string, ParseResult>* _map = _crawler->getResultMap();
	std::map< std::string, ParseResult>::iterator _iter = _map->begin();
	
	//writing to logfile
	std::ofstream file( "Log.txt", std::ios::out );
	int _brokenLinks = 0;

	for( ; _iter != _map->end(); _iter++)
	{
		if( (*_iter).second._broken )
		{
			file << "Found broken URL: " << (*_iter).first << "\n";
			file << "ParentUrl: " << (*_iter).second._parentUrl << "\n\n";
			++_brokenLinks;
		}
	}

	file << "Searched URL \"" << _crawler->getDomainName() << "\" for broken links...\n";
	file << "Found\n" << _brokenLinks << " broken Links\n";
	file << ( _map->size() - _brokenLinks ) << " good links\n";
	file << "from " << _map->size() << " links to search\n";
	file.close();

	std::cout << std::endl << "End" << std::endl;

	delete _crawler;
	return 0;
}


